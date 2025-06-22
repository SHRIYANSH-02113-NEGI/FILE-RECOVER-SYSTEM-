# 🔰Project Title: File Recovery System Using PYTSK3 and C

## 👋 Introduction

Accidental file loss is a common issue — whether it's a student deleting an assignment, a developer losing source code, or a user accidentally formatting a storage device. Our project addresses this real-world problem by creating a **File Recovery System** capable of recovering deleted files from disk images.

This tool utilizes **pytsk3 (Python bindings for The Sleuth Kit)** for NTFS-based recovery and **C-based implementation** for both NTFS and FAT32 systems, enabling low-level access to file system structures and deleted file entries.

---

## 🔍 Understanding File Systems

A **file system** is the structure and method used by an operating system to store and manage data on drives such as SSDs, HDDs, and USBs.

Two of the most widely used file systems in modern computing are:

---

### 📁 FAT32 – File Allocation Table 32

**FAT32** is an older file system introduced by Microsoft, commonly used in USB drives, memory cards, and small partitions.

#### 🧠 How It Works:
1. Data is stored in clusters; a **FAT Table** tracks where each file starts and continues.
2. If a file spans multiple clusters, the FAT links them sequentially.
3. Uses simple linear allocation, making it lightweight and easy to implement.

#### ⚠️ Limitations:
- ❌ **Max File Size**: 4 GB
- ❌ **Max Partition Size**: 2 TB
- ❌ **No File Permissions**
- ❌ **No Journaling** (prone to corruption)
- ❌ **Fragmentation** issues in large disks

---

### 💿 NTFS – New Technology File System

**NTFS** is a modern, secure file system developed by Microsoft and used by all current Windows systems.

#### 🧠 How It Works:
1. Uses a **Master File Table (MFT)** to store metadata and file information.
2. Each file/directory has an MFT entry with attributes like name, size, and location.
3. Supports **journaling**, **encryption**, **compression**, and **file permissions**.

#### ✅ Advantages over FAT32:
| Feature               | FAT32        | NTFS              |
|----------------------|--------------|-------------------|
| Max File Size        | 4 GB         | 16 TB+            |
| File Permissions     | ❌ No        | ✅ Yes            |
| Journaling Support   | ❌ No        | ✅ Yes            |
| Encryption/Compression | ❌ No     | ✅ Yes            |
| Crash Recovery       | Poor         | Excellent         |

---

## 🔧 Why This Matters

To effectively recover deleted files from **FAT32 and NTFS**, we must understand how they handle deletion:

- In **FAT32**, deletion simply marks the first character of a directory entry as `0xE5`, and marks the clusters as free.
- In **NTFS**, deletion marks the MFT entry as unused but often retains metadata and data clusters.

Thus, recovery is possible **as long as the deleted file data hasn’t been overwritten.**

---

## 🧠 Technologies Used

- 🐍 **Python 3.x**
- 🔧 **C (for FAT32 and NTFS low-level access)**
- 📚 **pytsk3** – Python bindings for The Sleuth Kit
- 🧰 **argparse**, `os`, `datetime` – Python standard modules
- 💾 Supports: `.img`, `.dd`, `.vhd` disk image formats

---

## 📌 Assumptions

To ensure accurate recovery, the following assumptions are made:

1. **Disk Image Availability**: User provides a valid disk image file (e.g., `.img`, `.dd`, `.vhd`).
2. **Files Not Overwritten**: Deleted files must not have their sectors reused.
3. **Supported File System**: Works on NTFS, FAT32, ext2/3/4 (as supported by TSK).
4. **Permissions**: Script has permission to read the image file.
5. **Python Environment Ready**: Python 3.x and `pytsk3` must be properly installed.

---

> ✅ This project demonstrates deep system-level understanding of file systems and their internal structures to **recover lost data intelligently and safely.**

---

