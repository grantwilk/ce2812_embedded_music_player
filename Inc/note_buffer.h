/**
  * @file note_buffer.c
  * @author Grant Wilk
  * @created 2/09/2020
  * @modified 2/09/2020
  * @brief a circular queue for buffering notes
  */

# ifndef NOTEBUFFER_H
# define NOTEBUFFER_H
# endif

# include "music_player_types.h"

# define NOTE_BUFFER_SIZE 256
# define DEFAULT_PUSHER_POS 0
# define DEFAULT_PULLER_POS 0
# define DEFAULT_ISEMPTY 1
# define DEFAULT_ISFULL 0

/**
 * Note buffer structure
 */
typedef struct {
    unsigned int pusher;
    unsigned int puller;
    int isempty;
    int isfull;
    mp_note buffer[NOTE_BUFFER_SIZE];
} note_buffer;

/**
 * Initializes a note buffer and returns it
 * @return the initialized note buffer
 */
note_buffer nb_init(void);

/**
 * Pushes an element into the note buffer
 * @param nb - the note buffer to push into
 * @param n - the note to push into the buffer
 */
void nb_push(note_buffer *nb, mp_note n);

/**
 * Pulls the next element from the note buffer
 * @param nb - the note buffer to pull from
 * @return the pulled note
 */
mp_note nb_pull(note_buffer *nb);

/**
 * Clears all values from the note buffer
 * @param nb - the note buffer to clear
 */
void nb_clear(note_buffer *nb);

/**
 * Determines whether a note buffer is empty or not
 * @param nb - the note buffer to analyze
 * @return One if the note buffer is empty, zero otherwise
 */
int nb_isempty(note_buffer *nb);

/**
 * Determines whether a note buffer is full or not
 * @param nb - the note buffer to analyze
 * @return One if the note buffer is full, zero otherwise
 */
int nb_isfull(note_buffer *nb);
