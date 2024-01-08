#include "Thread_Example.h"
#include <sys/time.h>
#include <iostream>
#include "../Utils/road_time.h"
#include "nlmt_struct.h"

using namespace std;
using namespace NLMT;

Thread_Example::Thread_Example() 
{
	this->shmem_example = 0;	
    
	this->is_running = 0;
	
	this->THREAD_ALIVE = 0;
}

Thread_Example::~Thread_Example()
{
	if(this->shmem_example)
		delete this->shmem_example;
		
	this->shmem_example = 0;
}

void Thread_Example::stopActivity() 
{
    		
    if(this->THREAD_ALIVE)
    {
		
		this->THREAD_ALIVE = 0;
		
		this->tim3.tv_sec = 1;
		this->tim3.tv_nsec = 0; 
			
		while(this->is_running)
		{
			nanosleep(&this->tim3 , &this->tim4);
		}
    }
	
    if(this->shmem_example)
		delete this->shmem_example;
	    
    this->shmem_example = 0;
      
    
    std::cout << "[THREAD_EXAMPLE]: Thread stopped!\n";
}
    
void Thread_Example::startActivity()
{       
	
	shmem_example = new ShMem("SHMEN_EXAMPLE_NAME", sizeof(Timestamped_GPS_DATA));
			      
	int rc = pthread_create(&this->thread, NULL, this->start, (void*)this);
	if (rc) 
	{
		std::cout << "[THREAD_EXAMPLE]: Unable to create thread! " << rc << std::endl;
	}
}

void *Thread_Example::start(void* param) 
{
	
	Thread_Example *pto = (Thread_Example*)param;
	
	return (void*)(intptr_t)pto->run();
}

int Thread_Example::run() 
{
    this->is_running = 1;
    THREAD_ALIVE = 1;
    
    this->tim.tv_sec = 0;
    this->tim.tv_nsec = 1000000L;
         
    while (THREAD_ALIVE) 
    {
		Timestamped_GPS_DATA m_TEST_DATA;
		
		m_TEST_DATA.time = road_time();
			
		shmem_example->write(&m_TEST_DATA, sizeof(Timestamped_GPS_DATA));
		
		this->shmem_example->read(&m_TEST_DATA, sizeof(Timestamped_GPS_DATA));
		
		std::cout << m_TEST_DATA.time << "|"<<  sizeof(Timestamped_GPS_DATA)<< std::endl;
	
		nanosleep(&tim , &tim2);
    }
    
    this->is_running = 0;
    
    pthread_exit(NULL);
    
    return 1;
}
