// Main program. Creates a shared TSQueue<short> queue for threads to pass samples,
// creates a decoder thread that usas mp32wav.h to decode MP3, get WAV samples and
// push them to the queue, and a player thread that reads and pops samples from the queue
// and plays them as FM at the specified frequency
// (C) 2013 Javier Garcia Gomez

#include <unistd.h>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <thread>

#include "tsqueue.h"
#include "mp32wav.h"
#include "libpifm.h"

#define FILENAME_LENGTH 256

using namespace std;

void help();

int main(int argc, char** argv) {
	char infile[FILENAME_LENGTH]="";
	double frequency=103.3;
	TSQueue<short>* stream=new TSQueue<short>();

	int c;
	int option_index=0;
	static option long_options[]=
	{
		{"frequency", required_argument, 0, 'f'},
		{"help", no_argument, 0, 'h'}
	};
	while ((c=getopt_long(argc, argv, "f:h:", long_options, &option_index))!=EOF) {
		switch (c) {
			case 'f':
				if ((!(stringstream(optarg) >> frequency))||(frequency<=0.0)) {
					cerr << "mp3fm: error: option -f requires a positive number or zero" << endl;
					return 1;
				}
				break;
			case 'h':
				help();
				return 0;
				break;
			
			case '?':
		    	switch (optopt) {
		    		case 'f':
			    	cerr << "mp3fm: error: option -" << optopt << " requires an argument" << endl;
				    break;
			    default:
			    	if (isprint (optopt)) {
	 	        	cerr << "mp3fm: error: Unknown option: -" << optopt << endl;
			    	} else {
	 	        	cerr << "mp3fm: error: Unknown option" << endl;
			    	}
			    }
			    return 1;
		}
	}
	if (optind<argc) {
		strncpy(infile, argv[optind], FILENAME_LENGTH);
	} else {
		cerr << "mp3fm: error: Input MP3 file must be provided as first argument" << endl;
		return 1;
	}

	thread mp32wav(run_decoder, infile, stream);
	thread wav2fm(run_fm, stream, frequency);

	mp32wav.join();
	wav2fm.join();
	return 0;

}

void help() {
	cout << "mp3fm - RPi MP3 FM player" << endl;
	cout << "mp3fm [-f FREQ] FILE" << endl;
	cout << endl;
	cout << "Modulates an MP3 FILE in FM and sends it through GPIO4 with a carrier frequency FREQ MHz (default 103.3 MHz). ";
	cout << "Input file must be an MP3 file, which may either be mono or stereo, and may have any samplerate. FM data is ";
	cout << "sent mono (sum of both channels if input is stereo) and with the same samplerate as input file." << endl;
	cout << endl;
	cout << "Options: " << endl;
	cout << "-f FREQ, --frequency FREQ: Sets the frequency of the output signal. Default is 103.3 MHz." << endl;
	cout << "-h, --help: Prints this help and exits." << endl;
}
