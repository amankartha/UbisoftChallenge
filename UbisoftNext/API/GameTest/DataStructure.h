#pragma once
#include <iostream>
#include <cassert>
/// <summary>
/// This is taken from https://gamedev.stackexchange.com/questions/33888/what-is-the-most-efficient-container-to-store-dynamic-game-objects-in  and converted to be used here
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
struct DataArray {

   


    struct Item {
        T item;
        int id; // (key << 16 | index) for allocated entries, (0 | nextFreeIndex) for free list entries
    };

    // Member variables
    Item* items = nullptr;
    int maxSize = 0;
    int maxUsed = 0;   // highest index ever allocated
    int count = 0;     // number of allocated items
    int nextKey = 1;   // [1..2^16] (don't let it == 0)
    int freeHead = -1; // index of the first free entry

    // Initialize the data array with a fixed size
    void Init(int size) {
        maxSize = size;
        items = new Item[maxSize];

        // Clear the array (setting up free list)
        Clear();
    }

   
    void Dispose() {
        delete items;
        items = nullptr;
        maxSize = 0;
        maxUsed = 0;
        count = 0;
        nextKey = 1;
        freeHead = -1;
    }

   
    void Clear() {
        for (int i = 0; i < maxSize; ++i) {
            items[i].id = 0; // Mark as free
        }
        freeHead = 0;

        maxUsed = 0;
        count = 0;
    }

    // Allocate a new item, returns a reference to the allocated item
    T& Alloc() {
        // Find a free slot (reuse from the free list if available)
        int index;
        if (freeHead != -1) {
            index = freeHead;
            freeHead = items[freeHead].id; // Move the free list head to the next available slot
        }
        else {
            assert(maxUsed < maxSize && "Max size exceeded");

            index = maxUsed++; // Allocate new space from the array
        }

        // Assign the ID and construct the item
        items[index].id = (nextKey++ << 16) | index;
        if (nextKey == 0) nextKey = 1; // Ensure the nextKey never becomes 0
        items[index].item = T(); // Construct default item (optional: use T(...))

        ++count;
        return items[index].item;
    }

    
    void Free(T& item) {
       
        int index = GetID(item) & 0xFFFF;
        if (index < 0 || index >= maxSize) return;

      
        items[index].id = freeHead;
        freeHead = index;

        --count;
    }

    
    int GetID(T& item) {
        for (int i = 0; i < maxUsed; ++i) {
            if (items[i].item == item) {
                return items[i].id;
            }
        }
        return -1; // Not found
    }

 
    T& Get(int id) {
        int index = id & 0xFFFF;
        assert(index >= 0 && index < maxSize && "Index out of bounds");
        return items[index].item;
    }

  
    T* TryToGet(int id) {
        int index = id & 0xFFFF;
        if (index < 0 || index >= maxSize || items[index].id == 0) {
            return nullptr; // Invalid or freed slot
        }
        return &items[index].item;
    }

   
    bool Next(T*& outItem) {
        for (int i = 0; i < maxUsed; ++i) {
            if ((items[i].id & 0xFFFF0000) != 0) {
                outItem = &items[i].item;
                return true;
            }
        }
        return false;
    }
};