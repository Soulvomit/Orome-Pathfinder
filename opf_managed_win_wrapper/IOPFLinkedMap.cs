namespace opf_managed_win_wrapper
{
    public interface IOPFLinkedMap
    {
        IOPFLinkedNode[] Map
        {
            get;
        }

        uint[] GetMapLinksArr();

        uint[] GetMapLinkCountsArr();

        byte[] GetMapResistanceArr();
    }
}
