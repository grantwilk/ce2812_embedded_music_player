/**
  * @file song.h
  * @author Grant Wilk
  * @modified 2/9/2020
  * @brief contains structures and definitions for creating songs
  */

#ifndef CE2812_WK08_LAB_SONGS_H
#define CE2812_WK08_LAB_SONGS_H
#endif //CE2812_WK08_LAB_SONGS_H

# define SONG_MAX_LEN 256

/**
 * Types of notes
 */
typedef enum {
    NOTE_NOTE,
    NOTE_PERC,
    NOTE_REST,
    NOTE_END
} note_type;

/**
 * A single musical note
 */
typedef struct {
    note_type type;
    int duration;
    int frequency;
} note;

/**
 * An array of notes in a song
 */
typedef struct {
    note notes[SONG_MAX_LEN];
} song;