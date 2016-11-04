#pragma once

/*
	Blank Direct3D Demo Class - this demo displays a blank Direct3D demo 
*/

#include "DX11DemoBase.h"
#include <xnamath.h>

class BlankDemo : public Dx11DemoBase
{
public:
	BlankDemo();
	virtual ~BlankDemo();

	bool Loadcontent();
	void UnloadContent();

	void Update(float dt);
	void Render();


};

