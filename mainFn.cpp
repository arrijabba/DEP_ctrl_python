/*
 * mainFn.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: arri-c
 */

//Summary of todo stuff



#include <iostream>
//#include <boost/chrono.hpp>
#include <wiringPi.h>
#include <chrono>


typedef std::chrono::nanoseconds ns;
typedef std::chrono::seconds s;

struct Electrode{

	int value; 						//0-63
	int type;  						//counting up/down
	int start_pin; 					//so we can find GPIO relatively for each electrode
};

struct Electrode e1; 
struct Electrode e2;
struct Electrode e3; 
struct Electrode e4;

ns interval; 
int debug = 0;
bool debug_on = false;
int run_count = 0; int run_count2 = 0; 
int accept_count = 0; 
int debug_count = 0; //misses
std::chrono::steady_clock::time_point timestamp;
std::chrono::steady_clock::time_point time_use;	//starting timestamp in ns since epoch

int main(int argc, char* argv[]) {
/*
 *  usage
 * ./dep freq threshold total_runtime (--debug)
 */

	if(argc > 4)
	{
		debug_on = true;	
	}
	else if(argc < 4)
	{
		std::cout << "usage: ./dep freq_in_hz threshold_in_ns total_runtime (--debug)\n";
		std::cout << "Minimum stable freq: ~700-800\n";
		std::cout << "Minimum threshold: 500nsn\n";
		std::cout << "Stable threshold: 750ns\n";

		return 0;
	}

	s runtime = s(atoi(argv[3]));
 	double freq = atof(argv[1]);

	wiringPiSetup();
	for(int i = 0; i < 28; i++)
	{
		pinMode (i, OUTPUT);
	}


    timestamp = std::chrono::steady_clock::now();

	interval = ns((int)(((1/freq)*1000*1000*1000)/256));
	std::cout << "interval: " << interval.count() << "\n";

	ns threshold = ns(interval.count()+atoi(argv[2]));

	e1.value = 0;
	e2.value = 63;   // 180 degrees out of phase
	e1.type = false; //going up
	e2.type = true;  //going down
	e1.start_pin = 0;
	e2.start_pin = 6;

	e3.value = 32;  //90 degrees out of phase
	e4.value = 32;  //270 degrees out of phase
	e3.type = true; //going up
	e4.type = false;  //going down
	e3.start_pin = 12;
	e4.start_pin = 18;
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();


    while(std::chrono::steady_clock::now() - start_time < runtime)
    {
    // while(run_count < )
    // {

    	time_use = std::chrono::steady_clock::now();	//starting timestamp in ns since epoch
		run_count++;
		run_count2++;

		if(time_use - timestamp > interval && time_use - timestamp < threshold)
		{
			//needs to be procedural bc function calls cost too much overhead
			//type true = up
			//type false = down


			if(e1.value == 0  || e1.value == 63)
			{
				e1.type = !e1.type;
			}
			if(e2.value == 0 || e2.value == 63)
			{
				e2.type = !e2.type;
			}
			if(e3.value == 0  || e3.value == 63)
			{
				e3.type = !e3.type;
			}
			if(e4.value == 0 || e4.value == 63)
			{
				e4.type = !e4.type;
			}

			if(e1.type == true)
			{
				e1.value = ++(e1.value);

				for(int i = 0; i < 6; i++)
				{
					int value = (e1.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e1.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e1.start_pin+i, LOW);
					}
				}
			}
			else
			{
				e1.value = --e1.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e1.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e1.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e1.start_pin+i, LOW);
					}
				}
			}

			digitalWrite (24, HIGH); //Write Enable 1



            //---------------------------//


			if(e2.type == true)
			{
				e2.value = ++e2.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e2.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e2.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e2.start_pin+i, LOW);
					}
				}
			}
			else
			{
				e2.value = --e2.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e2.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e2.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e2.start_pin+i, LOW);
					}
				}	
			}

			digitalWrite (25, HIGH); //Write Enable 2

			//---------------------------//

			if(e3.type == true)
			{
				e3.value = ++e3.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e3.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e3.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e3.start_pin+i, LOW);
					}
				}
			}
			else
			{
				e3.value = --e3.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e3.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e3.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e3.start_pin+i, LOW);
					}
				}	
			}

			digitalWrite (26, HIGH); //Write Enable 3

			//---------------------------//


			if(e4.type == true)
			{
				e4.value = ++e4.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e4.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e4.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e4.start_pin+i, LOW);
					}
				}
			}
			else
			{
				e4.value = --e4.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e4.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e4.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e4.start_pin+i, LOW);
					}
				}	
			}

			digitalWrite (27, HIGH); //Write Enable 4



			timestamp = std::chrono::steady_clock::now();
			accept_count++;

			//Disengage all Write En signals



			digitalWrite (24, LOW); //Write Enable 1
			digitalWrite (25, LOW); //Write Enable 2
			digitalWrite (26, LOW); //Write Enable 3
			digitalWrite (27, LOW); //Write Enable 4


		}
		else if(time_use - timestamp > interval)
		{
			//unacceptable miss
			//miss. time now is greater than latest run + interval
			//need this for testing accuracy
			//return true but log error

			//error is now() - timestamp - interval

			debug_count++;
			//still need to switch


			if(e1.value == 0  || e1.value == 63)
			{
				e1.type = !e1.type;
			}
			if(e2.value == 0 || e2.value == 63)
			{
				e2.type = !e2.type;
			}
			if(e3.value == 0  || e3.value == 63)
			{
				e3.type = !e3.type;
			}
			if(e4.value == 0 || e4.value == 63)
			{
				e4.type = !e4.type;
			}

			if(e1.type == true)
			{
				e1.value = ++(e1.value);

				for(int i = 0; i < 6; i++)
				{
					int value = (e1.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e1.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e1.start_pin+i, LOW);
					}
				}
			}
			else
			{
				e1.value = --e1.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e1.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e1.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e1.start_pin+i, LOW);
					}
				}
			}

			digitalWrite (24, HIGH); //Write Enable 1



            //---------------------------//


			if(e2.type == true)
			{
				e2.value = ++e2.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e2.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e2.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e2.start_pin+i, LOW);
					}
				}
			}
			else
			{
				e2.value = --e2.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e2.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e2.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e2.start_pin+i, LOW);
					}
				}	
			}

			digitalWrite (25, HIGH); //Write Enable 2

			//---------------------------//

			if(e3.type == true)
			{
				e3.value = ++e3.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e3.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e3.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e3.start_pin+i, LOW);
					}
				}
			}
			else
			{
				e3.value = --e3.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e3.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e3.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e3.start_pin+i, LOW);
					}
				}	
			}

			digitalWrite (26, HIGH); //Write Enable 3

			//---------------------------//


			if(e4.type == true)
			{
				e4.value = ++e4.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e4.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e4.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e4.start_pin+i, LOW);
					}
				}
			}
			else
			{
				e4.value = --e4.value;
				for(int i = 0; i < 6; i++)
				{
					int value = (e4.value >> i) & 1;
					if(value == 1)
					{
						//set this GPIO to high
						digitalWrite (e4.start_pin+i, HIGH);
					}
					else
					{
						//set this GPIO to zero
						digitalWrite (e4.start_pin+i, LOW);
					}
				}	
			}

			digitalWrite (27, HIGH); //Write Enable 4



			timestamp = std::chrono::steady_clock::now();
			accept_count++;

			//Disengage all Write En signals



			digitalWrite (24, LOW); //Write Enable 1
			digitalWrite (25, LOW); //Write Enable 2
			digitalWrite (26, LOW); //Write Enable 3
			digitalWrite (27, LOW); //Write Enable 4
		}
		else
		{
			//wait
		}

		//Below code slows program way down because of blocking/OS trapping/syscalls

		// if(run_count2 > 10000 && debug_on)
		// {
		// 		run_count2 = 0;
		//   	std::cout << "\r" << "Run " << run_count << " times. Miss " << debug_count << " times. Miss ratio: " << (double)debug_count/(double)run_count
		//   	<< " Acceptance ratio: " << (double)debug_count/(double)accept_count;
		//  }	
    }

    std::cout << "Miss " << debug_count << " times\n";
    std::cout << "good " << accept_count << " times\n";
    std::cout << "run " << run_count << " times\n";


}


