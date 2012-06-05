/*
 * CuttlefishGuts.h
 *
 * Copyright 2012 unbackwards@gmail.com.
 *
 * This file is part of Cuttlefish.
 *
 * Cuttlefish is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cuttlefish is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cuttlefish.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CUTTLEFISHGUTS_H_
#define CUTTLEFISHGUTS_H_

#include "Arduino.h"
#include "TimerOne.h"
#include "TimerTwo.h"


#define AUDIO_CHANNEL_1_PIN 9 /**< Digital pin 9 is the pwm audio output pin.  For now there is only one channel. */
#define AUDIO_CHANNEL_1_OUTPUT_REGISTER OCR1A /**< Used internally.  If there was a channel 2, it would be OCR1B.*/

/** Set digital pin 13 to output for testing timing with an oscilloscope.*/
#define SET_PIN13_OUT	(DDRB = DDRB | B00100000)
/** Set pin 13 high for testing timing with an oscilloscope.*/
#define SET_PIN13_HIGH 	(PORTB = PORTB | B00100000)
/** Set pin 13 low for testing timing with an oscilloscope.*/
#define SET_PIN13_LOW	(PORTB = B00000000)

/** The AUDIO_RATE is fixed at 16384 Hz for now. This is a compromise between the
sample rate (interrupt rate) and sample bitdepth (pwm width), which are
interdependent due to the way pulse wave modulation is used to generate the
sound output. With the AUDIO_RATE at 16384, the sample resolution is 488, which
provides some headroom above the 8bit table resolution currently used by the
oscillators. You can look at the TimerOne library for more info about how
interrupt rate and pwm resolution relate.
*/

// maybe 20,24 or 28k-ish later with combos of pow2
#define AUDIO_RATE 16384

#if AUDIO_RATE == 16384
#define AUDIO_RATE_AS_LSHIFT 14 /**< Used internally for audio-rate optimisation.*/

/** This is the maximum sample resolution. 8 bit or 256 is usually fine but
there might be times where the extra headroom is useful. Use powers of two in
audio calculations and use right shifts for divisions where possible. Also, in
tests while writing Cuttlefish, shifts on byte boundaries seem to work fastest.
For example, >> 8 is faster than >> 4. Test your timings where possible, using
an oscilloscope with setPin13High() and setPin13Low() around you test code.
*/

#define AUDIO_PWM_RESOLUTION 488 // from Timer1.pwmPeriod calculated for interrupt rate 16384
/**< Used internally to put the 0-biased generated audio into the right range for PWM output.*/
#define AUDIO_BIAS 244
#endif


#define FIXMATH_OPTIMIZE_8BIT /** libfixmath option */


void startCuttlefish(unsigned int control_rate_hz)
;
void updateControl();
int updateAudio();
void audioHook();
static void outputAudio();


#endif /* CUTTLEFISHGUTS_H_ */
