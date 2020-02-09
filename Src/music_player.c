/**
  * @file music_player.c
  * @author Grant Wilk
  * @created 2/09/2020
  * @modified 2/09/2020
  * @brief A driver for playing music on the piezo buzzer.
  */

# include <stm32f446xx.h>
# include "music_player.h"
# include "note_buffer.h"

note_buffer note_queue;

/**
 * Initializes the internal note buffer
 */
void mp_init(void) {
    note_queue = nb_init();
}

/**
 * Starts playing the notes currently queued in the internal note buffer
 */
void mp_play(void) {
    // enable TIM4 interrupts
    TIM4->DIER |= TIM_DIER_CC1IE;
}

/**
 * Stops playing notes
 */
void mp_stop(void) {
    // disable TIM4 interrupts
    TIM4->DIER &= ~(TIM_DIER_CC1IE);
}

/**
 * Queues a note to play on the piezo buzzer
 * @param n - the note to queue
 */
void mp_add_note(note n) {
    if (!nb_isfull(&note_queue)) nb_push(&note_queue, n);
}

/**
 * Queues a song to play using the piezo buzzer
 * @param s - the song to queue
 */
void mp_add_song(song s) {

    int i = 0;

    // push notes into the note queue until we hit an end note
    while (s.notes[i].type != NOTE_END) {
        nb_push(&note_queue, s.notes[i]);
        i++;
    }

}

/**
 * Clears all notes from the note queue
 */
void mp_clear(void) {
    nb_clear(&note_queue);
}

/**
 * TIM4 Interrupt Request Handler
 */
void TIM4_IRQHandler(void) {

    // if note in note buffer
    if (!nb_isempty(&note_queue)) {
        // play the note
        piezo_play(nb_pull(&note_queue));
    }

    // otherwise
    else {
        // disable TIM4 interrupts
        TIM4->DIER &= ~(TIM_DIER_CC1IE);
    }

}