#pragma once
#include <ENgines/Inc/ENgines.h>

class ShapeState : public ENgines::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	//void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape();
	virtual void Update(float deltaTime);
	struct Vertex {
		ENgines::Math::Vector3 position;
		ENgines::Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	ENgines::Graphics::Camera mCamera;
	ENgines::Graphics::ConstantBuffer mConstantBuffer;
	ENgines::Graphics::MeshBuffer mMeshBuffer;
	ENgines::Graphics::VertexShader mVertexShader;
	ENgines::Graphics::PixelShader mPixelShader;
};