#pragma once
#include <cassert>
#include <stack>
#include <vector>
#include <concepts>


//TODO: shud this be an interface instead???                 //Future Self IPoolable would need to use pointers instead of storing in an array directly
															//TODO: decouple this

/// ----------------------------------------------------------------------
/// https://www.youtube.com/watch?v=_doRiQS4GS8 <- video for concepts
/// ----------------------------------------------------------------------

/// this makes sure the type T has the functions clear and Start which are called on Release and Get respectively


template <typename T>
concept HasRequiredFunctions = requires(T obj) {
  
    { obj.Clear() } -> std::same_as<void>;                                              
    { obj.Start() } -> std::same_as<void>;
    { obj.Update() } -> std::same_as<void>;
};

/// <summary>
/// REQUIRES Clear(), Start() , Update() functions declared in the T class 
/// </summary>
/// <typeparam name="T"></typeparam>
template <HasRequiredFunctions T>
class ObjectPool {
public:
    ObjectPool(Game* gameInstance, size_t initialSize = 100) {
        m_game_instance_ = gameInstance;
        m_pool.reserve(initialSize * 2);
        inUseFlags.resize(initialSize, false);
        for (size_t i = 0; i < initialSize; ++i) {
            m_pool.emplace_back(gameInstance, this);
            availableIndices.push(i);
        }
    }

    T* Get() {
        if (availableIndices.empty()) {
            ExpandPool(); // Expands the pool by 50% + 1
        }
        size_t index = availableIndices.top();
        availableIndices.pop();
        inUseFlags[index] = true;
        m_pool[index].Start();
        return &m_pool[index];
    }

    void Release(T* object) {
        size_t index = object - m_pool.data(); // Calculate index using pointer arithmetic
        assert(index < m_pool.size() && "Object not from this pool");
        assert(inUseFlags[index] && "Object already released");
        m_pool[index].Clear();
        availableIndices.push(index);
        inUseFlags[index] = false; 
    }

    size_t size() const { return m_pool.size(); }
    size_t availableCount() const { return availableIndices.size(); }

    // Iterate through in-use objects and call function on them, the function uses the object as its parameter
    template <typename Func>
    void ApplyToEachInUse(Func func) const {
        for (size_t i = 0; i < m_pool.size(); ++i) {
            if (inUseFlags[i]) {
                func(m_pool[i]);
            }
        }
    }

    // Iterate through in-use objects and Update them
    void UpdateEachInUse() const {
        for (size_t i = 0; i < m_pool.size(); ++i) {
            if (inUseFlags[i]) {
               m_pool[i].Update();
            }
        }
    }

private:
    void ExpandPool() {
        size_t currentSize = m_pool.size();
        size_t newSize = currentSize * 1.5 + 1;
        m_pool.reserve(newSize);
        m_pool.resize(newSize);
        inUseFlags.resize(newSize, false);
        for (size_t i = currentSize; i < newSize; ++i) {
            m_pool.emplace_back(m_game_instance_, this);
            availableIndices.push(i);
        }
    }

private:
    Game* m_game_instance_;
    std::vector<T> m_pool;
    std::vector<bool> inUseFlags;
    std::stack<size_t> availableIndices;
};



