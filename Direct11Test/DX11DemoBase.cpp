
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

	RECT dimensions; // ���ڵĳߴ�

	// �ú�����ȡ���ڿͻ����Ĵ�С��
	// ע��һ�£����ڵĿͻ���Ϊ�����г����������˵���֮��ĵط���
	GetClientRect(hwnd, &dimensions);

	unsigned int width = dimensions.right - dimensions.left;  // �ͻ�����
	unsigned int height = dimensions.bottom - dimensions.top; // �ͻ�����


	// ����D3D�����б�(�оٿ��õ�����,���Ұ���Ч�ʸߵ�����, ��software�����������Ϊ�����Լ���д������)
	D3D_DRIVER_TYPE driverTypes[] = 
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE
	};

	// ��ʼ��d3d11���Եȼ�
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


