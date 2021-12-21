# How to modify kernel

## modify read function
**links:**
- file: https://elixir.bootlin.com/linux/v4.4.200/source/include/linux/fs.h#L875
- how to find filepath from file: https://stackoverflow.com/questions/17885676/in-linux-how-can-i-get-the-filename-from-the-struct-file-structure-while-ste
- vfs_read(): https://elixir.bootlin.com/linux/v4.4.200/source/fs/read_write.c#L442
- do_sys_open(): https://elixir.bootlin.com/linux/v4.4.200/source/fs/open.c#L1029


**How to force direct IO on certain files?**
solution 1
```c
// solution: fs/read_write.c - vfs_read()
#include <linux/string.h>
if(strstr(file->f_path.dentry->d_iname, "1mb_") != NULL){
	file->f_flags |= O_DIRECT;
}

```
solution 2
```c
#include <linux/string.h>
#include <linux/dcache.h>
char mybuf[256];
char* mypath;
mypath = d_path(&(file->f_path), mybuf, 256);
if(strstr(mypath, "/home/") != NULL){
	file->f_flags |= O_DIRECT;
}
```
solution 3
```c
if (!strcmp(file->f_inode->i_sb->s_type->name, "ext2") && (count % 512 == 0) && ((*pos) % 512 == 0)){
	file->f_flags |= O_DIRECT;
}
```



