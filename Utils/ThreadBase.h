/*********************************************************************
//  created:    2019/02/04 - 11:30
//  filename:   ThreadBase.h
//
//  author:     Danilo Alves de Lima
//              Copyright Seven Always
// 
//  version:    $Id: $
//
//  purpose:    
*********************************************************************/

#ifndef THREADBASE_H
#define THREADBASE_H

#include <pthread.h>

/** Class to provide the posix thread base */
class ThreadBase
{
public:
	//============================= DEFAULT ELEMENTS ===============================================
    ThreadBase()
    {
	};
    virtual ~ThreadBase()
    {
	};

    virtual int run() = 0;

    virtual void stopActivity() = 0; /*!< to stop the processing thread */
    virtual void startActivity() = 0; /*!< to start the processing thread */
	//==============================================================================================

};

#endif // THREADBASE
