#pragma once
#include <cassert>
#include <stack>
#include <vector>
#include <utility>
#include <optional>

// Concept to ensure T has required functions
template <typename T>
concept HasRequiredFunctions = requires(T obj) {
    { obj.Clear() } -> std::same_as<void>;
    { obj.Start() } -> std::same_as<void>;
    { obj.Update() } -> std::same_as<void>;
};

// Forward Declarations
class Game;

template <typename T>
class ObjectPool;

template <typename T>
struct PoolableObject {
    size_t m_index;
    T obj;
    ObjectPool<T>* m_pool;



    template <typename... Args>
    PoolableObject(ObjectPool<T>* pool, size_t index, Args&&... args)
        : m_pool(pool), m_index(index), obj(std::forward<Args>(args)...) {
    }
    PoolableObject(ObjectPool<T>* pool, size_t index)
        : m_pool(pool), m_index(index), obj() {
    }
};

/// <summary>
/// Creates an ObjectPool of Type T which will run Clear(), Start() and Update() functions if they exists in the type T
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
class ObjectPool {
public:
    ObjectPool(Game* gameInstance, size_t initialSize = 100) 
        : m_game_instance_(gameInstance) , activeIndices(0) {
        m_pool.reserve(initialSize);
        inUseFlags.resize(initialSize, false);
    }
    ObjectPool(size_t initialSize = 100)
        : m_game_instance_(nullptr) , activeIndices(0) {
        m_pool.reserve(initialSize);
        inUseFlags.resize(initialSize, false);
    }

    // Initialize the pool with objects using arguments 
    template <typename... Args>
    void InitializePool(size_t initialSize, Args&&... args) {
        for (size_t i = 0; i < initialSize; ++i) {
            EmplaceNewObject(i, std::forward<Args>(args)...);
        }
    }

    // Get an object from the pool, returns a PoolableObject not T directly
    template <typename... Args>
    PoolableObject<T>* Get(Args&&... args) {
        if (availableIndices.empty()) {
            ExpandPool(std::forward<Args>(args)...);
        }

        size_t index = availableIndices.top();
        availableIndices.pop();
        inUseFlags[index] = true;
        activeIndices.push_back(index);

        if constexpr (HasRequiredFunctions<T>) {
            m_pool[index].obj.Start();
        }

        return &m_pool[index];
    }



    // Get The T object directly from the pool, if the index is not in use it returns false 
    T* GetDirect(size_t index) {
        if (inUseFlags[index]) return &m_pool[index].obj;

        return nullptr;
    }

    // Release an object back to the pool
    void Release(size_t index) {
        if constexpr (HasRequiredFunctions<T>) {
            m_pool[index].obj.Clear();
        }

        availableIndices.push(index);
        inUseFlags[index] = false;
        activeIndices.erase(std::remove(activeIndices.begin(), activeIndices.end(), index), activeIndices.end());
    }

    size_t size() const { return m_pool.size(); }
    size_t availableCount() const { return availableIndices.size(); }

    // Apply a function to all in-use objects
    template <typename Func>
    void ApplyToEachInUse(Func func) {
        for (size_t i : activeIndices) {
            func(m_pool[i]);
        }
    }

    // Update all in-use objects   //TODO: this needs to be optimized
    void UpdateEachInUse() {
        if constexpr (!HasRequiredFunctions<T>) {
            return;
        }
        for (size_t i : activeIndices) {
            m_pool[i].obj.Update();
        }
    }

private:
    // Expand the pool with new objects 
    template <typename... Args>
    void ExpandPool(Args&&... args) {
        size_t currentSize = m_pool.size();
        size_t newSize = currentSize + (std::max)(currentSize / 2, size_t(1));
        m_pool.reserve(newSize);
        inUseFlags.resize(newSize, false);

        for (size_t i = currentSize; i < newSize; ++i) {
            EmplaceNewObject(i, std::forward<Args>(args)...);
        }
    }

    // Emplace a new object in the pool
    template <typename... Args>
    void EmplaceNewObject(size_t index, Args&&... args) {
        m_pool.emplace_back(this, index, std::forward<Args>(args)...);
        inUseFlags[index] = false;
        availableIndices.push(index);
    }

  /*  void ExpandPool() {
        size_t currentSize = m_pool.size();
        size_t newSize = currentSize + (std::max)(currentSize / 2, size_t(1));
        m_pool.reserve(newSize);
        inUseFlags.resize(newSize, false);

        for (size_t i = currentSize; i < newSize; ++i) {
            EmplaceNewObject(i);
        }
    }

    void EmplaceNewObject(size_t index) {
        m_pool.emplace_back(this, index);
        inUseFlags[index] = false;
        availableIndices.push(index);
    }*/


private:
    Game* m_game_instance_;
   
    std::vector<bool> inUseFlags;
    std::stack<size_t> availableIndices;
   
public:
    std::vector<size_t> activeIndices;
    std::vector<PoolableObject<T>> m_pool;
};