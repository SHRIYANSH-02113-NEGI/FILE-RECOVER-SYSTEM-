#include <stdio.h>
#include <stdlib.h>
#include "ntfs_utils.h"

int main() {
    char drivePath[100];
    printf("Enter NTFS drive (e.g., \\\\.\\E:): ");
    scanf("%s", drivePath);

    FILE *disk = fopen(drivePath, "rb");
    if (!disk) {
        perror("Failed to open disk");
        return 1;
    }

    NTFS_Boot boot;
    readBootSector(disk, &boot);

    listDeletedFiles(disk, &boot);

    char target[260];
    printf("Enter the name of the file to recover (case-sensitive): ");
    scanf("%s", target);

    if (!recoverDeletedFile(disk, target, &boot)) {
        printf("[-] Recovery failed or file not found.\n");
    }

    fclose(disk);
    return 0;
}
