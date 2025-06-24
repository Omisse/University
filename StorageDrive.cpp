#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

#include "StorageDrive.hpp"


namespace Task
{
    StorageDrive::StorageDrive()
    {
        //Я был неправ в ЛР5, дело в том, что я не константы принимал.
        SetVendor("Unknown Vendor");
        SetModel("Generic Storage Drive");
        SetSerial("Unknown");
        SetDriveType(DriveTypes::DT_HDD);
        SetStorageSpace(0);
        SetPTableType(PartitionTypes::PT_UNPARTITIONED);
        volumes.clear();
        lastUsedID = 0;
    }

    StorageDrive::StorageDrive(
        const std::string& Vendor,
        const std::string& Model,
        const std::string& Serial,
        DriveTypes DriveType
    )
    {
        SetVendor(Vendor);
        SetModel(Model);
        SetSerial(Serial);
        SetDriveType(DriveType);
        SetStorageSpace(0);
        SetPTableType(PartitionTypes::PT_UNPARTITIONED);
        volumes.clear();
        lastUsedID = 0;
    }

    StorageDrive::StorageDrive(
        DriveTypes DriveType,
        PartitionTypes PartitionType,
        unsigned long long StorageSpace
    )
    {
        //Я был неправ в ЛР5, дело в том, что я не константы принимал.
        SetVendor("Unknown Vendor");
        SetModel("Generic Storage Drive");
        SetSerial("Unknown");
        SetDriveType(DriveType);
        SetStorageSpace(StorageSpace);
        SetPTableType(PartitionType);
        volumes.clear();
        lastUsedID = 0;
    }

    StorageDrive::StorageDrive(
        const std::string& Vendor, 
        const std::string& Model,
        const std::string& Serial,
        DriveTypes DriveType,
        PartitionTypes PartitionType,
        unsigned long long StorageSpace
    )
    {
        SetVendor(Vendor);
        SetModel(Model);
        SetSerial(Serial);
        SetDriveType(DriveType);
        SetStorageSpace(StorageSpace);
        SetPTableType(PartitionType);
        volumes.clear();
        lastUsedID = 0;
    }

    std::string StorageDrive::GetVendor() const 
    {
        return vendor;
    }

    std::string StorageDrive::GetModel() const
    {
        return model;
    }

    std::string StorageDrive::GetSerialNumber() const 
    {
        return serial;
    }

    StorageDrive::DriveTypes StorageDrive::GetDriveType() const 
    {
        return driveType;
    }

    std::string StorageDrive::GetDriveTypeName() const 
    {
        //тернарный оператор не имеет особого смысла кроме лёгкой экономии места.
        return driveType == DriveTypes::DT_HDD ? std::string("HDD") : std::string("SSD");
    }

    StorageDrive::PartitionTypes StorageDrive::GetPTableType() const 
    {
        return partitionType;
    }

    std::string StorageDrive::GetPTableName() const 
    {
        std::string out("Таблица отсутствует");
        if (partitionType == PartitionTypes::PT_GPT) {
            out = std::string("GPT");
        }
        if (partitionType == PartitionTypes::PT_MBR) {
            out = std::string("MBR");
        }
        return out;
    }    

    unsigned long long StorageDrive::GetFreeSpace() const 
    {
        if (!IsPartitioned()) return storageSpace;

        return storageSpace-GetVolumeSizeSum();
    }

    void StorageDrive::SetVendor(const std::string& newVendor)
    {
        if (!_IsValidString(newVendor))
        {
            throw std::invalid_argument("Поле \"Производитель\": некорректный ввод!");
        };

        vendor = newVendor;
    }


    void StorageDrive::SetModel(const std::string& newModel) 
    {
        if (!_IsValidString(newModel))
        {
            throw std::invalid_argument("Поле \"Модель\": некорректный ввод!");
        }

        model = newModel;
    }


    void StorageDrive::SetSerial(const std::string& newSerial) 
    {
        if (!_IsValidString(newSerial))
        {
            throw std::invalid_argument("Поле \"Серийный номер\": некорректный ввод!");
        }

        serial = newSerial;
    }

    void StorageDrive::SetDriveType(StorageDrive::DriveTypes newDriveType)
    {
        driveType = newDriveType;
    }

    void StorageDrive::SetStorageSpace(unsigned long long newStorageSpace)
    {
        storageSpace = newStorageSpace;
        SetPTableType(PartitionTypes::PT_UNPARTITIONED);
    }

    bool StorageDrive::IsPartitioned() const 
    {
        return !(partitionType == PartitionTypes::PT_UNPARTITIONED);
    }

