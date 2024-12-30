#pragma once

class GameObject;

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute(GameObject& go) = 0;
	virtual void Undo(GameObject& go) = 0;
};

