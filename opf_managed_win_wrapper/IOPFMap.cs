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
        /// Should return the width of the 2d map. Width is screen space left to right. 
        /// </summary>
        ushort Width
        {
            get;
        }
        /// <summary>
        /// Should return the height of the 2d map. Hieght is screen space top to bottom.
        /// </summary>
        ushort Height
        {
            get;
        }
        /// <summary>
        /// Should convert a 2d grid of bytes to a linear array of bytes. 
        /// </summary>
        /// <returns>A byte array representing the 2d topograhy of a map.</returns>
        byte[] GetLinearTopography();
    }
}