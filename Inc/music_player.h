/**
  * @file piezo.h
  * @author Grant Wilk
  * @created 2/9/2020
  * @modified 2/9/2020
  * @brief A driver for generating tones on the piezo buzzer.
  */

#ifndef CE2812_WK08_LAB_PIEZO_H
#define CE2812_WK08_LAB_PIEZO_H
#endif //CE2812_WK08_LAB_PIEZO_H

#include "songs.h"

/**
 * Initializes the internal note buffer
 */
void mp_init(void);

/**
 * Starts playing the notes currently queued in the internal note buffer
 */
void mp_play(void);

/**
 * Stops playing notes
 */
void mp_stop(void);

/**
 * Queues a note to play on the piezo buzzer
 * @param n - the note to queue
 */
void mp_add_note(note n);

/**
 * Queues a song to play using the piezo buzzer
 * @param s - the song to queue
 */
void mp_add_song(song s);

/**
 * Clears all notes from the note queue
 */
void mp_clear(void);