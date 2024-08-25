#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "_stdio.h"

#define PERMS 0666

// The first call to getc for a particular file finds a count of zero, which forces a call of
// _fillbuf. If _fillbuf finds that the file is not open for reading, it returns EOF immediately.
// Otherwise, it tries to allocate a buffer (if reading is to be buffered).

// Once the buffer is established, _fillbuf calls read to fill it, sets the count and pointers, and
// returns the character at the beginning of the buffer. 
// Subsequent calls to _fillbuf will find a buffer allocated.
int _fillbuf(FILE *fp) {
    int bufsize;

    if((fp->flag & (_READ | _EOF | _ERR)) != _READ) // only _READ flag should be present
        return EOF; // note EOF indicator (macro) is different from _EOF (enum flag in _flags)

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ; // 1 character at a time for unbuffered reading

    if(fp->base == NULL) // no buffer yet
        if((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF; // error allocating buffer
    
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize); // store read bytes (from position fp->ptr) in fp->cnt

    if(--fp->cnt < 0) {
        if(fp->cnt == -1) // reached eof (0 bytes were read)
            fp->flag |= _EOF;
        else
        // read(): On error, -1 is returned, and errno is set to indicate the error.
            fp->flag |= _ERR;
        
        fp->cnt = 0;
        
        return EOF;
    }

    // note: return valid characters always as unsigned char
    return (unsigned char) *fp->ptr++; // return character we read, and increment fp->ptr
}

FILE *fopen(const char* name, const char* mode) {
    int fd;
    FILE *fp;

    if(*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for(fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if((fp->flag & (_READ | _WRITE)) == 0)
            break; // found free slot
    
    // if(fp == _iob + OPEN_MAX) // no free slots
    if(fp >= _iob + OPEN_MAX) // no free slots
        return NULL;
    
    if(*mode == 'w')
        fd = creat(name, PERMS);
    else if(*mode == 'a') {
        // use 000 perms:
        // Note that mode applies only to future accesses of the
        // newly created file; the open() call that creates a read-
        // only file may well return a read/write file descriptor
        if((fd = open(name, O_WRONLY, 0)) == -1) 
            fd = creat(name, PERMS); // create file if not exists
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if(fd == -1) // could not access name
        return NULL;
    
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    
    return fp;
}

FILE _iob[OPEN_MAX] = { // stdin, stdout, stderr
    {0, (char *) 0, (char *) 0, _READ, 0},
    {0, (char *) 0, (char *) 0, _WRITE, 0},
    {0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};