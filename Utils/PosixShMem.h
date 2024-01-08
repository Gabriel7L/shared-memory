/// @file
/// @author  Danilo Alves de Lima
/// @date    decembre, 2018
/// @version $Id: ShMem.h 1 2018-12-07 08:35:10Z dalvesde $
/// @copyright Copyright (c) Seven Always - 2018. All rights reserved.
/// @brief Unix class for shared memory
///
/// Implement the shared memory access in Unix-like systems.

#ifndef DEF_POSIXSHMEM_H
#define DEF_POSIXSHMEM_H

#include <unistd.h>
#include <sys/mman.h> 		// Used for shared memory
#include <semaphore.h> 		// Used for semaphores

#include "ShMemBase.h"

/// @todo Documentation
class PosixShMem
        : public ShMemBase
{
public:
    /// @todo Documentation
    PosixShMem(const char * name, int size);
    /// @todo Documentation
    virtual ~PosixShMem();

    /// @todo Documentation
    virtual void *read();
    /// @todo Documentation
    virtual void read(void * mem, int size);
    /// @todo Documentation
    virtual void write(void *data, int size, unsigned long offset = 0);
    /// @todo Documentation
    virtual bool wait(unsigned long timeout = 0);
    /// @todo Documentation
    virtual void lockMemory();
    /// @todo Documentation
    virtual void unlockMemory();

private:
    
    // Shared memory
    void *shm_pt; 		// pointer
    const char *shm_name;	// shared memory name
    int shm_fd;			// file descriptor
	    
    // Semaphore
    sem_t *sem_pt;		// pointer
    char sem_name[255];		// shared memory name

};

#endif // DEF_POSIXSHMEM_H
