#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <imgview.h>

int main( int argc, char *argv[] )
{
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        SDL_LogCritical( SDL_LOG_CATEGORY_ERROR, "SDL_Init failed: %s\n", SDL_GetError() );
        return 1;
    }

    image_viewer imgv; // context

    imgv_start( &imgv, "imgview", argv[1] ); // init values within the struct, and SDL_image

    // loads the file specified in the command line. MIGHT FAIL IF THE FILE IS UNSUPPORTED.TODO.
    imgv_load( &imgv, argv[1] );

    imgv_display( &imgv );

    SDL_Event e;

    while (1)
    {
        if ( imgv.exit_flag )
        {
            break;
        }

        if ( SDL_WaitEvent( &e ) )
        {
            if ( e.type == SDL_KEYDOWN )
            {
                imgv_key_press( &imgv, e.key.keysym.scancode );
            }
        }
    }

    imgv_quit( &imgv );

    return 0;
}
