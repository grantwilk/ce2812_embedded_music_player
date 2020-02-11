/**
 * @file piezo_driver.h
 * @author Grant Wilk
 * @created 2/09/2020
 * @modified 2/10/2020
 * @brief a driver for playing tones on two piezo buzzers
 */

# include <stm32f446xx.h>
# include "piezo_driver.h"

# define TIM2_FREQ 1000 // Hz
# define TIM3_FREQ 40000 // Hz
# define TIM4_FREQ 40000 // Hz
# define TIM2_FREQ 1000 // Hz

static int BUZZER0_BUSY = 0;
static int BUZZER1_BUSY = 0;

/**
 * Starts playing the note
 */
void piezo_play(piezo_buzzer buzzer) {

    // switch on buzzer to enable timers
    switch (buzzer) {

        case BUZZER0:
            // enable TIM2 interrupts
            TIM2->DIER |= TIM_DIER_CC1IE;
            // enable TIM2 and TIM3 count
            TIM2->CR1 |= TIM_CR1_CEN;
            TIM3->CR1 |= TIM_CR1_CEN;
            // set BUZZER0 busy flag
            BUZZER0_BUSY = 1;
            break;
        case BUZZER1:
            // enable TIM5 interrupts;
            TIM5->DIER |= TIM_DIER_CC1IE;
            // enable TIM4 and TIM5 count
            TIM4->CR1 |= TIM_CR1_CEN;
            TIM5->CR1 |= TIM_CR1_CEN;
            // set BUZZER1 busy flag
            BUZZER1_BUSY = 1;
            break;
        case ALL:
            // enable TIM2 and TIM5 interrupts;
            TIM2->DIER |= TIM_DIER_CC1IE;
            TIM5->DIER |= TIM_DIER_CC1IE;
            // enable TIM2-TIM5 count
            TIM2->CR1 |= TIM_CR1_CEN;
            TIM3->CR1 |= TIM_CR1_CEN;
            TIM4->CR1 |= TIM_CR1_CEN;
            TIM5->CR1 |= TIM_CR1_CEN;
            // set BUZZER1 and BUZZER2 busy flag
            BUZZER0_BUSY = 1;
            BUZZER1_BUSY = 1;
            break;
        default:
            // do nothing if we receive an invalid value
            break;
    }

}

/**
 * Stops playing the note
 */
void piezo_stop(piezo_buzzer buzzer) {

    // switch on buzzer to disable timers
    switch (buzzer) {

        case BUZZER0:
            // disable TIM2 and TIM3 count
            TIM2->CR1 &= ~(TIM_CR1_CEN);
            TIM3->CR1 &= ~(TIM_CR1_CEN);
            // disable TIM2 interrupts
            TIM2->DIER &= ~(TIM_DIER_CC1IE);
            // clear BUZZER0 busy flag
            BUZZER0_BUSY = 0;
            break;

        case BUZZER1:
            // disable TIM4 and TIM5 count
            TIM4->CR1 &= ~(TIM_CR1_CEN);
            TIM5->CR1 &= ~(TIM_CR1_CEN);
            // disable TIM5 interrupts
            TIM5->DIER &= ~(TIM_DIER_CC1IE);
            // clear BUZZER1 busy flag
            BUZZER1_BUSY = 0;
            break;

        case ALL:
            // disable TIM2-TIM4 count
            TIM2->CR1 &= ~(TIM_CR1_CEN);
            TIM3->CR1 &= ~(TIM_CR1_CEN);
            TIM4->CR1 &= ~(TIM_CR1_CEN);
            TIM5->CR1 &= ~(TIM_CR1_CEN);
            // disable TIM2 and TIM5 interrupts
            TIM2->DIER &= ~(TIM_DIER_CC1IE);
            TIM5->DIER &= ~(TIM_DIER_CC1IE);
            // clear BUZZER0 and BUZZER1 busy flags
            BUZZER0_BUSY = 0;
            BUZZER1_BUSY = 0;
            break;

        default:
            // do nothing if we receive an invalid value
            break;

    }

}

/**
 * Sets the note for the piezo buzzer to play
 * @param duration - the duration of the main note
 * @param frequency - the frequency of the main note
 * @param dual_duration - the duration of the dual note
 * @param dual_frequency - the frequency of the dual note
 */
void piezo_set(piezo_buzzer buzzer, int duration, int frequency) {

    // switch on buzzer to set duration and frequency
    switch (buzzer) {

        case BUZZER0:
            // set TIM2 and TIM3 count
            TIM2->CNT = 0;
            TIM3->CNT = 0;
            // clear capture/compare interrupt flag on TIM2
            TIM2->SR &= ~(TIM_SR_CC1IF);
            // set TIM3 frequency
            TIM3->ARR = TIM3_FREQ / (frequency * 2);
            // set TIM2 duration
            TIM2->ARR = duration;
            break;

        case BUZZER1:
            // clear TIM4 and TIM5 count
            TIM4->CNT = 0;
            TIM5->CNT = 0;
            // clear capture/compare interrupt flag on TIM5
            TIM5->SR &= ~(TIM_SR_CC1IF);
            // set TIM4 frequency
            TIM4->ARR = TIM4_FREQ / (frequency * 2);
            // set TIM5 duration
            TIM5->ARR = duration;
            break;

        case ALL:
            // set TIM2-TIM5 count
            TIM2->CNT = 0;
            TIM3->CNT = 0;
            TIM4->CNT = 0;
            TIM5->CNT = 0;
            // clear capture/compare interrupt flag on TIM2 and TIM5
            TIM2->SR &= ~(TIM_SR_CC1IF);
            TIM5->SR &= ~(TIM_SR_CC1IF);
            // set TIM3 and TIM4 frequency
            TIM3->ARR = TIM3_FREQ / (frequency * 2);
            TIM4->ARR = TIM4_FREQ / (frequency * 2);
            // set TIM2 and TIM5 duration
            TIM2->ARR = duration;
            TIM5->ARR = duration;
            break;

        default:
            // do nothing if we receive an invalid value
            break;

    }

}

/**
 * Checks the busy flag of a buzzer
 * @param buzzer - the buzzer to check
 * @return the value of the buzzers busy flag
 */
int piezo_busy(piezo_buzzer buzzer) {

    // switch on buzzer and return the respective busy flag
    switch (buzzer) {

        case BUZZER0:
            return BUZZER0_BUSY;

        case BUZZER1:
            return BUZZER1_BUSY;

        case ALL:
            // return true if any busy flags are set
            return BUZZER0_BUSY || BUZZER1_BUSY;

        default:
            // default to false
            return 0;
    }

}