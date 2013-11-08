//
//  SILock.h
//  SILock
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#ifndef SILOCK_H
#define SILOCK_H

#include <QMutex>

#define synchronize(M) SILock M##_lock(M);
#define synchronized(M) for( SILock M##_lock(M); M##_lock; M##_lock.unlock() )

/**
 * RAII implementation of Mutex lock.
 *
 *  Requires QMutex but can use any standard Mutex implementation.
 *
 */
class SILock
{
public:
    explicit SILock(QMutex &);
    ~SILock();

    // Report the state of locking when used as boolean
    inline operator bool () const { return m_locked; }
    // Unlock
    inline void unlock() { m_locked = false; }

private:
    //SILock(const SILock &);
    //SILock const &operator =(const SILock &);

    QMutex &m_mutex;
    bool m_locked;

};

#endif // SILOCK_H
