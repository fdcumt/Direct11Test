
#include "BlankDemo.h"

BlankDemo::BlankDemo()
{

}

BlankDemo::~BlankDemo()
{

}

bool BlankDemo::Loadcontent()
{
	return true;
}

void BlankDemo::UnloadContent()
{

}

void BlankDemo::Update(float dt)
{

}

void BlankDemo::Render()
{
	if (m_d3dContext == NULL) 
	{
		return ;
	}

	float clearColor[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
	m_d3dContext->ClearRenderTargetView(m_backBufferTarget, clearColor);

	m_swapChain->Present( 0, 0 );
}
