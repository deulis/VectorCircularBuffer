#include "VectorCircularBuffer.h"

VectorCircularBuffer::VectorCircularBuffer()
{
	init();
}

VectorCircularBuffer::~VectorCircularBuffer()
{
}

void VectorCircularBuffer::init(void)
{
	head_ = 0;
	tail_ = 0;
}

bool VectorCircularBuffer::put(std::vector<unsigned char> item)
{
	if (is_full())
		return false;

	pthread_mutex_lock(&mutex_);
	buf_[(head_++) & Buffer_MASK] = item;
	pthread_mutex_unlock(&mutex_);

	return true;
}

bool VectorCircularBuffer::get(std::vector<unsigned char>* item)
{
	if (is_empty())
		return false;

	pthread_mutex_lock(&mutex_);
	*item = buf_[(tail_++) & Buffer_MASK];
	pthread_mutex_unlock(&mutex_);

	return true;
}

void VectorCircularBuffer::reset(void)
{
	//set head_ = tail_ to reset the buffer
	pthread_mutex_lock(&mutex_);
	head_ = tail_;

	//Clear all the data for all item
	for (std::vector<unsigned char>& v : buf_)
	{
		v.clear();
		v.shrink_to_fit();
	}
	pthread_mutex_unlock(&mutex_);
}

bool VectorCircularBuffer::is_empty(void)
{
	//if head and tail are equal, the buffer is empty
	return head_ == tail_;
}

bool VectorCircularBuffer::is_full(void)
{
	//If tail is ahead the head by 1, the buffer is full
	return ((head_ + 1) & Buffer_MASK) == (tail_ & Buffer_MASK);
}

size_t VectorCircularBuffer::len(void)
{
	return head_ - tail_;
}

size_t VectorCircularBuffer::available(void)
{
	return  Buffer_SIZE - (head_ - tail_);
}


