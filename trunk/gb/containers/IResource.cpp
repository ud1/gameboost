/*      \file FileStream.cpp
 *      \author -Eugene-, kozlov_eugene@list.ru
*/
#include "gb/pch.h"
#include "gb/containers/IResource.h"

using namespace gb::containers;

IResource::IResource(void) : MemoryStream(), total_size(0), groups_count(0), groups_sizes(0), groups_offsets(0) { };

IResource::~IResource(void) { };

uint8_t*IResource::create(size_t _size, int _mode)
{
    return MemoryStream::create(_size, _mode);
};

bool IResource::create(const size_t _size)
{
    if(!isExist() || isOpened())
        return false;
    return MemoryStream::create(_size, gb::io::eStreamAccess::READ | gb::io::eStreamAccess::WRITE) != 0;
};

bool IResource::create(const size_t _size, const void*data)
{
    if(!isExist() || isOpened())
        return false;
    if(!MemoryStream::create(_size, gb::io::eStreamAccess::READ | gb::io::eStreamAccess::WRITE))
        return false;
    return MemoryStream::write(data, _size, 0) == _size;
};

bool IResource::update(const size_t _size, const void*data)
{
    if(!isExist() || !isOpened() || _size < size())
        return false;  
    return MemoryStream::write(data, _size, 0) == _size;
};

bool IResource::updateGroup(const size_t _size, const void*data, size_t group)
{
    if(!isExist() || !isOpened() || group >= groups_count || _size < groups_sizes[group])
        return false;  
    return MemoryStream::write(data, _size, groups_offsets[group]) == _size;
};
