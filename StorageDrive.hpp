#ifndef STORAGE_DRIVE_HPP
#define STORAGE_DRIVE_HPP

#include <string>
#include <unordered_map>
#include <vector>

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
                const std::string& Vendor, //производитель
                const std::string& Model, //модель
                const std::string& Serial, //серийный номер
                DriveTypes DriveType //вид накопителя
            );

            StorageDrive( //конструктор технической составляющей
                DriveTypes DriveType, //вид накопителя
                PartitionTypes PartitionType, //тип таблицы разделов
                unsigned long long StorageSpace //ёмкость
            );

            StorageDrive( //полный конструктор
                const std::string& Vendor, //производитель
                const std::string& Model,//модель
                const std::string& Serial,//серийный номер
                DriveTypes DriveType,//вид накопителя
                PartitionTypes PartitionType,//тип таблицы разделов
                unsigned long long StorageSpace //ёмкость
            );

            std::string GetVendor() const; //получить значение поля "производитель"
            std::string GetModel() const;//получить значение поля "модель"
            std::string GetSerialNumber() const;//получить значение поля "серийный номер"
            DriveTypes GetDriveType() const;//получить значение поля "вид накопителя"
            std::string GetDriveTypeName() const;//получить значение поля "вид накопителя" в виде строки
            PartitionTypes GetPTableType() const;//получить значение поля "тип таблицы разделов"
            std::string GetPTableName() const;//получить значение поля "тип таблицы разделов" в виде строки

            unsigned long long GetStorageSpace() const;//получить значение поля "ёмкость"
            
            void SetVendor(const std::string& newVendor); //установить значение поля "производитель"
            void SetModel(const std::string& newModel); //установить значение поля "модель"
            void SetSerial(const std::string& newSerial); //установить значение поля "серийный номер"
            void SetDriveType(DriveTypes newDriveType); //установить значение поля "вид накопителя"
            void SetStorageSpace(unsigned long long newStorageSpace); //установить значение поля "ёмкость
            
            bool IsPartitioned() const; //получить информацию о наличии таблицы разделов

            /*
            ------------------------------------------------------------
            НАЧАЛО ОБНОВЛЁННЫХ МЕТОДОВ
            ------------------------------------------------------------
            */
            //void SetPTableType(PartitionTypes newPTableType); //установить значение поля "тип таблицы разделов"
            //void SetClusterSize(unsigned long newClusterSize); //установить значение поля "размер кластера"
            //SetPtableType, SetClusterSize == SetPartition()
            void SetPTableType(PartitionTypes type);
            unsigned long long GetFreeSpace() const;//получить информацию о незанятом месте на накопителе
            unsigned long GetVolumeAmount() const;//получить значение поля "количество разделов"
            unsigned long long GetVolumeSizeSum() const;//получить значение поля "суммарный объём разделов"
            void CreateVolume( //"конструктор" раздела
                unsigned long long startByte,
                unsigned long long endByte,
                const std::string& name = "",
                const std::string& filesystem = "");
            std::vector<unsigned long> GetVolumeIDs() const; //получение вектора ID существующих разделов
            bool DeleteVolume(unsigned long ID); //удаление раздела
            unsigned long long GetVolumeStartByte(unsigned long ID) const; //получение адреса начала раздела
            unsigned long long GetVolumeEndByte(unsigned long ID) const; //получение адреса конца раздела
            std::string GetVolumeName(unsigned long ID) const; //получение имени раздела
            std::string GetVolumeFilesystem(unsigned long ID) const; //получение файловой системы раздела
            unsigned long long GetVolumeSize(unsigned long ID) const; //получение размера раздела
            unsigned long long GetVolumeUsedSpace(unsigned long ID) const; //получение занятого пространства раздела
            void SetVolumeName(unsigned long ID, const std::string& name); //установка нового имени раздела
            void SetVolumeFSystem(unsigned long ID, const std::string& fSysName); //установка новой файловой системы раздела
            void SetVolumeUsedSpace(unsigned long ID, unsigned long long newSpace); //обновление занятого места раздела

        private:
            class Volume
            {
                public:
                    /*
                    Конструктор со всеми полями.
                    Поскольку класс находится в закрытой части StorageDrive,
                    Мы используем метод-прокладку в публичной части StorageDrive,
                    Поэтому дополнительные конструкторы не нужны.
                    */
                    Volume(
                        const std::string& volName,
                        const std::string& filesystem,
                        unsigned long long startByte,
                        unsigned long long endByte
                    );

                    unsigned long long GetStartByte() const; //Возвращает адрес начала раздела.
                    unsigned long long GetEndByte() const; //Возвращает адрес конца раздела.
                    std::string GetName() const; //Возвращает имя раздела.
                    std::string GetFilesystem() const; //Возвращает тип файловой системы.
                    unsigned long long GetSize() const; //возвращает вычисленное значение размера раздела (end-start+1)
                    unsigned long long GetUsedSpace() const; //возвращает значение поля "занятое место"
                    
                    //Устанавливает название раздела.
                    void SetName(const std::string& newName);
                    //Устанавливает тип файловой системы. При установке происходит очистка занятого пространства.
                    void SetFilesystem(const std::string& fSysName);
                    //устанавливает объём занятого пространства. Не может быть больше размера раздела.
                    void SetUsedSpace(unsigned long long newSpace);
                    
                private:
                    std::string name; //название раздела, может быть пустым
                    std::string filesystem; //тип файловой системы, может быть пустым
                    unsigned long long startByte; //адрес первого байта раздела
                    unsigned long long endByte; //адрес последнего байта раздела
                    unsigned long long usedSpace; //объём занятого полезными данными пространства
                    
                    void _SetBoundary(unsigned long long start, unsigned long long end); //вызывается в конструкторе
                    static bool _IsValidString(const std::string& sample); //внутренний метод, определяет корректность ввода строк name и filesystem.
            };            

            
            std::string vendor; //производитель
            std::string model; //модель
            std::string serial; //серийный номер
            DriveTypes driveType; //вид накопителя
            PartitionTypes partitionType; //тип таблицы разделов
            unsigned long long storageSpace; //ёмкость

            std::unordered_map<unsigned long, Volume> volumes; //словарь разделов
            //служебная функция проверки, свободен ли указанный диапазон адресов
            bool _doIFit(unsigned long long startByte, unsigned long long endByte) const;
            //служебный счётчик ID разделов, чтобы не допустить повторения.
            unsigned long lastUsedID;
            static bool _IsValidString(const std::string& sample); //служебная функция проверки корректности входной строки
    };
}
#endif