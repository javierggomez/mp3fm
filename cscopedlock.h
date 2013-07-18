// Scoped mutex lock. Create an instance of this class at the beginning of a
// critical section, passing a shared mutex object to make the critical section
// thread safe.
// (C) 2013 Javier Garcia Gomez

#ifndef __CSCOPEDLOCK_H__
#define __CSCOPEDLOCK_H__

class CScopedLock {
private:
	// hide copy constructor
	CScopedLock(const CScopedLock& lock);
	std::mutex& m_mutex;
public:
	// initialize and acquire lock
	CScopedLock(std::mutex& mutex);
	// destroy and release lock
	~CScopedLock();
};

#endif
