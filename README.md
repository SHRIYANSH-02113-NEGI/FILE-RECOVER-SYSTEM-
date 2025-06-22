🔰 Project Title  :  File Recovery System Using PYTSK3

👋 Introduction:
🔍 Before We Begin: Understanding File Systems
A file system is a method and data structure that an operating system uses to control how data is stored and retrieved on storage media (like hard drives, SSDs, USB drives).

Two of the most widely used file systems in modern computing are:
_____________________________________________________________________________________________________________________________________________________________________________________________

📁 FAT32 – File Allocation Table 32
FAT32 stands for File Allocation Table (32-bit). It is an older file system introduced by Microsoft, primarily for portable storage like USB drives, SD cards, and small hard drives.

🧠 How it Works:
Data is stored in clusters, and a FAT table keeps track of where each file starts and continues.

If a file spans multiple clusters, the FAT table has to link them one after another.

It uses simple linear allocation, making it lightweight and easy to implement.
_____________________________________________________________________________________________________________________________________________________________________________________________

⚠️ Limitations of FAT32:
File Size Limit: Maximum file size is 4 GB. Any file larger than this can't be stored.

Partition Size Limit: FAT32 supports partitions only up to 2 TB.

No File Permissions: It does not support modern access control or file permissions.

No Journaling: It lacks journaling, making it more prone to corruption.

Less Efficient: For large drives and many files, FAT32 becomes inefficient and fragmented.
_____________________________________________________________________________________________________________________________________________________________________________________________

💿 NTFS – New Technology File System
NTFS (developed by Microsoft) is a modern, secure, and feature-rich file system used by all current versions of Windows and many external storage devices.

🧠 How it Works:
Instead of a FAT table, NTFS uses a Master File Table (MFT).

Each file and directory has a corresponding MFT entry with metadata and data location.

It supports advanced features like journaling, encryption, and compression.
_____________________________________________________________________________________________________________________________________________________________________________________________

🔧 Why This Matters for Our Project
Our project aims to recover deleted files from both FAT32 and NTFS file systems. To do this:

1. We must understand how data is stored and deleted in each format.
2. Deleted files in FAT32 simply have the first character in the directory entry replaced (often with 0xE5), and clusters marked as free.
3. NTFS marks file entries in the MFT as deleted but retains much metadata, making recovery possible with proper parsing.

Our project focuses on solving a real-life problem: accidental deletion of files.

Accidental file loss is something many people face in their day-to-day life—whether it's a student deleting an assignment, a developer losing code, or a regular user accidentally formatting a drive.

To tackle this issue, we developed a File Recovery System using the pytsk3 library in Python.
This tool scans the deleted files from disk images and tries to recover data using low-level access to disk partitions and file systems.
_____________________________________________________________________________________________________________________________________________________________________________________________

🧠 Technologies Used:
1. Python 3
2. C for Performance Optimization
3. pytsk3 (Python bindings for TSK – The Sleuth Kit)
4. OS module, datetime, argparse (for CLI)
5. Disk image files (.img, .dd, .vhd, etc.)
_____________________________________________________________________________________________________________________________________________________________________________________________

📌 Assumptions:
To ensure the system works effectively and delivers accurate results, the following assumptions are made:

1. Disk Image Availability :- The user provides a valid disk image file (e.g., .img, .dd, .vhd) from the storage medium where the deletion occurred.

2. Deleted Files Not Overwritten :- The tool assumes that the deleted files have not been overwritten. Once a file's sectors are reused by the system, full recovery is not guaranteed.

3. Supported File System :- The file system in the disk image should be supported by The Sleuth Kit (TSK) (e.g., NTFS, FAT, ext2/3/4). The tool may not function correctly with unsupported or encrypted file systems.

4. Read Permissions :- The Python script has permission to access the disk image file and its directories.

5. Python Environment is Set Up :- Python 3.x and required libraries like pytsk3 are properly installed on the machine running the recovery script.
