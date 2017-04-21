/*
Interface for oromë pathfinder managed windows library:
Author:		Jonas Brown
Date:		04/1-2016
File: 		IOPFVector.cs
*/
namespace opf_managed_win_wrapper
{
    /// <summary>
    /// Interface which represents a 2d integer implementation. IPFVector implementations are used by a PFTask, to represent 2d coordinates.  
    /// </summary>
    public interface IOPFVector
    {
        /// <summary>
        /// Should return the X coordinate of the node/point/vector as an integer value.
        /// </summary>
        ushort IntX
        {
            get;
        }
        /// <summary>
        /// Should return the Y coordinate of the node/point/vector integer value.
        /// </summary>
        ushort IntY
        {
            get;
        }
    }
}