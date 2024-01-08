/// @file
/// @author  Danilo Alves de Lima
/// @date    decembre, 2018
/// @version $Id: ShMemBase.h 1 2018-12-07 08:35:10Z dalvesde $
/// @copyright Copyright (c) Seven Always - 2018. All rights reserved.
/// @brief Base class for shared memory objects
///
/// Detailed description.

#ifndef DEF_SHMEMBASE_H
#define DEF_SHMEMBASE_H

/// Base class for shared memory objects.
class ShMemBase
{
public:
    /// Ctor
    ShMemBase()
    {
    }

    /// Dtor
    virtual ~ShMemBase()
    {
    }

    /// Use this method to get the data of the shared memory
    virtual void *read() = 0; 

    /// Use this method to write data in shared memory
    virtual void write(void *data, int size, unsigned long offset = 0) = 0; 

    /// Use this method to wait the incoming of new data
    /// you can specify a timeout in ms to avoid infinite blocking or 0 (infinite)
    /// @returns @b true if new data available before the timeout, @b false otherwise
    virtual bool wait(unsigned long timeout = 0) = 0; 

    /// To lock the access to the memory
    virtual void lockMemory() = 0; 

    /// To unlock the access to the memory
    virtual void unlockMemory() = 0; 

#ifdef WIN32
    /// Return the event handle under Windows 
    /// @todo ... under Linux ? 
    virtual void * getEventIdentifier() = 0; 
#endif 
  
protected:
    /// @todo Documentation
    void * shMem_;

private:
};

#endif // DEF_SHMEMBASE_H
