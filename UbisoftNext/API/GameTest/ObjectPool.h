#pragma once
#include <cassert>
#include <stack>
#include <vector>



//TODO: shud this be an interface instead???                 //Future Self IPoolable would need to use pointers instead of storing in an array directly
															//TODO: decouple this

/// ----------------------------------------------------------------------
/// https://www.youtube.com/watch?v=_doRiQS4GS8 <- video for concepts
/// ----------------------------------------------------------------------

/// this makes sure the type T has the functions clear and Start which are called on Release and Get respectively


template <typename T>
concept HasRequiredFunctions = requires( T obj) {
  
    { obj.Clear() } ->std::same_as<void> ;                                              
    { obj.Start() }->std::same_as<void>;
    { obj.Update() } ->std::same_as<void>;
};

template <typename T>
class ObjectPool;

template <typename T>
struct PoolableObject
{
    size_t m_index;
    T obj;
    ObjectPool<T>* m_pool;

    PoolableObject(Game* instance, ObjectPool<T>* pool, size_t index) : obj(instance)
    {
        static_assert(std::is_constructible<T, Game*>::value,
            "T must have a constructor that accepts Game* ");

        m_index = index;
        m_pool = pool;
    }


};

/// <summary>
/// Clear(), Start() , Update() functions declared in the T class will be called on Release, Get and Update
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
class ObjectPool {

   
public:
    ObjectPool(Game* gameInstance, size_t initialSize = 100) {
        m_game_instance_ = gameInstance;
        m_pool.reserve(initialSize);
        inUseFlags.resize(initialSize, false);
        for (size_t i = 0; i < initialSize; ++i) {
            m_pool.emplace_back(gameInstance,this,i);
            availableIndices.push(i);
        }
    }

    PoolableObject<T>* Get() {
        if (availableIndices.size() < 10) {
            ExpandPool(); // Expands the pool by 50% + 1
        }
        size_t index = availableIndices.top();
        availableIndices.pop();
        inUseFlags[index] = true;

        if constexpr (HasRequiredFunctions<T>)
        {
            m_pool[index].obj.Start();
        }
        
        return &m_pool[index];
    }

    void Release(size_t index) {
       // size_t index = object - m_pool.data(); // Calculate index using pointer arithmetic
       // size_t index = object->m_index;
    	//assert(index < m_pool.size() && "Object not from this pool");
      //  assert(inUseFlags[index] && "Object already released");

        if constexpr (HasRequiredFunctions<T>)
        {
            m_pool[index].obj.Clear();
        }

        availableIndices.push(index);
        inUseFlags[index] = false; 
    }

    size_t size() const { return m_pool.size(); }
    size_t SizeOFFlags() const { return inUseFlags.size(); }
    size_t availableCount() const { return availableIndices.size(); }

    // Iterate through in-use objects and call function on them, the function uses the object as its parameter
    template <typename Func>
    void ApplyToEachInUse(Func func)  {
        for (size_t i = 0; i < m_pool.size(); ++i) {
            if (inUseFlags[i]) {
                func(m_pool[i]);
            }
        }
    }

    // Iterate through in-use objects and Update them
    void UpdateEachInUse()  {
        if constexpr (HasRequiredFunctions<T>)
        {
            for (size_t i = 0; i < m_pool.size(); ++i) {
                if (inUseFlags[i]) {
                    m_pool[i].obj.Update();
                }
            }
        }
    }

private:
    void ExpandPool() {
        size_t currentSize = m_pool.size();
        size_t newSize = currentSize + (std::max)(currentSize / 2, size_t(1));
        m_pool.reserve(newSize);
        inUseFlags.resize(newSize, false);

        for (size_t i = currentSize; i < newSize; ++i) {
            m_pool.emplace_back(m_game_instance_, this, i);
            availableIndices.push(i);
        }
    }

private:
    Game* m_game_instance_;
    std::vector<PoolableObject<T>> m_pool;
    std::vector<bool> inUseFlags;
    std::stack<size_t> availableIndices;
};



