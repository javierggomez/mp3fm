// Modification of "pifm" code, created by Oliver Mattos and Oskar Weigl under GPL
// ( http://icrobotics.co.uk/wiki/index.php/Turning_the_Raspberry_Pi_Into_an_FM_Transmitter )
// Plays FM from the samples it gets from a TSQueue<short> queue. Intended to be called 
// concurrently with another thread that introduces samples in the queue.

#ifndef __LIBPIFM_H__
#define __LIBPIFM_H__
#include "tsqueue.h"

void run_fm(TSQueue<short>* stream, double freq=103.3);
#endif