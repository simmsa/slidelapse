/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution-ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by-sa/3.0/
 */

#include <math.h>
#include "SineEase.h"

#if !defined(M_PI_2)
#define M_PI_2 1.57079632679489661923
#endif


/*
 * Ease in
 */

NUMBER SineEase::easeIn(NUMBER time_) const
{
	return -_change*cos(time_/_duration*M_PI_2)+_change;
}


/*
 * Ease out
 */

NUMBER SineEase::easeOut(NUMBER time_) const
{
	return _change*sin(time_/_duration*M_PI_2);
}


/*
 * Ease in and out
 */

NUMBER SineEase::easeInOut(NUMBER time_) const
{
	return -_change/2*(cos(M_PI*time_/_duration)-1);
}
