mp3fm
=====

Modulate and transmit MP3 files in FM at the carrier frequency of your choice through Raspberry Pi's GPIO4. Add a 20cm wire as an antenna to increase range.

COMPILATION

This program must be compiled on the Raspberry Pi and requires g++ and MAD (MPEG Audio Decoder) libraries to work. Install them on the Raspberry Pi:

sudo apt-get install g++ libmad0 libmad0-dev

and then run

make

from the program directory.

USAGE

Run the program with

sudo ./mp3fm [-f FREQ] FILE

where FREQ is the FM frequency in MHz (defaults to 103.3 MHz if -f is not specified) and FILE is the MP3 file to transmit. FM will be transmitted through GPIO4: add a 20cm wire as an antenna to increase range.
Example:

sudo ./mp3fm -f 88.5 test_sound.mp3

Run

./mp3fm -h

to to see a basic usage guide.

