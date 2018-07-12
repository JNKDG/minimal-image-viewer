TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    imgview.c \
    filelist.c

LIBS = -L..\SDL2-2.0.8\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -static-libgcc -mconsole

LIBS += -L..\SDL2_image-2.0.3\i686-w64-mingw32\lib -lSDL2_image

INCLUDEPATH = ..\SDL2-2.0.8\i686-w64-mingw32\include\SDL2

INCLUDEPATH += ..\SDL2_image-2.0.3\i686-w64-mingw32\include\SDL2

HEADERS += \
    imgview.h \
    filelist.h
