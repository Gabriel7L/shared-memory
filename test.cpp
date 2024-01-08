#include "Containers/Thread_Example.h"
#include <iostream>

using namespace std;
using namespace NLMT;

int main(int argc, char*argv[])
{
    struct timespec tim, tim2;
    
    tim.tv_sec = 1;
    tim.tv_nsec = 0; 
    
	Thread_Example* t1 = new Thread_Example();
	t1->startActivity();
	
	while(true)
	{
		nanosleep(&tim , &tim2);
	}
	
	return 0;
}
