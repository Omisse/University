#ifndef STORAGE_DRIVE_HPP
#define STORAGE_DRIVE_HPP

#include <string>

namespace Task
{
    class StorageDrive
    {
        public:
            enum class DriveTypes //перечисление видов накопителя
            {
                DT_SSD = 1 << 0,
                DT_HDD = 1 << 1,
            };

            enum class PartitionTypes //перечисление типов таблицы разделов
            {
                PT_UNPARTITIONED = 0,
                PT_MBR = 1 << 0,
                PT_GPT = 1 << 1,
            };
            StorageDrive(); //конструктор по умолчанию
            StorageDrive( //конструктор информационной составляющей
                std::string& Vendor, //производитель
                std::string& Model, //модель
                std::string& Serial, //серийный номер
                DriveTypes DriveType //вид накопителя
            );

            StorageDrive( //конструктор технической составляющей
                DriveTypes DriveType, //вид накопителя
                PartitionTypes PartitionType, //тип таблицы разделов
                unsigned long long StorageSpace, //ёмкость
                unsigned long VolumeAmount, //количество разделов
                unsigned long long VolumeSizeSum //суммарный объём разделов
            );

            StorageDrive( //полный конструктор
                std::string& Vendor, //производитель
                std::string& Model,//модель
                std::string& Serial,//серийный номер
                DriveTypes DriveType,//вид накопителя
                PartitionTypes PartitionType,//тип таблицы разделов
                unsigned long long StorageSpace,//ёмкость
                unsigned long VolumeAmount,//количество разделов
                unsigned long long VolumeSizeSum//суммарный объём разделов
            );

            std::string GetVendor() const; //получить значение поля "производитель"
            std::string GetModel() const;//получить значение поля "модель"
            std::string GetSerialNumber() const;//получить значение поля "серийный номер"
            DriveTypes GetDriveType() const;//получить значение поля "вид накопителя"
            std::string GetDriveTypeName() const;//получить значение поля "вид накопителя" в виде строки
            PartitionTypes GetPTableType() const;//получить значение поля "тип таблицы разделов"
            std::string GetPTableName() const;//получить значение поля "тип таблицы разделов" в виде строки
            unsigned long GetVolumeAmount() const;//получить значение поля "количество разделов"
            unsigned long long GetVolumeSizeSum() const;//получить значение поля "суммарный объём разделов"
            

            unsigned long long GetStorageSpace() const;//получить значение поля "ёмкость"
            unsigned long long GetFreeSpace() const;//получить информацию о незанятом месте на накопителе

            void SetVendor(std::string& newVendor); //установить значение поля "производитель"
            void SetModel(std::string& newModel); //установить значение поля "модель"
            void SetSerial(std::string& newSerial); //установить значение поля "серийный номер"
            void SetDriveType(DriveTypes newDriveType); //установить значение поля "вид накопителя"
            void SetStorageSpace(unsigned long long newStorageSpace); //установить значение поля "ёмкость
            void SetVolumeData(unsigned long newAmount, unsigned long long newSum); //установить значения полей "количество разделов" и "суммарный объём разделов"
            void SetPTableType(PartitionTypes newPTableType); //установить значение поля "тип таблицы разделов"

            bool IsPartitioned() const; //получить информацию о наличии таблицы разделов

        private:
            std::string vendor; //производитель
            std::string model; //модель
            std::string serial; //серийный номер
            DriveTypes driveType; //вид накопителя
            PartitionTypes partitionType; //тип таблицы разделов
            unsigned long long storageSpace; //ёмкость
            unsigned long volumeAmount; //количество разделов
            unsigned long long volumeSizeSum; //суммарный объём разделов

            bool IsValidString(std::string sample); //служебная функция проверки корректности входной строки
    };
}
#endif