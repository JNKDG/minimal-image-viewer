#ifndef IMGVIEW_H
#define IMGVIEW_H

#include <stdint.h>
#include "filelist.h"


typedef struct
{
    uint8_t exit_flag;
    SDL_Window *w;
    SDL_Surface *w_surface;
    SDL_Surface *img;
    filelist *_flist;

}image_viewer;

int imgv_start(image_viewer *imgv , const char *wintitle , const char *filepath);

void imgv_kb_set();

void imgv_key_press( image_viewer *imgv, int key );

int imgv_load( image_viewer *imgv, const char *filepath ); // will return 1 on failure

void imgv_prev ( image_viewer *imgv );

void imgv_next ( image_viewer *imgv );

int imgv_display( image_viewer *imgv );

void imgv_exit_flag_set( image_viewer *imgv );

void imgv_deinit( image_viewer *imgv );

void imgv_quit( image_viewer *imgv );

#endif // IMGVIEW_H
