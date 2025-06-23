#include "StorageDrive.hpp"
#include <iostream>
#include <ostream>

int main(void)
{
    try
    {
        Task::StorageDrive drive(
            "Seagate",
            "Idksomething",
            "goodword123",
            Task::StorageDrive::DriveTypes::DT_HDD,
            Task::StorageDrive::PartitionTypes::PT_MBR,
            2e10,
            4
        );
        std::cout << drive.GetVendor() << std::endl;
        std::cout << drive.GetModel() << std::endl;
        std::cout << drive.GetSerialNumber() << std::endl;
        std::cout << drive.GetDriveTypeName() << std::endl;
        std::cout << drive.GetPTableName() << std::endl;
        std::cout << drive.GetFreeSpace() << std::endl;
        std::cout << drive.GetClusterSize() << std::endl;
        drive.CreateVolume("Vol1","ext4",2e5);
        std::cout << drive.GetFreeSpace() << std::endl;
        std::vector<Task::StorageDrive::VolumeInfo> infoVector = drive.GetVolumes();
        for (int i = 0; i < infoVector.size(); i++) {
            std::cout << infoVector[i].ID <<
            "||" << infoVector[i].name <<
            "||" << infoVector[i].filesystem <<
            "||" << infoVector[i].size <<
            std::endl;
        }
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    
    return 0;
}

