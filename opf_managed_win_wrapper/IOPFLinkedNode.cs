using System;
using System.Collections.Generic;
using System.Linq;
namespace opf_managed_win_wrapper
{
    public interface IOPFLinkedNode
    {
        uint ID
        {
            get;
        }
        IOPFLinkedNode[] Links
        {
            get;
        }
    }
}
