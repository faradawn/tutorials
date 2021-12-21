# How to modify kernel

## modify read function
**links:**
- file: https://elixir.bootlin.com/linux/v4.4.200/source/include/linux/fs.h#L875
- how to find filepath from file: https://stackoverflow.com/questions/17885676/in-linux-how-can-i-get-the-filename-from-the-struct-file-structure-while-ste
- vfs_read(): https://elixir.bootlin.com/linux/v4.4.200/source/fs/read_write.c#L442
- do_sys_open(): https://elixir.bootlin.com/linux/v4.4.200/source/fs/open.c#L1029


**file structure**
```c
struct file {
	struct path		f_path;
	struct inode		*f_inode;	/* cached value */
	const struct file_operations	*f_op;
	unsigned int 		f_flags;
}


// solution: fs/read_write.c - vfs_read()
#include <string.h>
if(strstr(file->f_path.dentry->d_iname, "1mb_") != NULL){
	file->f_flags |= O_DIRECT;
}

```

**How is file read?**
```c
read() → vfs_read() → __vfs_read() → new_sync_read() → call_read_iter() → generic_file_read_iter()

int open(const char *path, int oflag, .../*,mode_t mode */);
ssize_t read(int fd, void *buf, size_t count);



ssize_t vfs_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
{

        if (!strcmp(file->f_inode->i_sb->s_type->name, "ext2") && (count % 512 == 0) && ((*pos) % 512 == 0))

                file->f_flags |= O_DIRECT;

        /* Conplete the reading operation */
}

```
