
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

	unsigned int width  = dimensions.right - dimensions.left;  // 客户区宽
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
	D3D_FEATURE_LEVEL featureLeves[] = 
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};


	DXGI_SWAP_CHAIN_DESC swapChainDesc; 
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;  // 缓冲区数量
	swapChainDesc.BufferDesc.Width = width;   // 缓冲区宽
	swapChainDesc.BufferDesc.Height = height; // 缓冲区高
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 缓冲区格式
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;  // 刷新频率的分子
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // 刷新频率的分母
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // Means this swap chain will be used as output
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1; 
	swapChainDesc.SampleDesc.Quality = 0;

	unsigned int creationFlag = 0;
#ifdef _DEBUG
	creationFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT result;
	int nTotalDriverTypes = ARRAYSIZE(driverTypes);
	int nTotalFeatureLevels = ARRAYSIZE(featureLeves);

	// 找到一个可用的最优的设备
	for (int driver = 0; driver<nTotalDriverTypes; ++driver)
	{
		result = D3D11CreateDeviceAndSwapChain(
			0, driverTypes[driver], 0, creationFlag, featureLeves, nTotalFeatureLevels,
			D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_d3dDevice, &m_featureLevel, &m_d3dContext);
		if (SUCCEEDED(result))
		{
			m_driverType = driverTypes[driver];
			break;
		}
	}

	// 如果没找到设备就结束程序,并报错
	if (FAILED(result))
	{
		DXTRACE_MSG("Failed to create the Direct3D device!");
		return false;
	}


	ID3D11Texture2D *backBufferTexture;


	// 获取swap buff池,保存在backBufferTexture中
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
	if (FAILED(result))
	{
		DXTRACE_MSG("Failed to get the swap chain back buffer!");
		return false;
	}

	// 用get到的buff(backBufferTexture)创建渲染目标,并保存在全局bufferTargetView中
	result = m_d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &m_backBufferTarget);

	if(backBufferTexture)
	{  // 引用计数-1
		backBufferTexture->Release();
	}

	if (FAILED(result))
	{
		DXTRACE_MSG("Failed to create the render target view!");
		return false;
	}

	// 将渲染目标绑定到管线的输出合并阶段
	m_d3dContext->OMSetRenderTargets(1, &m_backBufferTarget, 0);

	//设置视口
	D3D11_VIEWPORT viewPort;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	m_d3dContext->RSSetViewports(1, &viewPort);

	return Loadcontent();
}

void Dx11DemoBase::Shutdown()
{
	if (m_backBufferTarget)  m_backBufferTarget->Release();
	if (m_swapChain) m_swapChain->Release();
	if (m_d3dContext) m_d3dContext->Release();
	if (m_d3dDevice) m_d3dDevice->Release();

	m_d3dDevice = NULL;
	m_d3dContext = NULL;
	m_swapChain = NULL;
	m_backBufferTarget = NULL;
}

bool Dx11DemoBase::Loadcontent()
{
	// override with demo specifics, if any ...
	return true;
}

void Dx11DemoBase::UnloadContent()
{
	// Override with demo specifics, if any...
}

