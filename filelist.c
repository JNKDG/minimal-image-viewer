#include "filelist.h"
#include <dirent.h>
#include <stdlib.h>
#include <SDL.h>

filelist *new_filelist(char* dirpath )
{
    filelist *self = calloc( 1, sizeof(filelist) );
    DIR *d = opendir(dirpath);
    struct dirent *item;
    uint16_t i = 0;

    self->_farr_size = FILE_ARRAY_STEP_SIZE;
    self->_farr = calloc( self->_farr_size, sizeof(char *) );
    self->next = _next;
    self->prev = _prev;
    self->set = _set;

    for( item = readdir( d ); item != NULL; item = readdir( d ) )
    {
        if ( i == self->_farr_size )
        {
            self->_farr_size += FILE_ARRAY_STEP_SIZE;
            self->_farr = realloc( self->_farr, sizeof(char *) * self->_farr_size );
        }

        if ( ( strcmp(item->d_name, ".") != 0 ) && ( strcmp(item->d_name, "..") != 0 ) )
        {
            char fullpath[PATH_MAX];

            strcpy_s(fullpath, PATH_MAX, dirpath);
            strcat_s( fullpath, PATH_MAX, item->d_name );
            self->_farr[i] = malloc( sizeof(char) * PATH_MAX );
            strcpy_s( self->_farr[i], PATH_MAX, fullpath );
            ++i;
        }
    }

    self->_index_last = i;

    closedir(d);
    return self;
}

char *_prev( filelist *self )
{
    if ( self->_index_pos == 0 )
    {
        self->_index_pos = self->_index_last;
    }
    else
    {
        self->_index_pos--;
    }

    return self->_farr[self->_index_pos];
}

char *_next ( filelist *self )
{
    if ( self->_index_pos == self->_index_last )
    {
        self->_index_pos = 0;
    }
    else
    {
        self->_index_pos++;
    }

    return self->_farr[self->_index_pos];
}

int _set(filelist *self, const char *filepath )
{
    for( uint16_t i = 0; i <= self->_index_last; i++)
    {
        if ( strcmp( self->_farr[i], filepath) == 0 )
        {
            self->_index_pos = i;
            return 0;
        }
    }

    return 1;
}
