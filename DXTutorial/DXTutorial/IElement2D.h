#pragma once

#include "SpriteBatch.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class IElement2D
{
public:
	virtual ~IElement2D() {}

	virtual const Vector2& GetPosition() const = 0;
	virtual const Vector2& GetOrigin() const = 0;
	virtual const Vector2& GetScale() const = 0;
	virtual const Color& GetTint() const = 0;
	virtual const FLOAT& GetAlpha() const = 0;
	virtual const FLOAT& GetRotation() const = 0;
	
	virtual void SetPostion(const Vector2& position) = 0;
	virtual void SetOrigin(const Vector2& origin) = 0;
	virtual void SetScale(const Vector2& scale) = 0;
	virtual void SetTint(const Color& color) = 0;
	virtual void SetAlpha(FLOAT alpha) = 0;
	virtual void SetRotation(FLOAT rotation) = 0;

	virtual void Load(ID3D11Device* device, const wchar_t* file) = 0;

	virtual void Draw(DirectX::SpriteBatch * spriteBatch) = 0;
};