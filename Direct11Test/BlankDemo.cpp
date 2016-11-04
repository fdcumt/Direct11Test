
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

	// 绘制渲染在场景中的(其他的要有,这个不绘制任何几何体,是个空的demo)

	m_swapChain->Present( 0, 0 );
}
