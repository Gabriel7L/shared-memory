/// @file
/// @author  Danilo Alves de Lima
/// @date    decembre, 2018
/// @version $Id: ShMem.h 1 2018-12-07 08:35:10Z dalvesde $
/// @copyright Copyright (c) Seven Always - 2018. All rights reserved.
/// @brief Shared memory class
///
/// Inherits from Win32ShMem on Windows system and from PosixShMem on Unix-like systems.

#ifndef DEF_SHMEM_H
#define DEF_SHMEM_H

#ifdef WIN32
#   include "Win32ShMem.h"
/// Defines shared memory as a Windows shared memory
#   define ShMemType Win32ShMem
#else
#   include "PosixShMem.h"
/// Defines shared memory as a POSIX shared memory
#   define ShMemType PosixShMem
#endif

namespace NLMT {

/// Shared memory class.
///
/// Inherits from Win32ShMem on Windows system and from PosixShMem on Unix-like systems.
class ShMem
    : public ShMemType
{
public:
    /// Ctor of shared memory class.
    ///
    /// Creates a shared memory of size @b size and named @b name.
    /// If a shared memory with the name @b name already exists, than
    /// it will return object pointing to the same memory.
    /// If this existing memory space has a size smaller than @b size,
    /// a warning will be issued.
    ///
    /// @param name Name of the created shared memory space.
    /// @param size Size of the created shared memory space in [bytes].
    ShMem(const char * name, int size)
        : ShMemType(name, size)
    {
    }

    /// Dtor of shared memory class.
    ///
    /// Does nothing.
    ~ShMem()
    {
    }

protected:
private:
};

} // namespace seven

#endif // DEF_SHMEM_H
