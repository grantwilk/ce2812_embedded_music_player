/**
  * @file
  * @author
  * @modified
  * @brief
  */

# ifndef MUSIC_H
# define MUSIC_H
# endif

# define MAX_SONG_LENGTH 256

# define MP_TEMPO 120
# define MP_BAR_DURATION   (60000 / (MP_TEMPO / 4))

/**
 * Music Player Note Durations
 */
# define MP_NOTE_WHOLE      (int) (MP_BAR_DURATION)
# define MP_NOTE_HALF      (int) (MP_BAR_DURATION / 2)
# define MP_NOTE_QUARTER   (int) (MP_BAR_DURATION / 4)
# define MP_NOTE_EIGTH     (int) (MP_BAR_DURATION / 8)
# define MP_NOTE_SIXTEENTH (int) (MP_BAR_DURATION / 16)

/**
 * Music Player Preset Instrument Frequencies
 */
# define MP_INSTR_HAT_FREQ 3520
# define MP_INSTR_KICK_FREQ 93
# define MP_INSTR_REST_FREQ 0
# define MP_INSTR_SNARE_FREQ 1000

/**
 * Music Player Preset Instrument Durations
 */
# define MP_INSTR_HAT_DURATION MP_NOTE_SIXTEENTH
# define MP_INSTR_KICK_DURATION MP_NOTE_EIGTH
# define MP_INSTR_SNARE_DURATION MP_NOTE_EIGTH

/**
 * Music Player Instruments
 */
typedef enum {
    MP_INSTR_HAT,
    MP_INSTR_KEYS,
    MP_INSTR_KICK,
    MP_INSTR_NONE,
    MP_INSTR_REST,
    MP_INSTR_SNARE,
    MP_INSTR_END
} mp_instrument;

/**
 * Music Player Note
 */
typedef struct {

    // main instrument
    mp_instrument instrument;
    int duration;
    int frequency;

    // dual instrument
    mp_instrument dual_instrument;
    int dual_duration;
    int dual_frequency;

} mp_note;

/**
 * Music Player Song
 */
typedef struct {
    mp_note *notes;
} mp_song;