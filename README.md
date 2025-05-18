🔰 Project Title  :  File Recovery System Using PYTSK3


👋 Introduction:

Hi, I’m Shriyansh Negi, and this is my PBL (Project-Based Learning) submission under the Operating System subject.
Our project focuses on solving a real-life problem: accidental deletion of files.

Accidental file loss is something many people face in their day-to-day life—whether it's a student deleting an assignment, a developer losing code, or a regular user accidentally formatting a drive.

To tackle this issue, we developed a File Recovery System using the pytsk3 library in Python.
This tool scans the deleted files from disk images and tries to recover data using low-level access to disk partitions and file systems.

🧠 Technologies Used:
1. Python 3
2. pytsk3 (Python bindings for TSK – The Sleuth Kit)
3. OS module, datetime, argparse (for CLI)
4. Disk image files (.img, .dd, .vhd, etc.)

📌 Assumptions:
To ensure the system works effectively and delivers accurate results, the following assumptions are made:

1. Disk Image Availability :- The user provides a valid disk image file (e.g., .img, .dd, .vhd) from the storage medium where the deletion occurred.

2. Deleted Files Not Overwritten :- The tool assumes that the deleted files have not been overwritten. Once a file's sectors are reused by the system, full recovery is not guaranteed.

3. Supported File System :- The file system in the disk image should be supported by The Sleuth Kit (TSK) (e.g., NTFS, FAT, ext2/3/4). The tool may not function correctly with unsupported or encrypted file systems.

4. Read Permissions :- The Python script has permission to access the disk image file and its directories.

5. Python Environment is Set Up :- Python 3.x and required libraries like pytsk3 are properly installed on the machine running the recovery script.
