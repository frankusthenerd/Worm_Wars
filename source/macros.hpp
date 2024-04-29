#ifndef MACROS_HEADER
#define MACROS_HEADER 1

#include <allegro.h>
#include <cstring>

using namespace std;

inline void Load_Bitmap_File(const char* bitmap_name,
                             BITMAP** bitmap)
{

    char file_name[50+1];

    strcpy(file_name, bitmap_name);
    fix_filename_slashes(file_name);
    (*bitmap) = load_bitmap(file_name, NULL);
    
}

inline void Load_Music_Track_File(const char* music_track_name,
                                  MIDI** music_track)
{

    char file_name[50+1];

    strcpy(file_name, music_track_name);
    fix_filename_slashes(file_name);
    (*music_track) = load_midi(file_name);
    
}

#endif
