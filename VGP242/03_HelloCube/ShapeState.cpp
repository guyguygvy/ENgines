#include "ShapeState.h"

using namespace ENgines;
using namespace ENgines::Math;
using namespace ENgines::Graphics;
using namespace ENgines::Core;
using namespace ENgines::Input;

void ShapeState::CreateShape()
{
	// front
	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Blue });

	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Blue });
	mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Green });

	// back
	mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });
	mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Green });

	mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });

	// right
	mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });

	mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });
	mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Green });

	// left
	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Blue });
	mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Green });

	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Green });
	mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Blue });

	// top
	mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });

	mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });
	mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Green });

	// bottom
	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Blue });
	mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Green });

	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Blue });
}

void ShapeState::Initialize()
{
	CreateShape();

	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), mVertices.size());
	mConstantBuffer.Initialize(sizeof(Matrix4));

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";
	mVertexShader.Initialize(shaderFile, VE_Position | VE_Color);
	mPixelShader.Initialize(shaderFile);
}

void ShapeState::Terminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
	mVertices.clear();
}

float gRotationX = 0.0f;
float gRotationY = 0.0f;
void ShapeState::Update(float deltaTime)
{
	gRotationX += Math::Constants::HalfPi * deltaTime * 0.5f;
	gRotationY += Math::Constants::HalfPi * deltaTime * 0.5f;
}


void ShapeState::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();
	mVertexShader.Bind();
	mPixelShader.Bind();


	Matrix4 matWorld = Matrix4::RotationY(gRotationY) * Matrix4::RotationX(gRotationX);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}