#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "StorageDrive.hpp"

void PrintDriveStorageInfo(const Task::StorageDrive* drive)
{
    if (!drive) return;
    std::cout << "Тип таблицы разделов: " << drive->GetPTableName() << std::endl;
    std::cout << "Ёмкость накопителя: " << drive->GetStorageSpace() << std::endl;
    std::cout << "Свободное место: " << drive->GetFreeSpace() << std::endl;
    std::cout << "Количество разделов: " << drive->GetVolumeAmount() << std::endl;
    std::cout << "Суммарный объём разделов: " << drive->GetVolumeSizeSum() << std::endl;
    std::cout << "Наличие таблицы разделов: " << drive->IsPartitioned() << std::endl;
}

void PrintDriveFullInfo(const Task::StorageDrive* drive)
{
    if(!drive) return;
    std::cout << "Производитель: " << drive->GetVendor() << std::endl;
    std::cout << "Модель: " << drive->GetModel() << std::endl;
    std::cout << "Серийный номер: " << drive->GetSerialNumber() << std::endl;
    std::cout << "Вид накопителя: " << drive->GetDriveTypeName() << std::endl;
    PrintDriveStorageInfo(drive);
}

void PrintVolumeInfo(const Task::StorageDrive* drive, unsigned long id)
{
    if (!drive) return;
    std::cout << "ID: " << id << std::endl;
    std::cout << "\tОбъём: " << drive->GetVolumeSize(id) << std::endl;
    std::cout << "\tПервый байт: " << drive->GetVolumeStartByte(id) << std::endl;
    std::cout << "\tПоследний байт: " << drive->GetVolumeEndByte(id) << std::endl;
    std::cout << "\tИмя раздела: " << drive->GetVolumeName(id) << std::endl;
    std::cout << "\tФайловая система: " << drive->GetVolumeFilesystem(id) << std::endl;
    std::cout << "\tЗанятое место: " << drive->GetVolumeUsedSpace(id) << std::endl;
}

void PrintStorageVolumes(const Task::StorageDrive* drive)
{
    if (!drive) return;
    std::vector<unsigned long> ids = drive->GetVolumeIDs();
    for (unsigned long i = 0; i < ids.size(); i++)
    {
        PrintVolumeInfo(drive, ids[i]);
        std::cout << std::endl;
    }
}

void PrintException(const char* ex)
{
    std::cout << "Исключение: " << ex << std::endl;
}

