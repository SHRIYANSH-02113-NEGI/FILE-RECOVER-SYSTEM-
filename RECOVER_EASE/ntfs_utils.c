#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>
#include <stdbool.h>
#include "ntfs_utils.h"

void readBootSector(FILE *disk, NTFS_Boot *boot) {
    fseek(disk, 0, SEEK_SET);
    fread(boot, sizeof(NTFS_Boot), 1, disk);
}

void readMFTEntry(FILE *disk, int index, const NTFS_Boot *boot, uint8_t *rec, uint32_t recSize) {
    uint64_t mftOffset = boot->mftCluster * boot->sectorsPerCluster * boot->bytesPerSector;
    fseek(disk, mftOffset + index * recSize, SEEK_SET);
    fread(rec, recSize, 1, disk);
}

bool parseFileNameFromAttr(uint8_t *attr, char *fname) {
    if (*(uint32_t *)attr != 0x30) return false;
    if (*(uint32_t *)(attr + 4) < 90) return false;
    uint16_t fnLen = attr[88];
    uint16_t fnOff = *(uint16_t *)(attr + 90);
    wchar_t *wname = (wchar_t *)(attr + fnOff);
    wchar_t tmp[260] = {0};
    wcsncpy(tmp, wname, fnLen);
    wcstombs(fname, tmp, 260);
    return true;
}

void listDeletedFiles(FILE *disk, const NTFS_Boot *boot) {
    uint32_t recSize = (boot->clustersPerFileRecord > 0) ?
        boot->clustersPerFileRecord * boot->sectorsPerCluster * boot->bytesPerSector :
        (1 << -(boot->clustersPerFileRecord));
    uint8_t *rec = malloc(recSize);

    printf("[+] Scanning MFT for deleted files...\n");
    int found = 0;

    for (int i = 0; i < 10000; ++i) {
        readMFTEntry(disk, i, boot, rec, recSize);
        if (memcmp(rec, "FILE", 4) != 0) continue;

        uint16_t flags = *(uint16_t *)(rec + 22);
        if (flags & 0x01) continue;

        uint16_t offset = *(uint16_t *)(rec + 20);
        uint8_t *attr = rec + offset;

        char fname[260] = {0};
        while (*(uint32_t *)attr != 0xFFFFFFFF) {
            uint32_t len = *(uint32_t *)(attr + 4);
            if (parseFileNameFromAttr(attr, fname)) {
                printf("Deleted: %s (MFT idx: %d)\n", fname, i);
                found++;
                break;
            }
            attr += len;
        }
    }

    if (!found)
        printf("[-] No deleted files found in MFT.\n");

    free(rec);
}

bool recoverDeletedFile(FILE *disk, const char *target, const NTFS_Boot *boot) {
    uint32_t recSize = (boot->clustersPerFileRecord > 0) ?
        boot->clustersPerFileRecord * boot->sectorsPerCluster * boot->bytesPerSector :
        (1 << -(boot->clustersPerFileRecord));
    uint8_t *rec = malloc(recSize);

    for (int i = 0; i < 2048; ++i) {
        readMFTEntry(disk, i, boot, rec, recSize);
        if (memcmp(rec, "FILE", 4) != 0) continue;
        if (*(uint16_t *)(rec + 22) & 0x01) continue;

        uint16_t offset = *(uint16_t *)(rec + 20);
        uint8_t *attr = rec + offset;

        char fname[260] = {0};
        uint64_t dataLcn = 0, dataSize = 0;

        while (*(uint32_t *)attr != 0xFFFFFFFF) {
            uint32_t type = *(uint32_t *)attr;
            uint32_t len = *(uint32_t *)(attr + 4);
            if (type == 0x30) {
                parseFileNameFromAttr(attr, fname);
            } else if (type == 0x80) {
                uint8_t flags = attr[8];
                if (flags & 0x01) {
                    uint32_t runOff = *(uint32_t *)(attr + 32);
                    uint8_t *run = attr + runOff;
                    dataSize = *(uint64_t *)(attr + 48);

                    int len = run[0];
                    int count = len >> 4;
                    int offsetSize = len & 0xF;
                    uint64_t lcn = 0;
                    memcpy(&lcn, run + 1 + offsetSize, count);
                    dataLcn = lcn;
                }
            }
            attr += len;
        }

        if (strcmp(fname, target) == 0 && dataLcn) {
            FILE *out = fopen(fname, "wb");
            uint64_t offsetBytes = dataLcn * boot->sectorsPerCluster * boot->bytesPerSector;
            fseek(disk, offsetBytes, SEEK_SET);
            uint8_t *buf = malloc(dataSize);
            fread(buf, 1, dataSize, disk);
            fwrite(buf, 1, dataSize, out);
            fclose(out); free(buf); free(rec);
            printf("[+] Recovered '%s' (%llu bytes)\n", fname, (unsigned long long)dataSize);
            return true;
        }
    }

    free(rec);
    return false;
}
