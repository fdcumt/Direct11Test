
#include "DX11DemoBase.h"



Dx11DemoBase::Dx11DemoBase() :
m_driverType(D3D_DRIVER_TYPE_NULL),
m_featureLevel(D3D_FEATURE_LEVEL_11_0),
m_d3dDevice(nullptr),
m_d3dContext(nullptr),
m_swapChain(nullptr),
m_backBufferTarget(nullptr)
{
}

Dx11DemoBase::~Dx11DemoBase()
{
	Shutdown();
}

bool Dx11DemoBase::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	m_hInstance = hInstance;
	m_hwnd = hwnd;

	RECT dimensions; // 窗口的尺寸

	// 该函数获取窗口客户区的大小。
	// 注意一下：窗口的客户区为窗口中除标题栏、菜单栏之外的地方。
	GetClientRect(hwnd, &dimensions);

	unsigned int width = dimensions.right - dimensions.left;  // 客户区宽
	unsigned int height = dimensions.bottom - dimensions.top; // 客户区高


	// 设置D3D驱动列表(列举可用的驱动,并且按照效率高低排列, 把software放在最后是因为那是自己编写的驱动)
	D3D_DRIVER_TYPE driverTypes[] = 
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE
	};

	// 初始化d3d11特性等级
	D3D_FEATURE_LEVEL m_featureLeve[] = 
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};


	DXGI_SWAP_CHAIN_DESC swapChainDesc; 
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;




}


