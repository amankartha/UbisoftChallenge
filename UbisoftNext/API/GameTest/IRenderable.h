#pragma once

class IRenderable
{
public:
	virtual void Render(const Camera camera, bool isUI) = 0;
	virtual ~IRenderable() = default;
};
