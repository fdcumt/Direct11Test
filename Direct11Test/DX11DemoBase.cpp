
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

	unsigned int width  = dimensions.right - dimensions.left;  // �ͻ�����
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
	D3D_FEATURE_LEVEL featureLeves[] = 
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};


	DXGI_SWAP_CHAIN_DESC swapChainDesc; 
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;  // ����������
	swapChainDesc.BufferDesc.Width = width;   // ��������
	swapChainDesc.BufferDesc.Height = height; // ��������
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ��������ʽ
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;  // ˢ��Ƶ�ʵķ���
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // ˢ��Ƶ�ʵķ�ĸ
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

	// �ҵ�һ�����õ����ŵ��豸
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

	// ���û�ҵ��豸�ͽ�������,������
	if (FAILED(result))
	{
		DXTRACE_MSG("Failed to create the Direct3D device!");
		return false;
	}


	ID3D11Texture2D *backBufferTexture;


	// ��ȡswap buff��,������backBufferTexture��
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
	if (FAILED(result))
	{
		DXTRACE_MSG("Failed to get the swap chain back buffer!");
		return false;
	}

	// ��get����buff(backBufferTexture)������ȾĿ��,��������ȫ��bufferTargetView��
	result = m_d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &m_backBufferTarget);

	if(backBufferTexture)
	{  // ���ü���-1
		backBufferTexture->Release();
	}

	if (FAILED(result))
	{
		DXTRACE_MSG("Failed to create the render target view!");
		return false;
	}

	// ����ȾĿ��󶨵����ߵ�����ϲ��׶�
	m_d3dContext->OMSetRenderTargets(1, &m_backBufferTarget, 0);

	//�����ӿ�
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

