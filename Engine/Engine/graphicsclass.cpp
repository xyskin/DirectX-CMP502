////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#define pi 3.1415926535898f
static float rotationX = 0.0f;
static float rotationY = 0.0f;
static D3DXMATRIX myMatrix;

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Model2 = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Text = 0;
	m_ParticleShader = 0;
	m_ParticleSystem = 0;
	cusf = 1.0f;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}


	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position and rotation of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -4.0f);
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
	m_Camera->Render();

	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/Sphere.txt", L"../Engine/data/Earth.dds", 1, 0);


	// Create the model object.
	m_Model2 = new ModelClass;
	if (!m_Model2)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/Sphere.txt", L"../Engine/data/Moon.dds", 0.2, 2);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	//Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	m_Camera->GetViewMatrix(myMatrix);

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, myMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader)
	{
		return false;
	}

	// Initialize the particle shader object.
	result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the particle system object.
	m_ParticleSystem = new ParticleSystemClass;
	if (!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"../Engine/data/star.dds");
	if (!result)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(0.9f, 0.9f, 0.9f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if (m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the particle system object.
	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	return;
}


bool GraphicsClass::Frame(int fps, int cpu, float frametime, bool particle)
{
	bool result;

	static const float delta = 1.0f;

	// Update the rotation variable each frame.
	//rotationX += (float)D3DX_PI * 0.01f;
	//if(rotationX > 360.0f)
	//{
	//	rotationX -= 360.0f;
	//}

	// Update the delta variable each frame. (keep this between 0 and 1)
	//delta += 0.001;
	//if (delta > 1.0f)
	//{
	//	delta -= 1.0f;
	//}


	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	if (particle) {
		m_ParticleSystem->Frame(frametime, m_D3D->GetDeviceContext());
	}

	// Render the graphics scene.
	result = Render(rotationX, rotationY, delta, particle);
	if (!result)
	{
		return false;
	}


	return true;
}


bool GraphicsClass::Render(float rotationX, float rotationY, float deltavalue, bool particle)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, myMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//D3DXMATRIX X, Y, Z;
	//D3DXMatrixRotationX(&X, rotationX);
	D3DXMatrixRotationY(&worldMatrix, rotationY);
	//D3DXMatrixRotationZ(&Z, rotation);
	//worldMatrix = Y;

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(), deltavalue, m_Model->GetTexture(), cusf);
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	static float delta = 0;
	delta += 0.01f;
	if (delta >= 2 * pi) {
		delta = 0;
	}
	D3DXMatrixRotationY(&worldMatrix, delta);
	m_Model2->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(), deltavalue, m_Model2->GetTexture(), cusf);
	if (!result)
	{
		return false;
	}

	if (particle) {
		m_D3D->GetWorldMatrix(worldMatrix);
		// Turn on alpha blending.
		m_D3D->TurnOnAlphaBlending();

		// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
		m_ParticleSystem->Render(m_D3D->GetDeviceContext());

		// Render the model using the texture shader.
		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, myMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());
		if (!result)
		{
			return false;
		}

		// Turn off alpha blending.
		m_D3D->TurnOffAlphaBlending();
	}
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

//void GraphicsClass::MoveCamera(float theta, float phi) {
//	static float radius = -10.0f;
//	static float thetap = 0.0f;
//	static float phip = 3 * pi / 4 ;
//	D3DXVECTOR3 rot = m_Camera->GetRotation();
//	D3DXVECTOR3 pos = m_Camera->GetPosition();
//	phip += phi;
//	thetap += theta;
//	//m_Camera->SetRotation(rot.x - atan(tan(theta) / sin(phip)), rot.y - phi, rot.z - atan(tan(theta) / cos(phip)));
//	m_Camera->SetRotation(atan(tan(thetap) / sin(phip)),phip, atan(tan(thetap) / cos(phip)));
//	rot = m_Camera->GetRotation();
//	//m_Camera->SetPosition(radius*sin(rot.y * 2 * pi / 360), pos.y, radius*cos(rot.y * 2 * pi / 360)); - atan(tan(theta) / cos(phi))
//    //m_Camera->SetPosition(pos.x, -radius*sin(rot.x * 2 * pi / 360), radius*cos(rot.x * 2 * pi / 360));
//	//m_Camera->SetPosition(-radius*cos(thetap * 2 * pi / 360)*sin(phip * 2 * pi / 360), radius*sin(thetap * 2 * pi / 360),
//	//	radius*cos(thetap * 2 * pi / 360)*cos(phip * 2 * pi / 360));
//	m_Camera->SetPosition(radius*sin(rot.y * 2 * pi / 360), -radius*sin(rot.x * 2 * pi / 360),radius*cos(rot.y * 2 * pi / 360)*cos(rot.x * 2 * pi / 360));
//}

void GraphicsClass::MoveCamera(float theta, float phi) {
	static float radius = 4.0f;
	static float thetap = 0.0f;
	static float phip = 0.0f;
	thetap += theta;
	phip += phi;
	if (thetap >= -88 && thetap <= 88) {
		m_Camera->SetPosition(radius*cos(thetap * 2 * pi / 360.0f)*cos((phip - 90) * 2 * pi / 360.0f), radius*sin(thetap * 2 * pi / 360.0f),
			radius*cos(thetap * 2 * pi / 360.0f)*sin((phip - 90) * 2 * pi / 360.0f));
		m_Camera->SetLookAt(-m_Camera->GetPosition().x, -m_Camera->GetPosition().y, -m_Camera->GetPosition().z);
	}
	else if (thetap < -88)
	{
		thetap = -88;
		m_Camera->SetPosition(radius*cos(thetap * 2 * pi / 360.0f)*cos((phip - 90) * 2 * pi / 360.0f), radius*sin(thetap * 2 * pi / 360.0f),
			radius*cos(thetap * 2 * pi / 360.0f)*sin((phip - 90) * 2 * pi / 360.0f));
		m_Camera->SetLookAt(-m_Camera->GetPosition().x, -m_Camera->GetPosition().y, -m_Camera->GetPosition().z);
	}
	else if (thetap > 88) {
		thetap = 88;
		m_Camera->SetPosition(radius*cos(thetap * 2 * pi / 360.0f)*cos((phip - 90) * 2 * pi / 360.0f), radius*sin(thetap * 2 * pi / 360.0f),
			radius*cos(thetap * 2 * pi / 360.0f)*sin((phip - 90) * 2 * pi / 360.0f));
		m_Camera->SetLookAt(-m_Camera->GetPosition().x, -m_Camera->GetPosition().y, -m_Camera->GetPosition().z);
	}
}

void GraphicsClass::SetAmbientLight(float r, float g, float b) {
	m_Light->SetAmbientColor(r, g, b, 1.0f);
}

void GraphicsClass::SetModelRotation(float roX, float roY) {
	rotationX = roX;
	rotationY = roY;
}

void GraphicsClass::SetCus(float cus) {
	cusf = cus;
}
