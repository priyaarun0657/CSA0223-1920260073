# In-place update
Seek to index*sizeof(Stock), read one record, modify units, seek back by sizeof(Stock), write. Invalid index/read fails before any write; therefore record 9 does not damage the file.
