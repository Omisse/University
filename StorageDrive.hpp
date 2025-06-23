#ifndef STORAGE_DRIVE_HPP
#define STORAGE_DRIVE_HPP

#include <string>
#include <map>
#include <vector>

namespace Task
{
    class StorageDrive
    {
        public:
            enum class DriveTypes
            {
                DT_SSD = 1 << 0,
                DT_HDD = 1 << 1,
            };

            enum class PartitionTypes
            {
                PT_UNPARTITIONED = 0,
                PT_MBR = 1 << 0,
                PT_GPT = 1 << 1,
            };

            struct VolumeInfo
            {
                unsigned long ID;
                std::string name;
                std::string filesystem;
                unsigned long long size;
            };

            StorageDrive(
                std::string vendor,
                std::string model,
                std::string serial,
                DriveTypes driveType,
                PartitionTypes partitionType,
                unsigned long long storageSpace,
                unsigned long long clusterSize
            );

            std::string GetVendor() const;
            std::string GetModel() const;
            std::string GetSerialNumber() const;
            DriveTypes GetDriveType() const;
            std::string GetDriveTypeName() const;
            PartitionTypes GetPTableType() const;
            std::string GetPTableName() const;
            unsigned long GetClusterSize() const;
            bool IsPartitioned() const;

            unsigned long long GetStorageSpace() const;
            unsigned long long GetFreeSpace() const;
            unsigned long long GetUselessSpace() const;

            void Repartition(PartitionTypes newPType, unsigned long newClusterSize);

            unsigned long GetVolumeAmount() const;
            unsigned long long GetVolumeSizeSum() const;
            std::vector<VolumeInfo> GetVolumes() const;

            std::vector<unsigned int> GetVolumeIDs() const;
            std::string GetVolumeName(unsigned int ID) const;
            std::string GetVolumeFilesystem(unsigned int ID) const;
            unsigned long long GetVolumeSize(unsigned int ID) const;

            unsigned int CreateVolume(const std::string& name, const std::string& filesystem, unsigned long long volumeSize);
            void SetVolumeName(unsigned int ID, const std::string& newVolumeName);
            unsigned int GenVolumeID() const;

        private:
            class Volume
            {
                public:
                    Volume(const std::string& volName, const std::string& filesystem,unsigned long long volSize, unsigned int clusterSize);
                    std::string GetName() const;
                    std::string GetFilesystem() const;
                    unsigned long long GetSize() const;
                    void Rename(const std::string& newName);
                    
                private:
                    std::string name;
                    std::string fSystem;
                    unsigned long long size;
            };
            std::string _vendor;
            std::string _model;
            std::string _serial;
            DriveTypes _driveType;
            unsigned long long _storageSpace;
            std::map<unsigned long, Volume> volumes;
            unsigned int _clusterSize;
            PartitionTypes _partitionType;

            static bool IsValidString(std::string sample);
    };
}
#endif