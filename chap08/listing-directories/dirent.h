#ifndef DIRENT_H
#define DIRENT_H

#define MY_NAME_MAX    14 // long filename component (system dependent)

// Dirent is a mapping from ino to filename
typedef struct {            // portable directory entry
    long ino;               // inode number
    char name[MY_NAME_MAX+1];  // name + '\0' terminator
} Dirent;

typedef struct {    // minimal MY_DIR: no buffering etc.
    int fd;         // file descriptor for the directory
    Dirent d;       // the directory entry
} MY_DIR;

MY_DIR *my_opendir(char *dirname);
Dirent *my_readdir(MY_DIR *dfd);
void my_closedir(MY_DIR *dfd);

// struct stat /* inode information returned by stat */
// {
//     dev_t st_dev; /* device of inode */
//     ino_t st_ino; /* inode number */
//     short st_mode; /* mode bits */
//     short st_nlink; /* number of links to file */
//     short st_uid; /* owners user id */
//     short st_gid; /* owners group id */
//     dev_t st_rdev; /* for special files */
//     off_t st_size; /* file size in characters */
//     time_t st_atime; /* time last accessed */
//     time_t st_mtime; /* time last modified */
//     time_t st_ctime; /* time originally created */
// };

// #define S_IFMT 0160000 /* type of file: */
// #define S_IFDIR 0040000 /* directory */
// #define S_IFCHR 0020000 /* character special */
// #define S_IFBLK 0060000 /* block special */
// #define S_IFREG 0010000 /* regular */

#endif