#pragma once
class Renderer : public Singleton<Renderer>
{
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;

public:
	Renderer();
	~Renderer();

	void Release();
	bool Init(int width = 1920, int height = 1080, bool windowMode = false);

	LPDIRECT3DDEVICE9 GetDevice() {
		return m_pDevice;
	}
	LPD3DXSPRITE GetSprite() {
		return m_pSprite;
	}

public:
	void Begin();
	void End();
};
