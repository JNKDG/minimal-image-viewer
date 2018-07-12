#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "imgview.h"

void ( *imgv_kb[284] )( image_viewer* );

int imgv_start( image_viewer *imgv, const char *wintitle, const char *filepath )
{
    imgv->exit_flag = 0;
    imgv_kb_set();

    const int flags=IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF;

    if( (IMG_Init(flags) & flags) != flags )
        return 1;

    // getting the directory path out of the full file path
    char dirpath[PATH_MAX];
    int i;

    for( i = strlen(filepath) - 1; i > 0; i-- )
    {
        if( (filepath[i] == '\\') || (filepath[i] == '/') )
        {
            break;
        }
    }

    strcpy_s(dirpath, PATH_MAX, filepath);
    dirpath[i+1] = '\0';

    imgv->_flist = new_filelist( dirpath );
    imgv->_flist->set( imgv->_flist, filepath );

    imgv->w = SDL_CreateWindow( wintitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1, 1, SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS );

    return 0;
}

void imgv_kb_set()
{
    // SDL scancode values are just DEFINEd integers, so
    // they can be used directly as array indices
    memset( imgv_kb, 0, sizeof(imgv_kb) );
    imgv_kb[SDL_SCANCODE_Q] = imgv_exit_flag_set;
    imgv_kb[SDL_SCANCODE_ESCAPE] = imgv_exit_flag_set;
    imgv_kb[SDL_SCANCODE_LEFT] = imgv_prev;
    imgv_kb[SDL_SCANCODE_UP] = imgv_prev;
    imgv_kb[SDL_SCANCODE_RIGHT] = imgv_next;
    imgv_kb[SDL_SCANCODE_DOWN] = imgv_next;
    return;
}

void imgv_key_press( image_viewer *imgv, int key )
{
    if ( imgv_kb[key] != NULL )
        imgv_kb[key](imgv);
    return;
}

int imgv_load( image_viewer *imgv, const char *filepath )
{
   imgv->img = IMG_Load( filepath );

   if( imgv->img == NULL )
       return 1;

    return 0;
}

void imgv_prev ( image_viewer *imgv )
{
    while( imgv_load( imgv, imgv->_flist->prev(imgv->_flist) ) == 1 ) //skip files that don't load properly
    {
    }
    imgv_deinit( imgv );
    imgv_display( imgv );

    return;
}

void imgv_next ( image_viewer *imgv )
{
    while( imgv_load( imgv, imgv->_flist->next(imgv->_flist) ) == 1 )
    {
    }
    imgv_deinit( imgv );
    imgv_display( imgv );

    return;
}

int imgv_display ( image_viewer *imgv )
{
    SDL_Rect drawarea;
    SDL_GetDisplayUsableBounds(0, &drawarea);
    int win_w = imgv->img->w;
    int win_h = imgv->img->h;
    // scaling down images that are bigger than the usable desktop area
    if ( imgv->img->w > drawarea.w )
    {
        win_w = drawarea.w;
        win_h = ( win_w * imgv->img->h ) / imgv->img->w;
    }

    if ( imgv->img->h > drawarea.h )
    {
        win_h = drawarea.h;
        win_w = ( win_h * imgv->img->w ) / imgv->img->h;
    }

    // resizing the window to fit the image
    SDL_SetWindowSize( imgv->w, win_w, win_h);
    SDL_SetWindowPosition( imgv->w, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    if ( imgv->w == NULL )
        return 1;

    imgv->w_surface = SDL_GetWindowSurface( imgv->w );

    SDL_BlitScaled( imgv->img, NULL, imgv->w_surface, NULL);

    SDL_UpdateWindowSurface( imgv->w );

    return 0;
}

void imgv_exit_flag_set( image_viewer *imgv )
{
    imgv->exit_flag = 1;
    return;
}

void imgv_deinit( image_viewer *imgv )
{
    SDL_FreeSurface( imgv->w_surface );
    return;
}

void imgv_quit ( image_viewer *imgv )
{
    SDL_FreeSurface( imgv->img );
    SDL_FreeSurface( imgv->w_surface );
    SDL_DestroyWindow( imgv->w );
    IMG_Quit();
    SDL_Quit();
    return;
}
