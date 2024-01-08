/// @author  Danilo Alves de Lima
/// @date    December, 2018

#include "PosixShMem.h"
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h> /* For O_* constants */
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <cstdio>

//////////////////////////////////////////////////////////////////////////
/// Constructor
PosixShMem::PosixShMem(const char * name, int size)
{  
	this->shm_name = name;
	strcpy(this->sem_name, "Semaphore_");
	strcat(this->sem_name, name);
	
	this->shm_pt = 0;
	this->sem_pt = 0;
	  
    // Check if shared memory is already opened
	if((this->shm_fd = shm_open(this->shm_name, O_RDWR, 0666)) == -1)
	{
		/* Create shared memory object and set its size */
		//	Permission flags
		//		Operation permissions 	Octal value
		//		Read by user 			00400
		//		Write by user 			00200
		//		Read by group 			00040
		//		Write by group 			00020
		//		Read by others 			00004
		//		Write by others			00002
		//		Examples:
		//			0666 Everyone can read and write
		if((this->shm_fd = shm_open(this->shm_name, O_CREAT | O_RDWR, 0666)) == -1)
		{
			perror("IPC error: shm_open");
			exit(1);
		}
		
		if (ftruncate(this->shm_fd, size) == -1)
		{
			perror("IPC error: ftruncate");
			exit(1);
		}
	}

	/* Map shared memory object */
	this->shm_pt = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, this->shm_fd, 0);
	if (this->shm_pt == MAP_FAILED)
	{
		perror("IPC error: mmap");
		exit(1);
	}


	// Check if the semaphore is already created
	if((this->sem_pt = sem_open(this->sem_name, O_RDWR, 0)) == SEM_FAILED)
	{
		// Create a semaphore object and init with 1
		//	Permission flags
		//		Operation permissions 	Octal value
		//		Read by user 			00400
		//		Write by user 			00200
		//		Read by group 			00040
		//		Write by group 			00020
		//		Read by others 			00004
		//		Write by others			00002
		//		Examples:
		//			0666 Everyone can read and write
		if((this->sem_pt = sem_open(this->sem_name, O_CREAT | O_RDWR, 0666, 1)) == SEM_FAILED)
		{
			perror("IPC error: sem_open");
			exit(1);
		}
	}

	
}

//////////////////////////////////////////////////////////////////////////
/// Destructor
PosixShMem::~PosixShMem()
{
    //--------------------------------
    //----- DETACH SHARED MEMORY -----
    //--------------------------------
    //Detach and delete
    if (shm_unlink(this->shm_name) == -1)
    {
	perror("IPC error: shm_unlink");
	//exit(EXIT_FAILURE);
    }
    
    //Delete the Semaphore
    //It's important not to unintentionally leave semaphores existing after program execution. It also may cause problems next time you run the program.
    if (this->sem_pt)
    {
	if(sem_close(this->sem_pt) == -1)
	    perror("IPC error: sem_close");
    }

}

//////////////////////////////////////////////////////////////////////////
/// Use this method to get the data of the shared memory
void * PosixShMem::read()
{
    return this->shm_pt;
}

//////////////////////////////////////////////////////////////////////////
/// Use this method to get a pointer to data of the shared memory
void PosixShMem::read(void * mem, int size)
{
    lockMemory(); 
    memcpy(mem,this->shm_pt,size); 
    unlockMemory(); 
}

//////////////////////////////////////////////////////////////////////////
/// Use this method to write data in shared memory. Offset is given in bytes
void PosixShMem::write(void * data, int size, unsigned long offset)
{
    this->lockMemory();
    uint32_t * dest = (uint32_t *) this->shm_pt + offset;

    memcpy(dest, data, size);
    this->unlockMemory();
}

//////////////////////////////////////////////////////////////////////////
/// Function that locks access to the shared memory
void PosixShMem::lockMemory()
{
	// Decrement semaphore
	if (sem_wait(this->sem_pt) == -1)		//Wait until free
	{
		perror("IPC error: sem_wait");
	}
}

//////////////////////////////////////////////////////////////////////////
/// Function that unlocks access to the shared memory
void PosixShMem::unlockMemory()
{
	// Increment semaphore
	if (sem_post(this->sem_pt) == -1)
	{
		perror("IPC error: sem_post");
	}
}

//////////////////////////////////////////////////////////////////////////
/// Use this method to wait the incoming of new data
/// you can specify a timeout in ms to avoid infinite blocking or 0 (infinite)
/// return true if new data available before the timeout or else false
bool PosixShMem::wait(unsigned long /*timeout*/)
{
    return true;
}
