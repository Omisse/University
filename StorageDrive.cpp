#include <stdexcept>
#include <string>
#include <map>
#include <utility>
#include <vector>

#include "StorageDrive.hpp"

namespace Task
{
    StorageDrive::Volume::Volume(
        const std::string& volName,
        const std::string& filesystem,
        unsigned long long volSize,
        unsigned int clusterSize)
    {
        if (!IsValidString(volName))
        {
            throw std::invalid_argument("Некорректное имя для раздела");
        }
        if (!IsValidString(filesystem))
        {
            throw std::invalid_argument("Некорректное название файловой системы!");
        }
        if (clusterSize > volSize || volSize == 0)
        {
            throw std::invalid_argument("Размер раздела слишком мал!");
        }
        name = volName;
        size = volSize-volSize%clusterSize;
        fSystem = filesystem;
    }

    StorageDrive::StorageDrive(
        std::string vendor,
        std::string model,
        std::string serial,
        DriveTypes driveType,
        PartitionTypes partitionType,
        unsigned long long storageSpace,
        unsigned long long clusterSize
    )
    {
        if (!IsValidString(vendor))
        {
            throw std::invalid_argument("Поле \"Производитель\": некорректный ввод!");
        }
        if (!IsValidString(model))
        {
            throw std::invalid_argument("Поле \"Модель\": некорректный ввод!");
        }
        if (!IsValidString(serial))
        {
            throw std::invalid_argument("Поле \"Серийный номер\": некорректный ввод!");
        }
        if (clusterSize > storageSpace)
        {
            throw std::invalid_argument("Размер кластера не может быть больше общей вместимости!");
        }

        if (partitionType == PartitionTypes::PT_UNPARTITIONED && clusterSize != 0)
        {
            throw std::invalid_argument("При отсутствии таблицы разделов размер кластера должен быть равным 0!");
        }
        _vendor = vendor;
        _model = model;
        _serial = serial;
        _driveType = driveType;
        _storageSpace = storageSpace;
        _clusterSize = clusterSize;
        _partitionType = partitionType;
        volumes.clear();
    }

    std::string StorageDrive::GetVendor() const 
    {
        return _vendor;
    }

    std::string StorageDrive::GetModel() const
    {
        return _model;
    }

    std::string StorageDrive::GetSerialNumber() const 
    {
        return _serial;
    }

    StorageDrive::DriveTypes StorageDrive::GetDriveType() const 
    {
        return _driveType;
    }

    std::string StorageDrive::GetDriveTypeName() const 
    {
        return _driveType == DriveTypes::DT_HDD ? std::string("HDD") : std::string("SSD");
    }

    StorageDrive::PartitionTypes StorageDrive::GetPTableType() const 
    {
        return _partitionType;
    }

    std::string StorageDrive::GetPTableName() const 
    {
        std::string out("Unpartitioned");
        if (_partitionType == PartitionTypes::PT_GPT) {
            out = std::string("GPT");
        }
        if (_partitionType == PartitionTypes::PT_MBR) {
            out = std::string("MBR");
        }
        return out;
    }

    unsigned long StorageDrive::GetClusterSize() const 
    {
        return _clusterSize;
    }

    bool StorageDrive::IsPartitioned() const 
    {
        return !(_partitionType == PartitionTypes::PT_UNPARTITIONED);
    }

    unsigned long long StorageDrive::GetStorageSpace() const 
    {
        return _storageSpace;
    }

    unsigned long long StorageDrive::GetFreeSpace() const 
    {
        if (!IsPartitioned()) return _storageSpace;

        return _storageSpace-GetVolumeSizeSum()-GetUselessSpace();
    }
    
    unsigned long long StorageDrive::GetUselessSpace() const 
    {
        if (!IsPartitioned()) return _storageSpace;
        return _storageSpace%_clusterSize;
    }

    unsigned long StorageDrive::GetVolumeAmount() const 
    {
        return volumes.size();
    }

    unsigned long long StorageDrive::GetVolumeSizeSum() const 
    {
        unsigned long long sum = 0;
        for (auto volume{volumes.begin()}; volume != volumes.end(); volume++)
        {
            sum+=volume->second.GetSize();
        }
        return sum;
    }

