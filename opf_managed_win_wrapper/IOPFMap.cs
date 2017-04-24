/*
Interface for oromë pathfinder managed windows library:
Author:		Jonas Brown
Date:		04/1-2016
File: 		IOPFMap.cs
*/
namespace opf_managed_win_wrapper
{
    /// <summary>
    /// Interface which represents a left-handed top-down 2d grid implementation. Any 2d grid implementation, that wishes to use the PFTask must inheirit from IPFMap.  
    /// </summary>
    public interface IOPFMap
    {
        /// <summary>
        /// Should return the width (in nodes) of this 2d map. Width is screen space left to right. 
        /// </summary>
        ushort Width
        {
            get;
        }
        /// <summary>
        /// Should return the height (in nodes) of this 2d map. Hieght is screen space top to bottom.
        /// </summary>
        ushort Height
        {
            get;
        }
        /// <summary>
        /// Should return the MaxPathLengt for this 2d map. A value equal to MapWidth*MapHeight will insure the whole 
        /// map is searched. A lower value will conserve memory.
        /// </summary>
        uint MaxPathLength
        {
            get;
        }
        /// <summary>
        /// Should convert a 2d grid of resistance bytes to a linear array of resistance bytes. 
        /// </summary>
        /// <returns>A byte array representing the 2d resistance topograhy of this map.</returns>
        byte[] GetResistanceBytes();
    }
}