int main(void)
{
    Task::StorageDrive* drive;
    drive = new Task::StorageDrive(
        "Seagate",
        "ID-K-Some-4455-thing",
        "887665",
        Task::StorageDrive::DriveTypes::DT_SSD,
        Task::StorageDrive::PartitionTypes::PT_GPT,
        16391
    );
    std::cout << "Исходный накопитель:" << std::endl;
    PrintDriveFullInfo(drive);
    std::cout << "\nСоздадим разделы на весь объём накопителя:" << std::endl;
    drive->CreateVolume(0, 512, "Volume1", "ext4");
    drive->CreateVolume(513, 1024, "Volume2", "FAT32");
    drive->CreateVolume(1025, 2048, "Volume3", "NTFS");
    drive->CreateVolume(2049, 4096, "Volume4");
    drive->CreateVolume(4097,8192);
    drive->CreateVolume(8193, 16390);
    PrintDriveFullInfo(drive);
    PrintStorageVolumes(drive);
    std::cout << "Удалим раздел: с ID = 3" << std::endl;
    std::cout << "drive->DeleteVolume(3);" << std::endl;
    std::cout << "Результат: " << drive->DeleteVolume(3) << std::endl;
    PrintDriveFullInfo(drive);
    PrintStorageVolumes(drive);
    std::cout << "Попробуем добавить на его место не вмещающийся раздел:" << std::endl;
    std::cout << "drive->CreateVolume(0, 4097);" << std::endl;
    try
    {
        drive->CreateVolume(0, 4097);
    }
    catch (const std::out_of_range &ex)
    {
        PrintException(ex.what());
    }
    PrintStorageVolumes(drive);
    std::cout << "Добавим точно вмещающийся раздел:" << std::endl;
    std::cout << "drive->CreateVolume(2566, 4000);" << std::endl;
    drive->CreateVolume(2566, 4000);
    PrintStorageVolumes(drive);
    std::cout << "Заметим, что ID = 3 в списке уже нет, попробуем вновь удалить ID = 3" << std::endl;
    std::cout << "drive->DeleteVolume(3);" << std::endl;
    std::cout << "Результат: " << drive->DeleteVolume(3) << std::endl;
    PrintStorageVolumes(drive);
    std::cout << "С существующего раздела данные собрать удалось. Попробуем с несуществующего:" << std::endl;
    std::cout << "drive->GetVolumeFilesystem(3);" << std::endl;
    try
    {
        drive->GetVolumeFilesystem(3);
    }
    catch(const std::logic_error& ex)
    {
        PrintException(ex.what());
    }
    std::cout << "Исключение не наше, контейнер справился сам." << std::endl;
    std::cout << "\nУдалим разметку, попробуем создать раздел" << std::endl;
    std::cout << "drive->SetPTableType(Task::StorageDrive::PartitionTypes::PT_UNPARTITIONED);" << std::endl;
    std::cout << "drive->CreateVolume(0, 500);" << std::endl;
    drive->SetPTableType(Task::StorageDrive::PartitionTypes::PT_UNPARTITIONED);
    PrintDriveStorageInfo(drive);
    try
    {
        drive->CreateVolume(0, 500);
    }
    catch (std::exception& ex)
    {
        PrintException(ex.what());
    }
    std::cout << "\nПопробуем получить вектор ID разделов:" << std::endl;
    std::cout <<"drive->GetVolumeIDs().empty() == " << drive->GetVolumeIDs().empty() << std::endl;
    std::cout << "\nВернём разметку, удостоверимся что ID остались:" << std::endl;
    drive->SetPTableType(Task::StorageDrive::PartitionTypes::PT_MBR);
    drive->CreateVolume(0, 16000);
    std::cout << "drive->SetPTableType(Task::StorageDrive::PartitionTypes::PT_MBR);" << std::endl;
    std::cout << "drive->CreateVolume(0, 16000);" << std::endl;
    PrintDriveStorageInfo(drive);
    PrintStorageVolumes(drive);
    std::cout << "Разделы удалились, но отсчёт всё равно идёт с 7, как и должно быть." << std::endl;
    std::cout << "\nВ завершение тестирования, проверим работу установки значений для раздела:" << std::endl;
    std::cout << "Корректные:" << std::endl;
    std::cout << "drive->SetVolumeName(7, \"valid\");" << std::endl;
    std::cout << "drive->SetVolumeFSystem(7, \"fsystem\");" << std::endl;
    std::cout << "drive->SetVolumeUsedSpace(7, 16000);" << std::endl;
    drive->SetVolumeName(7, "valid");
    drive->SetVolumeFSystem(7, "fsystem");
    drive->SetVolumeUsedSpace(7, 16000);
    PrintStorageVolumes(drive);
    std::cout << "Некорректные:" << std::endl;
    std::cout << "drive->SetVolumeName(7, \"vali-d\");" << std::endl;
    try
    {
        drive->SetVolumeName(7, "vali-d");
    }
    catch (const std::exception& ex)
    {
        PrintException(ex.what());
    }
    std::cout << "drive->SetVolumeFSystem(7, \"fsy`stem\");" << std::endl;
    try
    {
        drive->SetVolumeFSystem(7, "fsy`stem");
    }
    catch (const std::exception& ex)
    {
        PrintException(ex.what());
    }
    std::cout << "drive->SetVolumeUsedSpace(7, 18000);" << std::endl;
    try
    {
        drive->SetVolumeUsedSpace(7, 18000);
    }
    catch (const std::exception& ex)
    {
        PrintException(ex.what());
    }
    std::cout << "\nОчистка занятого места при смене файловой системы:" << std::endl;
    PrintVolumeInfo(drive, 7);
    std::cout << "drive->SetVolumeFSystem(7, \"123\");" << std::endl;
    drive->SetVolumeFSystem(7, "123");
    PrintVolumeInfo(drive, 7);
    delete(drive);
    return 0;
}