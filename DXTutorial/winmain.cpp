#include <memory>
#include "DXApp.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "SimpleMath.h"

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
	ID3D11ShaderResourceView* m_pTexture;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
};

TestApp::TestApp(HINSTANCE hInstance) : DXApp(hInstance)
{
}

TestApp::~TestApp()
{
}

bool TestApp::Init()
{
	if (!DXApp::Init())
		return false;

	m_spriteBatch.reset(new DirectX::SpriteBatch(m_pImmediateContext));
	m_spriteFont.reset(new DirectX::SpriteFont(m_pDevice, L"fonts/Arial.spritefont"));
	
	HR(DirectX::CreateDDSTextureFromFile(m_pDevice, L"images/test.dds", nullptr, &m_pTexture));

	return true;
}

void TestApp::Update(float deltatime)
{

}

void TestApp::Render(float deltatime)
{
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);

	m_spriteBatch->Begin();
	// Draw sprites, fonts, etc

	m_spriteBatch->Draw(m_pTexture, DirectX::SimpleMath::Vector2(100,100));

	m_spriteFont->DrawString(m_spriteBatch.get(), L"Hello", DirectX::SimpleMath::Vector2(300, 300));

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