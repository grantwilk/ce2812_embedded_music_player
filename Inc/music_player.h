/**
  * @file music_player.c
  * @author Grant Wilk
  * @created 2/09/2020
  * @modified 2/10/2020
  * @brief an API for playing music using two piezo buzzers
  */

# ifndef MUSIC_PLAYER_H
# define MUSIC_PLAYER_H
# endif

# include "note_buffer.h"

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
void mp_stop();

/**
 * Queues a note to play on the piezo buzzer
 * @param n - the note to queue
 */
void mp_add_note(mp_note * n);

/**
 * Queues a song to play using the piezo buzzer
 * @param s - the song to queue
 */
void mp_add_song(mp_song * s);

/**
 * Clears all notes from the note queue
 */
void mp_clear(void);

/**
 * Converts a non-keys note to a keys note
 * @param n - the note to convert
 * @return the converted note
 */
void mp_conv_to_keys(mp_note * n);