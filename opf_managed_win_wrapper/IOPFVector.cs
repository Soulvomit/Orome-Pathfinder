/*
Interface for oromë pathfinder managed windows library:
Author:		Jonas Brown
Date:		04/1-2016
File: 		IOPFVector.cs
*/

namespace opf_managed_win_wrapper
{
    /// <summary>
    /// Interface which represents a 2d point implementation. IPFVector implementations are used by a PFTask, to represent a 2d coordinate.  
    /// </summary>
    public interface IPFVector
    {
        /// <summary>
        /// Should return the X coordinate of the point/vector as an integer value.
        /// </summary>
        ushort IntX
        {
            get;
        }
        /// <summary>
        /// Should return the Y coordinate of the point/vector integer value.
        /// </summary>
        ushort IntY
        {
            get;
        }
    }
}