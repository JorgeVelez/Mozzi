/*
 * Line.h
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

#ifndef LINE_H_
#define LINE_H_

#include "Arduino.h"

/** For linear changes with a minimum of calculation at each step. For instance, you
can use Line to make an oscillator glide from one frequency to another,
pre-calculating the required phase increments for each end and then letting your
Line change the phase increment with only a simple addition at each step.
*/

template <class numType>
class Line
{
private:
	numType current_value;
	numType step_size;

public:
	/** Instantiates a Line. Use the template parameter to set the type of numbers you
	want to use. For example, Line <int> myline; makes a Line which uses ints.
	 */
	Line ()
	{
		;
	}

	/** Increments one step along the line, returning the next value.
	 */
	inline
	numType next()
	{
		current_value += step_size;
		return current_value;
	}

	/** Set the current value of the line. The Line will continue incrementing from this
	value using any previously calculated step size.
	 */
	inline
	void set(numType value)
	{
		current_value=value;
	}

	/** Given a target value and the number of steps to take on the way, this calculates
	the step size needed to get there from the current value.
	 */
	inline
	void set(numType targetvalue, numType num_steps)
	{
		step_size=(numType)(((float)(targetvalue-current_value)/num_steps));
	}

	/** Given a new starting value, target value and the number of steps to take on the way,
	this sets the step size needed to get there.
	 */
	inline
	void set(numType startvalue, numType targetvalue, numType num_steps)
	{
		set(startvalue);
		set(targetvalue, num_steps);
	}
};

#endif /* LINE_H_ */


