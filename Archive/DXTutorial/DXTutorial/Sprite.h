#pragma once
#include "IElement2D.h"

class Sprite : public IElement2D
{
public:
	Sprite();
	Sprite(const Vector2& position);
	~Sprite();

	// Inherited via IElement2D
	virtual const Vector2 & GetPosition() const override;
	virtual const Vector2 & GetOrigin() const override;
	virtual const Vector2 & GetScale() const override;
	virtual const Color & GetTint() const override;
	virtual const FLOAT & GetAlpha() const override;
	virtual const FLOAT & GetRotation() const override;

	virtual void SetPostion(const Vector2 & position) override;
	virtual void SetOrigin(const Vector2 & origin) override;
	virtual void SetScale(const Vector2 & scale) override;
	virtual void SetTint(const Color & color) override;
	virtual void SetAlpha(FLOAT alpha) override;
	virtual void SetRotation(FLOAT rotation) override;

	virtual void Load(ID3D11Device * device, const wchar_t * file) override;

	virtual void Draw(DirectX::SpriteBatch * spriteBatch) override;
	void Animate();

private:
	typedef enum AnimationDirectionType
	{
		kAnimatingUp,
		kAnimatingDown
	};

protected:
	ID3D11Resource *			m_pResource;
	ID3D11ShaderResourceView *	m_pTexture;
	UINT						m_Width;
	UINT						m_Height;
	RECT						m_SourceRect;
	Vector2						m_Position;
	Vector2						m_Origin;
	Vector2						m_Scale;
	Color						m_Tint;
	FLOAT						m_Alpha;
	FLOAT						m_Rotation;
	AnimationDirectionType		m_AnimationDirection;

};

