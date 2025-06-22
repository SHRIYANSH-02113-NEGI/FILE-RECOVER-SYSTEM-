## 🛠️ STEPS TO USE
---

### 📦 Step 1: Create a Virtual Disk (VHD)

1. Open **Disk Management** (`diskmgmt.msc`)
2. Click on **Action → Create VHD**
3. Set:
   - `Location`: `C:\mydisk.vhd`
   - `Size`: 100 MB (for testing)
   - `Format`: VHD
   - `Type`: Fixed Size (recommended)
4. Initialize the disk as **MBR**
5. Right-click unallocated space → **New Simple Volume**
   - Format as **FAT32** or **NTFS** (your choice)
---

### 📸 Step 2: Use the VHD as a Disk Image

> You can use the `.vhd` file **directly** as an input to your recovery tool (no conversion needed).

---

### ⚙️ Step 3: Compile and Run

#### 🔧 Compile for NTFS and FAT32 (C):

```bash
gcc main.c ntfs_utils.c -o ntfs_recover
./ntfs_recover mydisk.vhd NTFS

gcc mainfat.c fat32_utils.c -o fat32_recover
./fat32_recover mydisk.vhd FAT32

