// filelist - a class-like structure that will extract all the file paths
// from a given directory path and allow you to iterate through them

#ifndef FILELIST_H
#define FILELIST_H

#include <stdint.h>

// value that the dynamic array holding the file paths will grow by
// when it becomes full
#define FILE_ARRAY_STEP_SIZE 10

typedef struct filelist_s
{
    uint16_t _farr_size;
    uint16_t _index_pos;
    uint16_t _index_last;
    char **_farr;
    char* (*prev)(struct filelist_s*);
    char* (*next)(struct filelist_s*);
    int (*set)(struct filelist_s*, const char *);
}filelist;

filelist *new_filelist( char* dirpath );

char *_prev( filelist *self );

char *_next( filelist *self );

// finds the specified file path and sets the current position to it
// if it's among the file paths contained in the struct
int _set( filelist *self, const char *filepath );

void _debug_print ( filelist *self );

#endif // FILELIST_H
