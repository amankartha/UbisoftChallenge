#pragma once


class ObjectPool;


/// <summary>
/// Currently Unused
/// </summary>
class IPoolable
{
public:
	virtual ~IPoolable() {}
	virtual void Update() = 0;
	virtual void Clear() = 0;
	virtual void Start() = 0;
	virtual void SetPool(ObjectPool& pool) = 0;
};
