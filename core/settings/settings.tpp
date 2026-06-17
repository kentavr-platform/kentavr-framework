
//------------------------------------------------------------------------------------------------
/**
 * @brief Constructs the settings storage object.
 *
 * Reads the settings header from EEPROM and formats the storage area if the
 * header is missing, corrupted, or incompatible with the current format.
 */
template <EEPROM_Storage :: offset_t Size>
__inline Settings <Size> :: Settings()
{
    _read_header();
    if(!is_valid())
    {
        format();
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Formats the settings storage area.
 *
 * Reinitializes the header and clears the logical contents of the settings
 * storage. Existing EEPROM bytes outside the header are not erased, but become
 * inaccessible because the index is reset.
 */
template <EEPROM_Storage :: offset_t Size>
__inline  void Settings <Size> :: format()
{
    header.magic       = MAGIC;
    header.data_end    = sizeof(Header);
    header.index_end   = kst_size;
    header.entries_count = 0;
    _write_header();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Reads a raw binary setting by key.
 *
 * Searches for a setting identified by the pair @p key and @p size, then copies
 * its stored binary data into @p data.
 *
 * @param key Setting key.
 * @param data Destination buffer.
 * @param size Number of bytes to read.
 *
 * @retval OK Setting was found and read successfully.
 * @retval ERR_BAD_PARAMETER @p data is nullptr or @p size is zero.
 * @retval ERR_NOT_FOUND No setting with the specified key and size exists.
 * @retval ERR_INVALID Settings storage header is invalid.
 */
template <EEPROM_Storage :: offset_t Size>
__inline ResultCode Settings <Size> :: read(uint32_t key, void *data, size_t size)
{
    if(data == nullptr || size == 0)
        return ERR_BAD_PARAMETER;

    IndexRecord entity = {key, size, 0};
    ResultCode result = _find(entity);
    if(result != OK)
    {
        return result;
    }
    EEPROM.read(entity.addr, data, size);
    return OK;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Reads a typed setting by key.
 *
 * Reads exactly sizeof(Type) bytes into @p value. The setting is identified by
 * the pair @p key and sizeof(Type).
 *
 * @tparam Type Value type.
 * @param key Setting key.
 * @param value Destination value.
 *
 * @return Result code.
 */
template <EEPROM_Storage :: offset_t Size>
template <class Type>
__inline ResultCode Settings <Size> :: read(uint32_t key, Type &value)
{
    return read(key, &value, sizeof(Type));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes a raw binary setting by key.
 *
 * If a setting identified by the pair @p key and @p size already exists, its
 * data is overwritten in place. Otherwise a new record is appended to the data
 * area and a new index entry is created.
 *
 * @param key Setting key.
 * @param data Source buffer.
 * @param size Number of bytes to write.
 *
 * @retval OK Setting was written successfully.
 * @retval ERR_BAD_PARAMETER @p data is nullptr or @p size is zero.
 * @retval ERR_NO_SPACE_LEFT Not enough free EEPROM space for a new setting.
 * @retval ERR_INVALID Settings storage header is invalid.
 */
template <EEPROM_Storage :: offset_t Size>
__inline ResultCode Settings <Size> :: write(uint32_t key, const void *data, size_t size)
{
    if(data == nullptr || size == 0)
        return ERR_BAD_PARAMETER;

    IndexRecord entity = {key, size, header.data_end};
    ResultCode result = _find(entity);

    switch(result)
    {
    case ERR_NOT_FOUND:
        // add new entity
        if(size + sizeof(IndexRecord) > get_free_space())
        {
            return ERR_NO_SPACE_LEFT;
        }
        header.index_end -= sizeof(IndexRecord);
        header.data_end += size;
        header.entries_count++;
        EEPROM.write(entity.addr, data, size);  // data
        EEPROM.write(header.index_end, entity); // index
        _write_header();                        // header
        return OK;
    case OK:
        EEPROM.write(entity.addr, data, size);
        return OK;
    default:
        return result;
    }
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Writes a typed setting by key.
 *
 * Writes exactly sizeof(Type) bytes from @p value. The setting is identified by
 * the pair @p key and sizeof(Type).
 *
 * @tparam Type Value type.
 * @param key Setting key.
 * @param value Source value.
 *
 * @return Result code.
 */
template <EEPROM_Storage :: offset_t Size>
template <class Type>
__inline ResultCode Settings <Size> :: write(uint32_t key, const Type &value)
{
    return write(key, &value, sizeof(Type));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Checks whether the settings storage header is valid.
 *
 * Verifies the magic value, data/index bounds, and index size consistency.
 *
 * @retval true Header is valid.
 * @retval false Header is invalid or incompatible.
 */
template <EEPROM_Storage :: offset_t Size>
__inline bool Settings <Size> :: is_valid() const
{
    if(header.magic != MAGIC)
        return false;

    if(header.data_end < sizeof(Header))
        return false;

    if(header.data_end > kst_size)
        return false;

    if(header.index_end > kst_size)
        return false;

    if(header.data_end > header.index_end)
        return false;

    if(header.entries_count > kst_size / sizeof(IndexRecord))
        return false;

    uint16_t index_size = header.entries_count * sizeof(IndexRecord);

    if(index_size > kst_size)
        return false;

    if(header.index_end != kst_size - index_size)
        return false;

    return true;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Returns the amount of free space in the settings storage area.
 *
 * Free space is the gap between the end of the data area and the beginning of
 * the index area.
 *
 * @return Number of free bytes.
 */
 template <EEPROM_Storage :: offset_t Size>
__inline uint16_t Settings <Size> :: get_free_space() const
{
    return header.index_end - header.data_end;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Finds a setting entry in the index.
 *
 * Searches the settings index for a record matching the pair
 * @p entry.key and @p entry.size. If found, the record address is written
 * back to @p entry.addr.
 *
 * The search is performed from the newest index entry to the oldest.
 *
 * @param[in,out] entry Search descriptor. The @c key and @c size fields are
 * used as search criteria. On success, @c addr is updated with the data
 * location of the matching setting.
 *
 * @retval OK Matching setting was found.
 * @retval ERR_NOT_FOUND No matching setting exists.
 * @retval ERR_INVALID Settings storage header is invalid.
 */
template <EEPROM_Storage :: offset_t Size>
__inline ResultCode Settings <Size> :: _find(IndexRecord &entry) const
{
    if(!is_valid())
    {
        return ERR_INVALID;
    }
    IndexRecord record;
    for(uint16_t i = 1; i <= header.entries_count; i++)
    {
        EEPROM.read(kst_size - i * sizeof(IndexRecord), record);
        if(record.key == entry.key && record.size == entry.size)
        {
            entry.addr = record.addr;
            return OK;
        }
    }
    return ERR_NOT_FOUND;
}
//------------------------------------------------------------------------------------------------

