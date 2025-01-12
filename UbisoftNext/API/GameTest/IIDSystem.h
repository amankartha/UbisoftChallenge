#pragma once
#include <cassert>
#include <queue>



class IIDSystem
{
public:
    int GenerateID() {
        if (!m_freeIDs.empty()) {
            int id = m_freeIDs.front();
            m_freeIDs.pop();
            return id;
        }

        assert(m_nextID < m_max_ID && "Max ID Limit reached");
     
        return m_nextID++;
    }

    void ReleaseID(int id) {
        assert(id < m_nextID && "Invalid ID: ID must have been previously generated.");
        m_freeIDs.push(id);
    }

   
    void Reset() {
        m_nextID = 0;
        std::queue<int> emptyQueue;
        std::swap(m_freeIDs, emptyQueue); 
    }

protected:
    IIDSystem() = default;
    virtual ~IIDSystem() = default;
    int m_max_ID = 1000;
private:
    int m_nextID = 0;
    std::queue<int> m_freeIDs;
};


