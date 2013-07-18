// Header file for modified version of madlld.c "mp32wav.cpp"

#ifndef __MP32WAV_H__
#define __MP32WAV_H__

#include "tsqueue.h"

int run_decoder(const char* filename, TSQueue<short>* outputStream);
#endif