/*
Class for oromë pathfinder managed windows library:
Author:		Jonas Brown
Date:		04/1-2016
File: 		OPFTask.cs
*/
using System;
using System.Runtime.InteropServices;

namespace opf_managed_win_wrapper
{
    /// <summary>
    /// Status flags: Gives information about the last operation "called" on a PFTask.
    /// </summary>
    public enum OPFStatus: byte
    {
        #region Enumerated Types             
        ErrorPointOutOfBounds,      //the starting or target point is out-of-bounds. 
        ErrorPathTooLong,           //the path is longer the supplied maxPathLength.
        ErrorStartNotTraversable,   //the starting point in not tarversable.
        ErrorTargetNotTraversable,  //the target point in not tarversable.
        ErrorTargetNotAccessable,   //all paths to the target point are blocked.
        ErrorStartIsTarget,         //starting point and target point are the same.
        ErrorUndefined,             //undefined error.
        TaskIsRunning,              //task has not completed yet.
        TaskIsDone,                 //task is done, but not necessarily synchronized yet.
        TaskUninitialized           //task is in a syncronized state - task is ready for re-initialization.
        #endregion
    }

    /// <summary>
    /// Each PFTask corresponds to a windows worker thread and its thread local data on the native level.
    /// </summary>
    public sealed class PFTask
    {
        #region Internal Data
        private IntPtr instanceData = IntPtr.Zero;                  //pointer to native task data.
        private bool isDone = true;                                 //private storage for isDone flag.
        private int pathLength = 0;                                 //private storage for pathLength value.
        private OPFStatus pfStatus = OPFStatus.TaskUninitialized;     //private storage for pfStatus flag.
        #endregion

        #region Properties
        #region IsDone Property
        /// <summary>
        /// Gets the isDone flag and updates pfStatus. Done does not mean that the task is properly synchroniced yet.
        /// Done only means that the data is ready for retrieval. If you on re-initializing the task you must still
        /// synchronize it.
        /// </summary>
        public bool IsDone
        {
            get
            {
                isDone = PFThreadDone(instanceData);
                if (isDone)
                {
                    pfStatus = OPFStatus.TaskIsDone;
                }
                else
                {
                    pfStatus = OPFStatus.TaskIsRunning;
                }
                return isDone;
            }
        }
        #endregion

        #region PathLength Property
        /// <summary>
        /// Gets the length of the last worked path and updates the pfStatus. If null is returned the reason 
        /// will be decernable via the Status.
        /// </summary>
        public int? PathLength
        {
            get
            {
                int pathcode = PFThreadGetPathLength(instanceData);

                if (pathcode > 0)
                {
                    pathLength = pathcode;
                    pfStatus = OPFStatus.TaskIsDone;
                    return pathLength;
                }
                switch (pathcode)
                {
                    case 0:
                        pathLength = pathcode;
                        pfStatus = OPFStatus.ErrorStartIsTarget;
                        return null;
                    case -1:
                        pathLength = pathcode;
                        pfStatus = OPFStatus.ErrorPointOutOfBounds;
                        return null;
                    case -2:
                        pathLength = pathcode;
                        pfStatus = OPFStatus.ErrorTargetNotTraversable;
                        return null;
                    case -3:
                        pathLength = pathcode;
                        pfStatus = OPFStatus.ErrorStartNotTraversable;
                        return null;
                    case -4:
                        pathLength = pathcode;
                        pfStatus = OPFStatus.ErrorTargetNotAccessable;
                        return null;
                    case -5:
                        pathLength = pathcode;
                        pfStatus = OPFStatus.ErrorTargetNotAccessable;
                        return null;
                    case -6:
                        pathLength = pathcode;
                        pfStatus = OPFStatus.ErrorPathTooLong;
                        return null;
                    case -10:
                        pathLength = pathcode;
                        pfStatus = OPFStatus.TaskIsRunning;
                        return null;
                }
                pfStatus = OPFStatus.ErrorUndefined;
                return null;
            }
        }
        #endregion

        #region Status Property
        public OPFStatus Status
        {
            get
            {
                return pfStatus;
            }
        }
        #endregion

        #region FinalPath Property
        /// <summary>
        /// Gets the final path last worked task and updates the pfStatus. If null is returned the reason 
        /// will be decernable via the Status.
        /// </summary>
        public int[] FinalPath
        {
            get
            {
                IntPtr pathdata = PFThreadGetPOutbuffer(instanceData);
                int[] ints = new int[pathLength];
                int bytesCounter = 0;
                for (int i = 0; i < pathLength; i++)
                {
                    ints[i] = Marshal.ReadInt32(pathdata, bytesCounter);
                    bytesCounter = bytesCounter + 4;
                }
                //Marshal.Copy(bytes, 0, pathdata, pathLength);
                //int[] pathdata = PFThreadGetPOutbuffer(instanceData);
                if (pathdata == null)
                {
                    pfStatus = OPFStatus.TaskIsRunning;
                }
                else
                {
                    pfStatus = OPFStatus.TaskIsDone;
                }
                return ints;
                //return pathdata;
            }
        }
        #endregion

