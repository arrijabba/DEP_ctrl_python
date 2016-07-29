/*
 * mainPy.cpp
 *
 *  Created on: Jul 28, 2016
 *      Author: arri-c
 */


#include <iostream>
#include <pigpio.h>
#include <chrono>


typedef std::chrono::nanoseconds ns;
typedef std::chrono::seconds s;

typedef struct
{
   uint32_t gpioOn;
   uint32_t gpioOff;
   uint32_t usDelay;
} gpioPulse_t;

ns interval; 

int main(int argc, char* argv[]) {

	if(argc < 3)
	{
		std::cout << "usage: ./mainPy freq_in_hz total_runtime\n";
		std::cout << "Minimum stable freq: ~4kHz\n";

		return 0;
	}

	s runtime = s(atoi(argv[2]));
 	double freq = atof(argv[1]);


	interval = ns((int)(((1/freq)*1000*1000)/256));
	std::cout << "interval: " << interval.count() << "\n";


	int i, wid[4];

	if (gpioInitialise()<0) return -1;

	gpioSetMode(2, PI_OUTPUT);
	gpioSetMode(3, PI_OUTPUT);
	gpioSetMode(4, PI_OUTPUT);
	gpioSetMode(5, PI_OUTPUT);
	gpioSetMode(6, PI_OUTPUT);
	gpioSetMode(7, PI_OUTPUT);

	gpioWrite(2, 1); // Starting clock signals high (falling edge trig)
	gpioWrite(3, 1);

////////////////////////////////////////////////////////////////////////////////////
// So here I assume that the counter has an input where you specify counting up/down
//
//
	gpioWrite(4, 1); 	// up
	gpioWrite(5, 0); 	// down
	gpioWrite(6, 1); 	// up
	gpioWrite(7, 0); 	// down

//
//
// Pins 4 and 5 are each counter's respective input, assuming I'm correct. Also mirroring this in pins 6/7
// cuz some chips have different ports for up/down
////////////////////////////////////////////////////////////////////////////////////


	printf("To start wave, press return.\n"); getchar();
	printf("Running...To stop early use CTRL+C\n");

	for (i=0; i<2; i++)
	{
	  gpioWaveAddGeneric(2, (gpioPulse_t[]) { {0, i+2, interval}, {i+2, 0, interval} }); // cou nters are on pins 1 and 2

	  wid[i] = gpioWaveCreate();
	}

////////////////////////////////////////////////////////////////////////////////////
//	Here, I'm initializing the counter on pin 3 to 255 so we dont have to manually put the value in.
//	Thus, we can start one up and one down for a 180 degree phase shift effect
//
//	Make sure the counter is set up to count up!

	gpioWaveChain((char []) {
	255, 0,                       // loop start
	wid[1]   					  // transmit waves on pin 3
	255, 1, 255, 0                // loop 255x 
	}, 8);

	gpioWrite(6,!(gpioRead(6))); //switching to down
	gpioWrite(7,!(gpioRead(7))); //switching to down
//
//  Use pins 6/7 for the counter on 3
/////////////////////////////////////////////////////////////////////////////////////

	//now we start

    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    while(std::chrono::steady_clock::now() - start_time < runtime)
    {
		gpioWaveChain((char []) {
		  	 255, 0,                       // loop start
		     wid[0], wid[1],   			   // transmit waves on pins 2 and 3
		     255, 1, 255, 0                // loop 255x 
		}, 8);


		gpioWrite(4,!(gpioRead(4))); //switching down/up
		gpioWrite(5,!(gpioRead(5))); //switching down/up
		gpioWrite(6,!(gpioRead(6))); //switching down/up
		gpioWrite(7,!(gpioRead(7))); //switching down/up
	}

	//end
	gpioTerminate();
}