    void StorageDrive::Repartition(PartitionTypes newPType, unsigned long newClusterSize)
    {
        if (newPType == PartitionTypes::PT_UNPARTITIONED && newClusterSize != 0) 
        {
            throw std::invalid_argument("Попытка удалить таблицу разделов, но размер кластера ненулевой!");
        }
        volumes.clear();
        _partitionType = newPType;
        _clusterSize = newClusterSize;
        return;
    }

    std::vector<unsigned int> StorageDrive::GetVolumeIDs() const
    {
        std::vector<unsigned int> ids(volumes.size());
        unsigned int i = 0;
        for (auto volume{volumes.begin()}; volume != volumes.end(); volume++)
        {
            ids[i] = volume->first;
        }
        return ids;
    }

    std::string StorageDrive::GetVolumeName(unsigned int ID) const {
        std::string name;
        try 
        {
            name = volumes.at(ID).GetName();
        }
        catch (const std::out_of_range &ex)
        {
            throw ex;
        }
        return name;
    }

    std::string StorageDrive::GetVolumeFilesystem(unsigned int ID) const {
        std::string filesystem;
        try 
        {
            filesystem = volumes.at(ID).GetFilesystem();
        }
        catch (const std::out_of_range &ex)
        {
            throw ex;
        }
        return filesystem;
    }

    unsigned long long StorageDrive::GetVolumeSize(unsigned int ID) const {
        unsigned long long size;
        try 
        {
            size = volumes.at(ID).GetSize();
        }
        catch (const std::out_of_range &ex)
        {
            throw ex;
        }
        return size;
    }



    std::vector<StorageDrive::VolumeInfo> StorageDrive::GetVolumes() const
    {
        std::vector<VolumeInfo> info(volumes.size());
        unsigned int i = 0;
        for (auto volume{volumes.begin()}; volume != volumes.end(); volume++)
        {
            info[i++] = (VolumeInfo)
            {
                volume->first,
                volume->second.GetName(),
                volume->second.GetFilesystem(),
                volume->second.GetSize()
            };
        }
        return info;
    }

    unsigned int StorageDrive::CreateVolume(const std::string& name, const std::string& filesystem ,unsigned long long volumeSize)
    {
        bool name_used = 0;
        for (auto volume{volumes.begin()}; volume != volumes.end() && !name_used; volume++)
        {
            name_used = volume->second.GetName() == name;
        }
        if (name_used)
        {
            throw std::invalid_argument("Имя раздела занято!");
        }
        if (volumeSize > GetFreeSpace())
        {
            throw std::length_error("Запрошенный объём больше свободного места на диске!");
        }

        unsigned int new_id = GenVolumeID();
        volumes.insert(std::pair<unsigned int, Volume>{new_id, Volume(name, filesystem,volumeSize, _clusterSize)});
        return new_id;
    }

    void StorageDrive::SetVolumeName(unsigned int ID,const std::string& newVolumeName)
    {
        try
        {
            auto volume_iter = volumes.find(ID);
            volume_iter->second.Rename(newVolumeName);
        }
        catch(const std::out_of_range& exID)
        {
            throw exID;
        }
        catch(const std::invalid_argument exName)
        {
            throw exName;
        }
    }

    unsigned int StorageDrive::GenVolumeID() const
    {
        return volumes.size();
    }

    std::string StorageDrive::Volume::GetName() const
    {
        return name;
    }

    std::string StorageDrive::Volume::GetFilesystem() const
    {
        return fSystem;
    }

    unsigned long long StorageDrive::Volume::GetSize() const
    {
        return size;
    }

    void StorageDrive::Volume::Rename(const std::string& newName)
    {
        if (!IsValidString(newName))
        {
            throw std::invalid_argument("Раздел не может иметь такое имя!");
        }

        name = newName;
    }

    bool StorageDrive::IsValidString(std::string sample) {
        int isNotSpecial = true;
        for (auto ch {sample.begin()}; ch != sample.end() && isNotSpecial; ch++) {
            isNotSpecial = (*ch >= 'a' && *ch <= 'z')
                || (*ch >= 'A' && *ch <= 'Z')
                || (*ch >= '!' && *ch < '@');
        }
        return !sample.empty() && isNotSpecial;
    }

}