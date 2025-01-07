#include "GameState.h"

using namespace ENgines;
using namespace ENgines::Math;
using namespace ENgines::Graphics;
using namespace ENgines::Core;
using namespace ENgines::Input;

void GameState::Initialize()
{
	MeshPX mesh = MeshBuilder::CreateSpherePX(60,60, 1.0f);
	mCamera.SetPosition({ 0.0f, 1.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mMeshBuffer.Initialize<MeshPX>(mesh);

	mConstantBuffer.Initialize(sizeof(Matrix4));
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderFile);
	mPixelShader.Initialize(shaderFile);

	mDiffuseTexture.Initialize("../../Assets/Images/misc/basketball.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameState::Terminate()
{
	mSampler.Terminate();
	mDiffuseTexture.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
}

float gRotationX = 0.0f;
float gRotationY = 0.0f;
void GameState::Update(float deltaTime)
{
	gRotationX += Math::Constants::HalfPi * deltaTime * 0.25f;
	gRotationY += Math::Constants::HalfPi * deltaTime * 0.5f;
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mDiffuseTexture.BindPS(0);
	mSampler.BindPS(0);

	Matrix4 matWorld = Matrix4::RotationY(gRotationY) * Matrix4::RotationX(gRotationX);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}