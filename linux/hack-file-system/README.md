# How to modify kernel

## modify read function
**links:**
- file: https://elixir.bootlin.com/linux/v4.4.200/source/include/linux/fs.h#L875
- how to find filepath from file: https://stackoverflow.com/questions/17885676/in-linux-how-can-i-get-the-filename-from-the-struct-file-structure-while-ste
- vfs_read(): https://elixir.bootlin.com/linux/v4.4.200/source/fs/read_write.c#L442
- do_sys_open(): https://elixir.bootlin.com/linux/v4.4.200/source/fs/open.c#L1029


**How to force direct IO on certain files?**
```c
// solution: fs/read_write.c - vfs_read()
#include <linux/string.h>
if(strstr(file->f_path.dentry->d_iname, "1mb_") != NULL){
	file->f_flags |= O_DIRECT;
}

```

**How is file read?**
```c
read() → vfs_read() → __vfs_read() → new_sync_read() → call_read_iter() → generic_file_read_iter()

int open(const char *path, int oflag, .../*,mode_t mode */);
ssize_t read(int fd, void *buf, size_t count);
```
