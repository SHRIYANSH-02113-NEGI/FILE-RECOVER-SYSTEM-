#ifndef NTFS_UTILS_H
#define NTFS_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    uint8_t jump[3];
    uint8_t oemID[8];
    uint16_t bytesPerSector;
    uint8_t sectorsPerCluster;
    uint16_t reservedSectors;
    uint8_t unused1[7];
    uint8_t mediaDescriptor;
    uint16_t unused2;
    uint16_t sectorsPerTrack;
    uint16_t numberOfHeads;
    uint32_t hiddenSectors;
    uint32_t unused3;
    uint64_t totalSectors;
    uint64_t mftCluster;
    uint64_t mftMirrCluster;
    int8_t clustersPerFileRecord;
    uint8_t unused4[3];
    int8_t clustersPerIndexBuffer;
    uint8_t unused5[3];
    uint64_t volumeSerialNumber;
    uint8_t unused6[512 - 73];
} __attribute__((packed)) NTFS_Boot;

void readBootSector(FILE *disk, NTFS_Boot *boot);
void listDeletedFiles(FILE *disk, const NTFS_Boot *boot);
bool recoverDeletedFile(FILE *disk, const char *target, const NTFS_Boot *boot);

#endif
