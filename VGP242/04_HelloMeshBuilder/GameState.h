#pragma once
#include <ENgines/Inc/ENgines.h>

class GameState : public ENgines::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;

	void Update(float deltaTime);
protected:
	ENgines::Graphics::Camera mCamera;
	ENgines::Graphics::ConstantBuffer mConstantBuffer;
	ENgines::Graphics::MeshBuffer mMeshBuffer;
	ENgines::Graphics::VertexShader mVertexShader;
	ENgines::Graphics::PixelShader mPixelShader;
	ENgines::Graphics::Texture mDiffuseTexture;
	ENgines::Graphics::Sampler mSampler;
};