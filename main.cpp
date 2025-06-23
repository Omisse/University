#include "StorageDrive.hpp"
#include <exception>
#include <iostream>

void PrintStorageInfo(const Task::StorageDrive* drive)
{
    if (!drive) return;
    std::cout << "Тип таблицы разделов: " << drive->GetPTableName() << std::endl;
    std::cout << "Ёмкость накопителя: " << drive->GetStorageSpace() << std::endl;
    std::cout << "Свободное место: " << drive->GetFreeSpace() << std::endl;
    std::cout << "Количество разделов: " << drive->GetVolumeAmount() << std::endl;
    std::cout << "Суммарный объём разделов: " << drive->GetVolumeSizeSum() << std::endl;
    std::cout << "Наличие таблицы разделов: " << drive->IsPartitioned() << std::endl;
}

void PrintFullInfo(const Task::StorageDrive* drive)
{
    if(!drive) return;;
    std::cout << "Производитель: " << drive->GetVendor() << std::endl;
    std::cout << "Модель: " << drive->GetModel() << std::endl;
    std::cout << "Серийный номер: " << drive->GetSerialNumber() << std::endl;
    std::cout << "Вид накопителя: " << drive->GetDriveTypeName() << std::endl;
    PrintStorageInfo(drive);
}

int main(void)
{
    Task::StorageDrive* drive;
    std::string name("Se@gate");
    std::string model("ID-K-Some-4455-thing");
    std::string serial("887665");
    
    std::cout << "\nВызовы конструктора с некорректными данными:" << std::endl;

    try
    {
        drive = new Task::StorageDrive(
            name,
            model,
            serial,
            Task::StorageDrive::DriveTypes::DT_HDD,
            Task::StorageDrive::PartitionTypes::PT_GPT,
            3e12,
            5,
            2e10
        );
    }
    catch (const std::exception &ex)
    {
        std::cout << "Исключение: " << ex.what() << std::endl;
        drive = 0;
    }

    name = "Seagate";
    model = "ID-\nK-Some-4455-thing";
    try
    {
        drive = new Task::StorageDrive(
            name,
            model,
            serial,
            Task::StorageDrive::DriveTypes::DT_HDD,
            Task::StorageDrive::PartitionTypes::PT_GPT,
            3e12,
            5,
            2e10
        );
    }
    catch (const std::exception &ex)
    {
        std::cout << "Исключение: " << ex.what() << std::endl;
        drive = 0;
    }
    model = "ID-K-Some-4455-thing";
    serial = "8876 65";

    try
    {
        drive = new Task::StorageDrive(
            name,
            model,
            serial,
            Task::StorageDrive::DriveTypes::DT_HDD,
            Task::StorageDrive::PartitionTypes::PT_GPT,
            3e12,
            5,
            2e10
        );
    }
    catch (const std::exception &ex)
    {
        std::cout << "Исключение: " << ex.what() << std::endl;
        drive = 0;
    }
    serial = "887665";
    
    try
    {
        drive = new Task::StorageDrive(
            name,
            model,
            serial,
            Task::StorageDrive::DriveTypes::DT_HDD,
            Task::StorageDrive::PartitionTypes::PT_GPT,
            0,
            5,
            2e10
        );
    }
    catch (const std::exception &ex)
    {
        std::cout << "Исключение: " << ex.what() << std::endl;
        drive = 0;
    }
    try
    {
        drive = new Task::StorageDrive(
            name,
            model,
            serial,
            Task::StorageDrive::DriveTypes::DT_HDD,
            Task::StorageDrive::PartitionTypes::PT_GPT,
            3e12,
            0,
            2e10
        );
    }
    catch (const std::exception &ex)
    {
        std::cout << "Исключение: " << ex.what() << std::endl;
        drive = 0;
    }
    try
    {
        drive = new Task::StorageDrive(
            name,
            model,
            serial,
            Task::StorageDrive::DriveTypes::DT_HDD,
            Task::StorageDrive::PartitionTypes::PT_GPT,
            1,
            5,
            2e10
        );
    }
    catch (const std::exception &ex)
    {
        std::cout << "Исключение: " << ex.what() << std::endl;
        drive = 0;
    }

    std::cout << "\nВызов конструктора с корректными данными:" << std::endl;
    drive = new Task::StorageDrive(
        name,
        model,
        serial,
        Task::StorageDrive::DriveTypes::DT_HDD,
        Task::StorageDrive::PartitionTypes::PT_GPT,
        3e12,
        5,
        2e10
    );
    std::cout << "Получена информация:" << std::endl;
    PrintFullInfo(drive);

    std::cout << "\nУдаление таблицы разделов: " << std::endl;
    drive->SetPTableType(Task::StorageDrive::PartitionTypes::PT_UNPARTITIONED);
    PrintStorageInfo(drive);

    std::cout << "\nПопытка добавления раздела без таблицы:" << std::endl;
    try
    {
        drive->SetVolumeData(3, 330);
    }
    catch (const std::exception &ex)
    {
        std::cout << "Исключение: " << ex.what() << std::endl;
    }
    PrintStorageInfo(drive);

    std::cout << "\nУстановка новой таблицы разделов:" << std::endl;
    drive->SetPTableType(Task::StorageDrive::PartitionTypes::PT_MBR);
    PrintStorageInfo(drive);

    std::cout << "\nПопытки добавления некорректной информации о разделах:" << std::endl;
    std::cout << "\n0 разделов, объём = 3" << std::endl;
    try
    {
        drive->SetVolumeData(0, 3);
    }
    catch (const std::exception &ex)
    {
        std::cout << "Исключение: " << ex.what() << std::endl;
    }
    std::cout << "\n3 раздела, объём = 0" << std::endl;
    try
    {
        drive->SetVolumeData(3, 0);
    }
    catch (const std::exception &ex)
    {
        std::cout << "Исключение: " << ex.what() << std::endl;
    }
    std::cout << "\nОбъём раздела больше ёмкости накопителя: (3e18 > 3e12)" << std::endl;
    try
    {
        drive->SetVolumeData(1, 3e18);
    }
    catch (const std::exception &ex)
    {
        std::cout << "Исключение: " << ex.what() << std::endl;
    }

    std::cout << "\nДобавление корректной информации о разделах:" << std::endl;
    drive->SetVolumeData(44, drive->GetStorageSpace());
    PrintStorageInfo(drive);

    std::cout << "\nКонтроль полной информации о накопителе:" << std::endl;
    PrintFullInfo(drive);

    delete(drive);
    return 0;
}

