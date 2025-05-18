import pytsk3
import os

def start_program():
    print("Data Recovery Program Started")

def select_disk_or_image(image_path):
    print(f"Selected image: {image_path}")
    return pytsk3.Img_Info(image_path)

def mount_disk(img):
    fs = pytsk3.FS_Info(img)
    return fs

def scan_filesystem(fs):
    print("Scanning filesystem...")
    root_dir = fs.open_dir("/")
    return root_dir

def locate_deleted_entries(fs):
    deleted_entries = []
    for dir_entry in fs.open_dir(path="/"):
        if dir_entry.info.meta and dir_entry.info.meta.flags & pytsk3.TSK_FS_META_FLAG_UNALLOC:
            deleted_entries.append(dir_entry)
    return deleted_entries

def extract_metadata(entry):
    meta = entry.info.meta
    print(f"Extracting metadata for deleted file: inode={meta.addr}")
    return {
        "size": meta.size,
        "name": entry.info.name.name.decode(),
        "inode": meta.addr
    }

def read_data_blocks(fs, inode):
    file_obj = fs.open_meta(inode=inode)
    return file_obj.read_random(0, file_obj.info.meta.size)

def reconstruct_file(data, file_name):
    recovered_path = f"recovered_{file_name}"
    with open(recovered_path, "wb") as f:
        f.write(data)
    return recovered_path

def log_and_display(file_path):
    print(f"Recovered file saved as: {file_path}")

def main():
    start_program()
    
    image_path = r"disk.img"
    
    img = select_disk_or_image(image_path)
    fs = mount_disk(img)
    
    root_dir = scan_filesystem(fs)
    deleted_entries = locate_deleted_entries(fs)
    
    for entry in deleted_entries:
        metadata = extract_metadata(entry)
        data = read_data_blocks(fs, metadata["inode"])
        recovered_file = reconstruct_file(data, metadata["name"])
        log_and_display(recovered_file)

    print("End of recovery process.")

if __name__ == "__main__":
    main()
