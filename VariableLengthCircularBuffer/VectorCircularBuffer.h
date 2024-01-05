#pragma once

/*

2024-01-04
Eng. Deulis A. Pelegrin Jaime
*/

#include <cstdio>
#include <thread>
#include <vector>

#define Buffer_SIZE 64 //MUST BE POWER OF 2
#define Buffer_MASK (Buffer_SIZE-1)

class VectorCircularBuffer
{
public:
	VectorCircularBuffer();
	~VectorCircularBuffer();

	/// <summary>
	/// Don't need to call this method, this method is called in the constructor.
	/// </summary>
	void init(void);

	/// <summary>
	/// Add an item to the buffer
	/// </summary>
	/// <returns>Return true if the item was added to the buffer</returns>
	bool put(std::vector<unsigned char> item);

	/// <summary>
	/// Retrie an item.
	/// </summary>
	/// <returns>If the return is false the item was not recovered</returns>
	bool get(std::vector<unsigned char>* item);

	/// <summary>
	/// Reset the buffer and clear all data from each item
	/// </summary>
	void reset(void);

	/// <summary>
	/// Retur true if the buffer is empty
	/// </summary>
	bool is_empty(void);

	/// <summary>
	/// Return true if the buffer is full
	/// </summary>
	bool is_full(void);

	/// <summary>
	/// Return the quantity of items stored in the buffer
	/// </summary>
	size_t len(void);

	/// <summary>
	/// Return the available capacity 
	/// </summary>
	size_t available(void);

private:
	pthread_mutex_t mutex_ = PTHREAD_MUTEX_INITIALIZER;
	std::vector<unsigned char> buf_[Buffer_SIZE];
	size_t head_ = 0;
	size_t tail_ = 0;
};

