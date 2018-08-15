////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textclass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"
#include <math.h>

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, float, bool);
	//bool Renderf();
	void MoveCamera(float, float);
	void SetAmbientLight(float, float, float);
	void SetModelRotation(float, float);
	void SetCus(float);
	bool Render(float, float, float, bool);
	//float GetCus();

private:
	

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model,* m_Model2;
	ModelClass* m_Modeltest;
	TextClass* m_Text;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;
	float cusf;
};

#endif