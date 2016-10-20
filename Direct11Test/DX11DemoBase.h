
#pragma once


#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>


class Dx11DemoBase
{
public:
	Dx11DemoBase();
	~Dx11DemoBase();

	// D3D≥ı ºªØ
	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	void Shutdown();

	virtual bool Loadcontent();
	virtual void UnloadContent();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

protected:

	HINSTANCE m_hInstance;
	HWND m_hwnd;

	D3D_DRIVER_TYPE m_driverType;
	D3D_FEATURE_LEVEL m_featureLevel;

	ID3D11Device *m_d3dDevice;
	ID3D11DeviceContext *m_d3dContext;
	IDXGISwapChain *m_swapChain;
	ID3D11RenderTargetView *m_backBufferTarget;
};