    bool StorageDrive::_IsValidString(const std::string& sample) {
        int isNotSpecial = true;
        //данная функция не учитывает конец таблицы ASCII, а так же кириллические символы
        //кириллица не учитывается по причине необходимости переработки строки под "широкие" символы
        for (auto ch {sample.begin()}; ch != sample.end() && isNotSpecial; ch++) {
            isNotSpecial = (*ch >= 'a' && *ch <= 'z')
                || (*ch >= 'A' && *ch <= 'Z')
                || (*ch >= ' ' && *ch < '@');
        }
        //также проверим "непустоту" строки.
        return !sample.empty() && isNotSpecial;
    }
    
    unsigned long StorageDrive::GetVolumeAmount() const 
    {
        return volumes.size();
    }

    unsigned long long StorageDrive::GetVolumeSizeSum() const 
    {
        unsigned long long sum = 0;
        for (auto vol{volumes.begin()}; vol != volumes.end(); vol++)
        {
            sum += vol->second.GetSize();
        }
        return sum;
    }

    unsigned long long StorageDrive::GetStorageSpace() const 
    {
        return storageSpace;
    }

    void StorageDrive::SetPTableType(PartitionTypes type)
    {
        partitionType = type;
        volumes.clear();    
    }

    bool StorageDrive::_doIFit(unsigned long long startByte, unsigned long long endByte) const
    {
        bool fit = endByte < storageSpace;
        unsigned long long tempStart, tempEnd;
        for (auto vol{volumes.begin()}; vol != volumes.end() && fit; vol++)
        {
            tempStart = vol->second.GetStartByte();
            tempEnd = vol->second.GetEndByte();
            //если хоть один из адресов оказался в пределах запрошенного - невозможно создать раздел.
            fit &= !((startByte <= tempStart) && (tempStart <= endByte));
            fit &= !((startByte <= tempEnd) && (tempEnd <= endByte));
        }
        return fit;
    }

    void StorageDrive::CreateVolume(unsigned long long startByte, unsigned long long endByte, const std::string& name, const std::string& filesystem)
    {
        Volume* vol = 0;
        if (partitionType == PartitionTypes::PT_UNPARTITIONED)
        {
            throw std::domain_error("Невозможно создать раздел на неразмеченном накопителе");
        }
        if (!_doIFit(startByte, endByte))
        {
            throw std::out_of_range("Раздел с такими адресами не может быть расположен на накопителе.");
        }
        try
        {
            vol = new Volume(name, filesystem, startByte, endByte);
        }
        catch (const std::logic_error& ex)
        {
            delete(vol);
            throw ex;
        }
        volumes.insert({lastUsedID++, *vol});
        delete(vol);
    }

    std::vector<unsigned long> StorageDrive::GetVolumeIDs() const
    {
        std::vector<unsigned long> out;
        out.reserve(volumes.size());
        for (auto vol{volumes.begin()}; vol != volumes.end(); vol++)
        {
            out.push_back(vol->first);
        }
        return out;
    }

    bool StorageDrive::DeleteVolume(unsigned long ID)
    {
        //В качестве информации передадим дальше bool = true, если удаление успешно.
        return volumes.erase(ID) != 0;
        //Можно было бы вызвать исключение если такого ID не было в нашем словаре
        //Но глобально - если его не было, ничего не изменилось, критической ошибки не произошло.
    }

    unsigned long long StorageDrive::GetVolumeStartByte(unsigned long ID) const
    {
        return volumes.at(ID).GetStartByte();
    }

    unsigned long long StorageDrive::GetVolumeEndByte(unsigned long ID) const
    {
        return volumes.at(ID).GetEndByte();
    }

    std::string StorageDrive::GetVolumeName(unsigned long ID) const
    {
        return volumes.at(ID).GetName();
    }
    
    std::string StorageDrive::GetVolumeFilesystem(unsigned long ID) const
    {
        return volumes.at(ID).GetFilesystem();
    }

    unsigned long long StorageDrive::GetVolumeSize(unsigned long ID) const
    {
        return volumes.at(ID).GetSize();
    }

    unsigned long long StorageDrive::GetVolumeUsedSpace(unsigned long ID) const
    {
        return volumes.at(ID).GetUsedSpace();
    }

    void StorageDrive::SetVolumeName(unsigned long ID, const std::string& name)
    {
        volumes.at(ID).SetName(name);
    }

    void StorageDrive::SetVolumeFSystem(unsigned long ID, const std::string& fSysName)
    {
        volumes.at(ID).SetFilesystem(fSysName);
    }

    void StorageDrive::SetVolumeUsedSpace(unsigned long ID, unsigned long long newSpace)
    {
        volumes.at(ID).SetUsedSpace(newSpace);
    }
}