#pragma once
#include <cassert>
#include <vector>

template <typename T>
class RingBuffer
{
public:
    explicit RingBuffer(size_t size)
        : m_capacity(size + 1), m_buffer(m_capacity), m_head(0), m_tail(0), m_size(0)
    {
        assert(size > 0 && "Size must be greater than 0");
    }

    void Push(const T& value)
    {
        m_buffer[m_tail] = value;
        if (IsFull())
        {
            m_head = (m_head + 1) % m_capacity; // Overwrite the oldest value
        }
        else
        {
            ++m_size;
        }
        m_tail = (m_tail + 1) % m_capacity;
    }
    //gets the oldest element
    T Front() const
    {
        //assert(!IsEmpty() && "Buffer is empty");
        if (IsEmpty())
        {
            return NULL;
        }
        return m_buffer[m_head];
    }
    //Gets the newest element
    T Back() const
    {
        //assert(!IsEmpty() && "Buffer is empty");
        if (IsEmpty())
        {
            return NULL;
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
        return m_size == (m_capacity - 1);
    }

    size_t Size() const
    {
        return m_size;
    }

    size_t Capacity() const
    {
        return m_capacity - 1; 
    }

    bool Contains(const T& value) const
    {
        if (IsEmpty()) return false;

        size_t current = m_head;
        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_buffer[current] == value)
            {
                return true;
            }
            current = (current + 1) % m_capacity;
        }
        return false;
    }

    bool ContainsSequence(const std::vector<T>& sequence) const
    {
        if (sequence.empty() || sequence.size() > m_size) return false;

        size_t current = m_head;
        size_t seqIndex = 0;

        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_buffer[current] == sequence[seqIndex])
            {
                ++seqIndex;
                if (seqIndex == sequence.size())
                {
                    return true;
                }
            }
            else
            {
                seqIndex = 0;
            }
            current = (current + 1) % m_capacity;
        }

        return false;
    }

private:
    size_t m_capacity;              // Total buffer size (including one extra space for head/tail distinction)
    std::vector<T> m_buffer;        // Internal storage
    size_t m_size;                  // Current number of elements
    size_t m_head;                  // Index of the oldest element
    size_t m_tail;                  // Index of the next insert position
};