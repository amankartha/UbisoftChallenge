#pragma once
#include <cassert>
#include <vector>


template <typename T>
class RingBuffer
{
public:
	RingBuffer(int size)
	{
		if (size <= 0)
		{
			assert("Size cannot be 0");
		}
		else
		{
			m_buffer = new T[size + 1];
		}
		m_capacity = size+1;
		m_head = 0;
		m_tail = 0;
		m_size = 0;
	}

	~RingBuffer() { delete[] m_buffer; }

	void Push(const T& value)
	{
		m_buffer[m_tail] = value;
		if (m_size == m_capacity)
		{
			m_head = (m_head + 1) % m_capacity;
		}
		else
		{
			++m_size;
		}
		m_tail = (m_tail + 1) % m_capacity;
	}
	T Front() const
	{
		if (IsEmpty())
		{
			return nullptr;
		}
		return m_buffer[m_head];
	}
	T Back() const
	{
		if (IsEmpty())
		{
			return nullptr;
		}
		return m_buffer[(m_tail - 1 + m_capacity) % m_capacity];
	}

	void Pop()
	{
		if (IsEmpty())
		{
			return;
		}
		m_head = (m_head + 1) % m_capacity;
		--m_size;
	}
	bool IsEmpty() const
	{
		return m_size == 0;
	}
	bool IsFull() const
	{
		return m_size == m_capacity;
	}
	int Size() const
	{
		return m_size;
	}
	int Capacity() const
	{
		return m_capacity;
	}
	bool Contains(const T& value) const {
		if (IsEmpty()) return false;

		size_t current = m_head; 
		for (size_t i = 0; i < m_size; ++i) {
			if (m_buffer[current] == value) {
				return true; 
			}
			current = (current + 1) % m_capacity; 
		}
		return false; 
	}

	// Check if a sequence of elements exists in order in the buffer, think fighting games 
	bool ContainsSequence(const std::vector<T>& sequence) const {
		if (sequence.empty() || sequence.size() > m_size) return false;

		size_t current = m_head; 
		size_t seqIndex = 0; 

		for (size_t i = 0; i < m_size; ++i) {
			if (m_buffer[current] == sequence[seqIndex]) {
				++seqIndex; 
				if (seqIndex == sequence.size()) {
					return true; 
				}
			}
			else {
				seqIndex = 0; 
			}
			current = (current + 1) % m_capacity; 
		}

		return false; 
	}

private:
	T m_buffer[];
	int m_capacity;
	int m_size;
	int m_head;
	int m_tail;
};
