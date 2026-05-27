//------------------------------------------------------------------------------------------------
template <class Storage>
void Settings <Storage> :: clear()
{
    header.magic       = MAGIC;
    header.data_end    = sizeof(Header);
    header.index_end   = kst_size;
    header.entries_count = 0;
    _write_header();
    uint8_t buf[3] = {5, 6, 7};
    storage.write(kst_size - 3, buf);
}
//------------------------------------------------------------------------------------------------
template <class Storage>
bool Settings <Storage> :: _validate_header() const
{
    if(header.magic != MAGIC)
        return false;
    if(header.data_end < sizeof(Header))
        return false;
    if(header.index_end > kst_size)
        return false;
    if(header.data_end > header.index_end)
        return false;
    return true;
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
