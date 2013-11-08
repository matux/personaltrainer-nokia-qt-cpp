//
//  SILock.cpp
//  SILock
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#include "SILock.h"

SILock::SILock(QMutex &mutex)
    :m_mutex(mutex),
     m_locked(true)
{
    m_mutex.lock();
}

SILock::~SILock()
{
    m_mutex.unlock();
}
