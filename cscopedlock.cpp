// Scoped mutex lock. Create an instance of this class at the beginning of a
// critical section, passing a shared mutex object to make the critical section
// thread safe.

#include <mutex>

#include "cscopedlock.h"

using namespace std;

CScopedLock::CScopedLock(std::mutex& mutex): m_mutex(mutex) {
	m_mutex.lock();
}
CScopedLock::~CScopedLock() {
	m_mutex.unlock();
}
