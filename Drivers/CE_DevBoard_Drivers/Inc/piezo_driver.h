/**
 * @file piezo_driver.h
 * @author Grant Wilk
 * @created 2/9/2020
 * @modified 2/9/2020
 * @brief a driver for playing tones on a piezo buzzer.
 */

#ifndef PIEZO_DRIVER_H
#define PIEZO_DRIVER_H
#endif

# ifndef MUSIC_H
# include "music_player_types.h"
# endif

/**
 * Piezo Buzzers
 */
typedef enum {
    BUZZER0,
    BUZZER1,
    ALL
}piezo_buzzer;

/**
 * Starts playing the note
 */
void piezo_play(piezo_buzzer buzzer);

/**
 * Stops playing the note
 */
void piezo_stop(piezo_buzzer buzzer);

/**
 * Sets the note for a piezo buzzer to play
 * @param buzzer - the buzzer being modified
 * @param duration - the duration of the note
 * @param frequency - the frequency of the note
 */
void piezo_set(piezo_buzzer buzzer, int duration, int frequency);

/**
 * Checks the busy flag of a buzzer
 * @param buzzer - the buzzer to check
 * @return the value of the buzzers busy flag
 */
int piezo_busy(piezo_buzzer buzzer);