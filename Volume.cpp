#include "StorageDrive.hpp"

#include <stdexcept>

namespace Task
{
    StorageDrive::Volume::Volume(
        const std::string& volName,
        const std::string& filesystem,
        unsigned long long startAddress,
        unsigned long long endAddress
    )
    {
        _SetBoundary(startAddress, endAddress);
        SetName(volName);
        SetFilesystem(filesystem);
        SetUsedSpace(0);
    }

    unsigned long long StorageDrive::Volume::GetStartByte() const
    {
        return startByte;
    }
    unsigned long long StorageDrive::Volume::GetEndByte() const
    {
        return endByte;
    }
    std::string StorageDrive::Volume::GetName() const
    {
        return name;
    }
    std::string StorageDrive::Volume::GetFilesystem() const
    {
        return filesystem;
    }
    unsigned long long StorageDrive::Volume::GetUsedSpace() const
    {
        return usedSpace;
    }

    unsigned long long StorageDrive::Volume::GetSize() const
    {
        return GetEndByte()-GetStartByte()+1;
    }
    
    void StorageDrive::Volume::SetName(const std::string& newName)
    {
        if (!_IsValidString(newName))
        {
            throw std::invalid_argument("Некорректное имя раздела.");
        }
        name = newName;
    }
    
    void StorageDrive::Volume::SetFilesystem(const std::string& fSysName)
    {
        if (!_IsValidString(fSysName))
        {
            throw std::invalid_argument("Некорректный тип файловой системы.");
        }
        SetUsedSpace(0);
        filesystem = fSysName;
    }

    void StorageDrive::Volume::SetUsedSpace(unsigned long long newSpace)
    {
        if (newSpace > GetSize())
        {
            throw std::out_of_range("Невозможно занять больше пространства, чем размер раздела.");
        }
        usedSpace = newSpace;
    }
    
    
    void StorageDrive::Volume::_SetBoundary(unsigned long long start, unsigned long long end)
    {
        if (end < start)
        {
            throw std::invalid_argument("Начало раздела не может быть в памяти дальше его конца!");
        }
        startByte = start;
        endByte = end;
    }

    bool StorageDrive::Volume::_IsValidString(const std::string& sample)
    {
        bool isValid = true;
        for (auto ch{sample.begin()}; ch != sample.end() && isValid; ch++)
        {
            isValid = (*ch >= 'a' && *ch <= 'z')
                || (*ch >='0' && *ch <='9') 
                || (*ch >='A' && *ch <= 'Z');
        }
        return isValid;
    }
}