#include "Sprite.h"
#include "DXUtil.h"
#include "DDSTextureLoader.h"

Sprite::Sprite()
{
}

Sprite::Sprite(const Vector2 & position)
{
	m_Position = position;
	m_Alpha = 1.0f;
	m_Rotation = 0.0f;
	m_Scale = Vector2(1, 1);
	m_Tint = DirectX::Colors::White.v;
	m_AnimationDirection = kAnimatingUp;
}

Sprite::~Sprite()
{
	Memory::SafeRelease(m_pTexture);
	Memory::SafeRelease(m_pResource);
}

const Vector2 & Sprite::GetPosition() const
{
	return m_Position;
}

const Vector2 & Sprite::GetOrigin() const
{
	return m_Origin;
}

const Vector2 & Sprite::GetScale() const
{
	return m_Scale;
}

const Color & Sprite::GetTint() const
{
	return m_Tint;
}

const FLOAT & Sprite::GetAlpha() const
{
	return m_Alpha;
}

const FLOAT & Sprite::GetRotation() const
{
	return m_Rotation;
}

void Sprite::SetPostion(const Vector2 & position)
{
	m_Position = position;
}

void Sprite::SetOrigin(const Vector2 & origin)
{
	m_Origin = origin;
}

void Sprite::SetScale(const Vector2 & scale)
{
	m_Scale = scale;
}

void Sprite::SetTint(const Color & color)
{
	m_Tint = color;
}

void Sprite::SetAlpha(FLOAT alpha)
{
	m_Alpha = alpha;
}

void Sprite::SetRotation(FLOAT rotation)
{
	m_Rotation = rotation;
}

void Sprite::Load(ID3D11Device * device, const wchar_t * file)
{
	HR(DirectX::CreateDDSTextureFromFile(device, file, &m_pResource, &m_pTexture));

	
	Utility::GetTextureDim(m_pResource, &m_Width, &m_Height);

	m_Origin = Vector2(m_Width / 2.0f, m_Height / 2.0f);
	m_SourceRect.left = 0;
	m_SourceRect.top = 0;
	m_SourceRect.bottom = m_Height;
	m_SourceRect.right = m_Width;
}

void Sprite::Draw(DirectX::SpriteBatch * spriteBatch)
{
	spriteBatch->Draw(m_pTexture, m_Position, &m_SourceRect, m_Tint, m_Rotation, m_Origin, m_Scale, DirectX::SpriteEffects::SpriteEffects_None, 0.0f);
}

void Sprite::Animate()
{
	const float animationOFfset = 0.0001;

	if(m_AnimationDirection == kAnimatingUp)
	{
		m_Scale.x += animationOFfset;
		m_Scale.y += animationOFfset;
	}
	else
	{
		m_Scale.x -= animationOFfset;
		m_Scale.y -= animationOFfset;
	}

	if (m_Scale.x > 1.5)
		m_AnimationDirection = kAnimatingDown;
	else if (m_Scale.x < 1.0)
		m_AnimationDirection = kAnimatingUp;

}
