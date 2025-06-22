import pytsk3
import sys
import os

def read_data_blocks(fs, inode):
    file = fs.open_meta(inode=inode)
    data = b""
    size = file.info.meta.size

    if size == 0:
        return data

    offset = 0
    CHUNK_SIZE = 1024 * 1024

    while offset < size:
        available_to_read = min(CHUNK_SIZE, size - offset)
        data += file.read_random(offset, available_to_read)
        offset += available_to_read

    return data

def extract_metadata(entry):
    metadata = {
        "name": entry.info.name.name.decode("utf-8", errors="ignore"),
        "inode": entry.info.meta.addr,
        "size": entry.info.meta.size,
        "created": entry.info.meta.crtime,
        "modified": entry.info.meta.mtime,
        "deleted": entry.info.meta.atime,
    }
    return metadata

def recover_deleted_file(image_path, target_filename):
    if not os.path.exists(image_path):
        print(f"[!] Disk image not found: {image_path}")
        return

    try:
        img = pytsk3.Img_Info(image_path)
        fs = pytsk3.FS_Info(img)
        directory = fs.open_dir(path="/")

        found = False

        for entry in directory:
            if entry.info.name.name and entry.info.meta:
                if entry.info.meta.flags & pytsk3.TSK_FS_META_FLAG_UNALLOC:
                    metadata = extract_metadata(entry)
                    if metadata["name"] == target_filename:
                        print(f"[+] Deleted file found: {metadata['name']}")
                        data = read_data_blocks(fs, metadata["inode"])

                        output_path = f"recovered_{metadata['name']}"
                        with open(output_path, "wb") as f:
                            f.write(data)

                        print(f"[✔] File recovered and saved as: {output_path}")
                        found = True
                        break

        if not found:
            print(f"[!] File '{target_filename}' not found or not deleted.")

    except Exception as e:
        print(f"[!] Error: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python recover.py <image_file> <filename_to_recover>")
    else:
        image_path = sys.argv[1]
        target_filename = sys.argv[2]
        recover_deleted_file(image_path, target_filename)