        #region Native Property Handlers
        //documented in pf_native_wrapper source code
        [DllImport("opf_native_win_wrapper.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.U1)]
        private static extern bool PFThreadDone(IntPtr instanceData);
        //documented in pf_native_wrapper source code
        [DllImport("opf_native_win_wrapper.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.SysUInt)]
        private static extern IntPtr PFThreadGetPOutbuffer(IntPtr instanceData);
        //documented in pf_native_wrapper source code
        [DllImport("opf_native_win_wrapper.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.I4)]
        private static extern int PFThreadGetPathLength(IntPtr instanceData);
        #endregion
        #endregion

        #region Constructor 
        /// <summary>
        /// Starts a new threaded pathfinding task.
        /// </summary>
        /// <param name="startPoint">Starting point of the path.</param>
        /// <param name="targetPoint">Target point of the path.</param>
        /// <param name="map">Topographic data to use for pathfinding. Must inheirit from interface: IPFMap.</param>
        /// <param name="maxPathLength">The maximum pathlength. Pathfinding will stop once enum PathTooLong. A value equal to 
        /// MapWidth*MapHeight will insure that the insure map is searched. A lower value will conserve memory.</param>
        public PFTask(IPFVector startPoint, IPFVector targetPoint, IOPFMap map, int maxPathLength, bool includeDiagonals = true, byte nodeBaseCost = 1)
        {
            pfStatus = OPFStatus.TaskIsRunning;
            byte[] linearTopography = map.GetLinearTopography();
            instanceData = FindPathExThreaded(startPoint.IntX, startPoint.IntY, targetPoint.IntX, targetPoint.IntY, linearTopography,
                    map.Width, map.Height, maxPathLength, includeDiagonals, nodeBaseCost);
        }
        //documented in pf_native_wrapper source code
        [DllImport("opf_native_win_wrapper.dll", CharSet = CharSet.Ansi,  CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.SysUInt)]
        private static extern IntPtr FindPathExThreaded(
            [param: MarshalAs(UnmanagedType.U4)]
            int startX,
            [param: MarshalAs(UnmanagedType.U4)]
            int startY,
            [param: MarshalAs(UnmanagedType.U4)]
            int targetX,
            [param: MarshalAs(UnmanagedType.U4)]
            int targetY,
            [param: MarshalAs(UnmanagedType.LPArray)]
            byte[] map,
            [param: MarshalAs(UnmanagedType.U4)]
            int mapWidth,
            [param: MarshalAs(UnmanagedType.U4)]
            int mapHeight,
            [param: MarshalAs(UnmanagedType.U4)]
            int outBufferSize,
            [param: MarshalAs(UnmanagedType.U1)]
            bool includeDiagonal,
            [param: MarshalAs(UnmanagedType.U4)]
            int nodeBaseCost);
        #endregion

        #region Destructor
        /// <summary>
        /// Terminates the thread and does native level cleanup of thread data. Only called by the garbage collector.
        /// </summary>
        ~PFTask()
        {
            PFThreadDeleteTID(instanceData);
        }
        //documented in pf_native_wrapper source code
        [DllImport("opf_native_win_wrapper.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern void PFThreadDeleteTID(IntPtr instanceData);
        #endregion

        #region Methods
        #region Join Method
        /// <summary>
        /// Attempts to synchronize the task with the calling thread.
        /// </summary>
        /// <returns>Bool: true = PFTask was synchronized with calling thread, false = PFTask is still working on a task OR no task has been started.</returns>
        public bool Join()
        {
            if (PFThreadJoin(instanceData))
            {
                pfStatus = OPFStatus.TaskUninitialized;
                return true;
            }
            else
            {
                pfStatus = OPFStatus.TaskIsRunning;
                return false;
            }
        }
        //documented in pf_native_wrapper source code
        [DllImport("opf_native_win_wrapper.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.U1)]
        private static extern bool PFThreadJoin(IntPtr instanceData);
        #endregion

        #region WaitJoin Method
        /// <summary>
        /// Synchronizes the task with the calling thread.
        /// </summary>
        /// <returns>Bool: true = PFTask was synchronized with calling thread, false = no task has been started.</returns>
        public bool WaitJoin()
        {
            if (PFThreadWaitJoin(instanceData))
            {
                pfStatus = OPFStatus.TaskUninitialized;
                return true;
            }
            else
            {
                pfStatus = OPFStatus.TaskUninitialized;
                return false;
            }
        }
        //documented in pf_native_wrapper source code
        [DllImport("opf_native_win_wrapper.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.U1)]
        private static extern bool PFThreadWaitJoin(IntPtr instanceData);
        #endregion

        #region Initialize
        /// <summary>
        /// Initializes (or re-intializes) a pathfinding task. Use this if ïf the PFTask was default constructed or you wish the re-initialize an instance PFTask.
        /// </summary>
        /// <param name="startPoint">Starting point of the path.</param>
        /// <param name="targetPoint">Target point of the path.</param>
        /// <param name="map">Topographic data to use for pathfinding. Must inheirit from interface: IPFMap.</param>
        /// <param name="maxPathLength">The maximum pathlength. Pathfinding will stop once enum PathTooLong. A value equal to 
        /// MapWidth*MapHeight will insure that the insure map is searched. A lower value will conserve memory.</param>
        /// <param name="wait">Wait for completion of current pathfinding.</param>
        /// <returns></returns>
        public bool Initialize(IPFVector startPoint, IPFVector targetPoint, IOPFMap map, int maxPathLength, bool wait = false, bool includeDiagonals = true, byte nodeBaseCost = 1)
        {
            if (!isDone)
            {
                if (!wait)
                {
                    return false;
                }
                if (!WaitJoin())
                {
                    return false;
                } 
            }
            PFThreadDeleteTID(instanceData);
            pfStatus = OPFStatus.TaskIsRunning;
            instanceData = FindPathExThreaded(startPoint.IntX, startPoint.IntY, targetPoint.IntX, targetPoint.IntY, map.GetLinearTopography(),
                    map.Width, map.Height, maxPathLength, includeDiagonals, nodeBaseCost);
            return true;
        }
        #endregion
        #endregion
    }
}
