/**
  * @file note_buffer.c
  * @author Grant Wilk
  * @created 2/09/2020
  * @modified 2/09/2020
  * @brief a circular queue for buffering notes
  */

# include "note_buffer.h"

/**
 * Initializes a note buffer and returns it
 * @return the initialized note buffer
 */
note_buffer nb_init(void) {

    // create a note buffer with default values
    note_buffer nb = {
            .pusher = DEFAULT_PUSHER_POS,
            .puller = DEFAULT_PULLER_POS,
            .isempty = DEFAULT_ISEMPTY,
            .isfull = DEFAULT_ISFULL
    };

    return nb;
}

/**
 * Pushes an element into the note buffer
 * @param nb - the note buffer to push into
 * @param n - the note to push into the buffer
 */
void nb_push(note_buffer *nb, mp_note n) {

    // push the character into the queue then increment the pusher
    nb->buffer[(nb->pusher)++] = n;

    // if the pusher passes the end of the buffer, put it back at the start of the buffer
    if (nb->pusher == NOTE_BUFFER_SIZE) nb->pusher = 0;

    // set the full flag if the pusher moves to the same position as the puller
    nb->isfull = (nb->pusher == nb->puller);

    // clear the empty flag
    nb->isempty = 0;
}

/**
 * Pulls the next element from the note buffer
 * @param nb - the note buffer to pull from
 * @return the pulled note
 */
mp_note nb_pull(note_buffer *nb) {

    // pull the note out of the queue and increment the puller
    mp_note n = nb->buffer[(nb->puller)++];

    // if the pusher passes the end of the buffer, put it back at the start of the buffer
    if (nb->puller == NOTE_BUFFER_SIZE) nb->puller = 0;

    // set the empty flag if the puller moves to the same position as the pusher
    nb->isempty = (nb->puller == nb->pusher);

    // clear the full flag
    nb->isfull = 0;

    // return the note
    return n;
}

/**
 * Clears all values from the note buffer
 * @param nb - the note buffer to clear
 */
void nb_clear(note_buffer *nb) {
    nb->pusher = 0;
    nb->puller = 0;
}

/**
 * Determines whether a note buffer is empty or not
 * @param nb - the note buffer to analyze
 * @return One if the note buffer is empty, zero otherwise
 */
int nb_isempty(note_buffer *nb) {
    return nb->isempty;
}

/**
 * Determines whether a note buffer is full or not
 * @param nb - the note buffer to analyze
 * @return One if the note buffer is full, zero otherwise
 */
int nb_isfull(note_buffer *nb) {
    return nb->isfull;
}
