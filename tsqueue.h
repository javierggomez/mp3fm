// Thread-safe queue with some additional data spaces to store information 
// related to sound files. Wraps a std::queue and makes it thread-safe.
// (C) 2013 Javier Garcia Gomez

#ifndef __TSQUEUE_H__
#define __TSQUEUE_H__
#include <queue>
#include <mutex>

#include "cscopedlock.h"

template <class T> class TSQueue {
private:
	std::mutex m_mutex;
	std::queue<T>* m_queue;
	bool m_eof;
	float m_samplerate;
public:
	TSQueue() {
		m_queue=new std::queue<T>();
		m_eof=false;
    }
	~TSQueue() {
		delete m_queue;
	}
	/* Checks if queue is empty */
	bool empty() {
		CScopedLock lock(m_mutex);
		return m_queue->empty();
	}
	/* Sets eof flag */
	void set_eof(bool eof) {
		CScopedLock lock(m_mutex);
		m_eof=eof;
	}
	/* Gets eof flag */
	bool eof() {
		CScopedLock lock(m_mutex);
		return m_eof;
	}
	/* Sets samplerate data space (float) */
	void set_samplerate(float samplerate) {
		CScopedLock lock(m_mutex);
		m_samplerate=samplerate;
	}
	/* Gets samplerate data space (float) */
	float samplerate() {
		CScopedLock lock(m_mutex);
		return m_samplerate;
	}
	/* Gets last element of queue */
	T& back() {
		CScopedLock lock(m_mutex);
		return m_queue->back();
	}
	/* Gets first element of queue */
	T& front() {
		CScopedLock lock(m_mutex);
		return m_queue->front();
	}
	/* Gets first element of queue, and removes it from the queue. Equivalent to calling TSQueue::front() followed by TSQueue::pop() */
	T next() {
		CScopedLock lock(m_mutex);
		T result=m_queue->front();
		m_queue->pop();
		return result;
	}
	/* Removes first element from queue */
	void pop() {
		CScopedLock lock(m_mutex);
		m_queue->pop();
	}
	/* Adds element to end of queue */
	void push(const T& element) {
		CScopedLock lock(m_mutex);
		m_queue->push(element);
	}
};

#endif
