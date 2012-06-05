/*
 * DelayCuttlefish.h
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

#ifndef DELAY_CUTTLEFISH_H_
#define DELAY_CUTTLEFISH_H_

#include "Arduino.h"

class DelayCuttlefish
{

public:

	DelayCuttlefish(unsigned int UPDATE_RATE);


	inline
	void set(unsigned int millisToWait)
	{
		counter_start_value = ((long)millisToWait*1000)/micros_per_update;
	}


	inline
	void start()
	{
		counter = counter_start_value;
	}


	inline
	boolean ready()
	{
		return --counter<0;
	}


private:

	long counter; // long so even at a control rate of 2048 you can have >15seconds
	long counter_start_value;
	const unsigned int micros_per_update;

};


#endif /* DELAY_CUTTLEFISH_H_ */