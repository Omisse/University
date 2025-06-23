#include <stdexcept>
#include <string>

#include "StorageDrive.hpp"

namespace Task
{
    StorageDrive::StorageDrive()
    {
        //в данном случае строки создаются в конструкторе,
        //поскольку в методах предполагается ссылочный тип(для экономии памяти)
        //а значит, мы не можем ссылаться на "входные" данные - это не lvalue
        //и они исчезнут как только будут получены
        std::string _vendor("Unknown Vendor");
        std::string _model("Generic Storage Drive");
        std::string _serial("Unknown");

        SetVendor(_vendor);
        SetModel(_model);
        SetSerial(_serial);
        SetDriveType(DriveTypes::DT_HDD);
        SetStorageSpace(0);
        SetPTableType(PartitionTypes::PT_UNPARTITIONED);
        SetVolumeData(0, 0);
    }

    StorageDrive::StorageDrive(
        std::string& Vendor,
        std::string& Model,
        std::string& Serial,
        DriveTypes DriveType
    )
    {
        SetVendor(Vendor);
        SetModel(Model);
        SetSerial(Serial);
        SetDriveType(DriveType);
        SetStorageSpace(0);
        SetPTableType(PartitionTypes::PT_UNPARTITIONED);
        SetVolumeData(0, 0);
    }

    StorageDrive::StorageDrive(
        DriveTypes DriveType,
        PartitionTypes PartitionType,
        unsigned long long StorageSpace,
        unsigned long VolumeAmount,
        unsigned long long VolumeSizeSum
    )
    {
        //в данном случае строки создаются в конструкторе,
        //поскольку в методах предполагается ссылочный тип(для экономии памяти)
        //а значит, мы не можем ссылаться на "входные" данные - это не lvalue
        //и они исчезнут как только будут получены
        std::string _vendor("Unknown Vendor");
        std::string _model("Generic Storage Drive");
        std::string _serial("Unknown");

        SetVendor(_vendor);
        SetModel(_model);
        SetSerial(_serial);
        SetDriveType(DriveType);
        SetStorageSpace(StorageSpace);
        SetPTableType(PartitionType);
        SetVolumeData(VolumeAmount, VolumeSizeSum);
    }

    StorageDrive::StorageDrive(
        std::string& Vendor,
        std::string& Model,
        std::string& Serial,
        DriveTypes DriveType,
        PartitionTypes PartitionType,
        unsigned long long StorageSpace,
        unsigned long VolumeAmount,
        unsigned long long VolumeSizeSum
    )
    {
        SetVendor(Vendor);
        SetModel(Model);
        SetSerial(Serial);
        SetDriveType(DriveType);
        SetStorageSpace(StorageSpace);
        SetPTableType(PartitionType);
        SetVolumeData(VolumeAmount, VolumeSizeSum);
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

    unsigned long StorageDrive::GetVolumeAmount() const 
    {
        return volumeAmount;
    }

    unsigned long long StorageDrive::GetVolumeSizeSum() const 
    {
        return volumeSizeSum;
    }

    unsigned long long StorageDrive::GetStorageSpace() const 
    {
        return storageSpace;
    }

    unsigned long long StorageDrive::GetFreeSpace() const 
    {
        if (!IsPartitioned()) return storageSpace;

        return storageSpace-GetVolumeSizeSum();
    }

    void StorageDrive::SetVendor(std::string& newVendor)
    {
        if (!IsValidString(newVendor))
        {
            throw std::invalid_argument("Поле \"Производитель\": некорректный ввод!");
        };

        vendor = newVendor;
    }


    void StorageDrive::SetModel(std::string& newModel) 
    {
        if (!IsValidString(newModel))
        {
            throw std::invalid_argument("Поле \"Модель\": некорректный ввод!");
        }

        model = newModel;
    }


    void StorageDrive::SetSerial(std::string& newSerial) 
    {
        if (!IsValidString(newSerial))
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


    void StorageDrive::SetVolumeData(unsigned long newAmount, unsigned long long newSum)
    {   
        //если нет таблицы, но значение ненулевое
        if (!IsPartitioned() && (newAmount != 0 || newSum!= 0))
        {
            throw std::invalid_argument("На неразмеченном накопителе не может быть разделов!");
        }
        //если ёмкость диска не определилась, а значение ненулевое
        if (storageSpace == 0 && (newAmount != 0 || newSum != 0))
        {
            throw std::invalid_argument("На накопителе нет места для разделов.");
        }
        //если только одно из значений ненулевое
        if ((newAmount && !newSum) || (newSum && !newAmount))
        {
            throw std::invalid_argument("Количество разделов и их суммарный объём могут быть 0 только одновременно!");
        }
        //если объём меньше количества разделов
        if (newSum < newAmount)
        {
            throw std::invalid_argument("Суммарный объём разделов не может быть меньше их количества!");
        }
        //если объём больше ёмкости
        if (newSum > storageSpace)
        {
            throw std::invalid_argument("Суммарный объём разделов не может быть больше ёмкости накопителя!");
        }
        
        volumeAmount = newAmount;
        volumeSizeSum = newSum;
    }

    void StorageDrive::SetPTableType(PartitionTypes newPTableType) 
    {
        //очистить записи о разделах
        SetVolumeData(0, 0);
        partitionType = newPTableType;
    }

    bool StorageDrive::IsPartitioned() const 
    {
        return !(partitionType == PartitionTypes::PT_UNPARTITIONED);
    }

    bool StorageDrive::IsValidString(std::string sample) {
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

}