/**
  * @file music_player.c
  * @author Grant Wilk
  * @created 2/09/2020
  * @modified 2/10/2020
  * @brief an API for playing music using two piezo buzzers
  */

# include "music_player.h"
# include "piezo_driver.h"

/**
 * The queue of notes to be played
 */
note_buffer note_queue;


/**
 * Initializes the internal note buffer
 */
void mp_init(void) {
    mp_stop(ALL);
    note_queue = nb_init();
}

/**
 * Starts playing the notes currently queued in the internal note buffer
 */
void mp_play(void) {
    if (!nb_isempty(&note_queue)) {
        mp_note n = nb_pull(&note_queue);
        piezo_set(BUZZER0, n.duration, n.frequency);
        piezo_set(BUZZER1, n.dual_duration, n.dual_frequency);
        piezo_play(ALL);
    }
}

/**
 * Stops playing notes
 */
void mp_stop() {
    piezo_stop(ALL);
}

/**
 * Queues a note to play on the piezo buzzer
 * @param n - the note to queue
 */
void mp_add_note(mp_note * n) {

    // if there is room in the note queue
    if (!nb_isfull(&note_queue)) {

        // convert the note to keys in case its not already
        mp_conv_to_keys(n);

        // push the note into the note queue
        nb_push(&note_queue, *n);

    }
}

/**
 * Queues a song to play using the piezo buzzer
 * @param s - the song to queue
 */
void mp_add_song(mp_song * s) {
    int i = 0;
    while (s->notes[i].instrument != MP_INSTR_END) {
        mp_add_note(&(s->notes[i]));
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
 * Converts a non-keys note to a keys note
 * @param n - the note to convert
 * @return the converted note
 */
void mp_conv_to_keys(mp_note * n) {

    // convert instrument
    switch (n->instrument) {

        case MP_INSTR_HAT:
            n->instrument = MP_INSTR_KEYS;
            n->frequency = MP_INSTR_HAT_FREQ;
            n->duration = MP_INSTR_HAT_DURATION;
            break;

        case MP_INSTR_KEYS:
            // don't modify the note if it is already a keys note
            break;

        case MP_INSTR_KICK:
            n->instrument = MP_INSTR_KEYS;
            n->frequency = MP_INSTR_KICK_FREQ;
            n->duration = MP_INSTR_KICK_DURATION;
            break;

        case MP_INSTR_REST:
            n->instrument = MP_INSTR_KEYS;
            n->frequency = MP_INSTR_REST_FREQ;
            break;

        case MP_INSTR_SNARE:
            n->instrument = MP_INSTR_KEYS;
            n->frequency = MP_INSTR_SNARE_FREQ;
            n->duration = MP_INSTR_SNARE_DURATION;
            break;

        default:
            // default to an empty note if an invalid note is received
            n->instrument = MP_INSTR_KEYS;
            n->frequency = 0;
            n->duration = 0;
    }

    // convert dual instrument
    switch (n->dual_instrument) {

        case MP_INSTR_HAT:
            n->dual_instrument = MP_INSTR_KEYS;
            n->dual_frequency = MP_INSTR_HAT_FREQ;
            n->dual_duration = MP_INSTR_HAT_DURATION;
            break;

        case MP_INSTR_KEYS:
            // don't modify the note if it is already a keys note
            break;

        case MP_INSTR_KICK:
            n->dual_instrument = MP_INSTR_KEYS;
            n->dual_frequency = MP_INSTR_KICK_FREQ;
            n->dual_duration = MP_INSTR_KICK_DURATION;
            break;

        case MP_INSTR_REST:
            n->dual_instrument = MP_INSTR_KEYS;
            n->dual_frequency = MP_INSTR_REST_FREQ;
            break;

        case MP_INSTR_SNARE:
            n->dual_instrument = MP_INSTR_KEYS;
            n->dual_frequency = MP_INSTR_SNARE_FREQ;
            n->dual_duration = MP_INSTR_SNARE_DURATION;
            break;

        default:
            // default to an empty 1ms note if an invalid note is received
            n->dual_instrument = MP_INSTR_KEYS;
            n->dual_frequency = 0;
            n->dual_duration = 1;
    }

}

/**
 * TIM2 Interrupt Request Handler
 */
void TIM2_IRQHandler(void) {

    // if BUZZER1 is not busy and there is a note in the note buffer
    if (!piezo_busy(BUZZER1) && !nb_isempty(&note_queue)) {

        // set the next note
        mp_note n = nb_pull(&note_queue);
        piezo_set(BUZZER0, n.duration, n.frequency);
        piezo_set(BUZZER1, n.dual_duration, n.dual_frequency);

        // restart BUZZER1 because it has stopped
        piezo_play(BUZZER1);
    }

        // otherwise
    else {
        // stop BUZZER0
        piezo_stop(BUZZER0);
    }

}

/**
 * TIM5 Interrupt Request Handler
 */
void TIM5_IRQHandler(void) {

    // if BUZZER0 is not busy and there is a note in the note buffer
    if (!piezo_busy(BUZZER0) && !nb_isempty(&note_queue)) {

        // set the next note
        mp_note n = nb_pull(&note_queue);
        piezo_set(BUZZER0, n.duration, n.frequency);
        piezo_set(BUZZER1, n.dual_duration, n.dual_frequency);

        // restart BUZZER0 because it has stopped
        piezo_play(BUZZER0);
    }

        // otherwise
    else {
        // stop BUZZER1
        piezo_stop(BUZZER1);
    }

}