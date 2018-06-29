#include <memory>
#include "DXApp.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "SimpleMath.h"

#include "Sprite.h"

class TestApp : public DXApp
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp();

	bool Init() override;
	void Update(float deltatime) override;
	void Render(float deltatime) override;

private:
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	Sprite*									m_sprite;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
};

TestApp::TestApp(HINSTANCE hInstance) : DXApp(hInstance)
{
}

TestApp::~TestApp()
{
	Memory::SafeDelete(m_sprite);
}

bool TestApp::Init()
{
	if (!DXApp::Init())
		return false;

	m_spriteBatch.reset(new DirectX::SpriteBatch(m_pImmediateContext));
	m_spriteFont.reset(new DirectX::SpriteFont(m_pDevice, L"fonts/Arial.spritefont"));

	m_sprite = new Sprite(DirectX::SimpleMath::Vector2(100, 100));
	m_sprite->Load(m_pDevice, L"images/test.dds");

	return true;
}

void TestApp::Update(float deltatime)
{
	auto offset = 0.1;
	auto position = m_sprite->GetPosition();
	if (GetAsyncKeyState('D'))	// right
	{
		m_sprite->SetPostion(DirectX::SimpleMath::Vector2(position.x + offset, position.y));
	}
	if (GetAsyncKeyState('A'))	// left
	{
		m_sprite->SetPostion(DirectX::SimpleMath::Vector2(position.x - offset, position.y));
	}
	if (GetAsyncKeyState('S'))	// back
	{
		m_sprite->SetPostion(DirectX::SimpleMath::Vector2(position.x, position.y + offset));
	}
	if (GetAsyncKeyState('W'))	// forward
	{
		m_sprite->SetPostion(DirectX::SimpleMath::Vector2(position.x, position.y - offset));
	}
}

void TestApp::Render(float deltatime)
{
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);

	// Draw sprites, fonts, etc
	m_spriteBatch->Begin();
	{
		m_sprite->Draw(m_spriteBatch.get());
		m_spriteFont->DrawString(m_spriteBatch.get(), L"Hello", DirectX::SimpleMath::Vector2(300, 300));
	}
	m_spriteBatch->End();

	HR(m_pSwapChain->Present(0, 0));
}

//
// MAIN
//
int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	TestApp tApp(hInstance);
	if (!tApp.Init()) return 1;

	return tApp.Run();
}