#include "GameState.h"

using namespace ENgines;
using namespace ENgines::Math;
using namespace ENgines::Graphics;
using namespace ENgines::Core;
using namespace ENgines::Input;

const char* gSolarSystemNames[] =
{
	"MilkyWay",
	"Earth",
	"Jupiter",
	"Mars",
	"Mercury",
	"Neptune",
	"Pluto",
	"Saturn",
	"Sun",
	"Uranus",
	"Venus"
};
float planetRotationSpeed[11]
{
   0,
   1.5,
   45.5,
   86.6,
   10.8,
   9.7,
   17,
   36.8,
   31.89,
   14.7,
   6.5
};
float planetDistance[11]
{
   0,
   241,
   860,
   319,
   150,
   3500,
   4000,
   1500,
   0,
   1900,
   200
};
float planetOrbitSpeed[11]
{
	0,
	1.5,
	45.5,
	88.6,
	10.8,
	9.7,
	17,
	36.8,
	0,
	4.7,
	6.5
};

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mRenderTargetCamera.SetPosition({ 0.0f, 1.0f, -5.0f });
	mRenderTargetCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mRenderTargetCamera.SetAspectRatio(1.0f);

	MeshPX mesh0 = MeshBuilder::CreateSkySpherePX(100, 100, 8000.0f);//Space - Really Big
	MeshPX mesh1 = MeshBuilder::CreateSpherePX(60, 60, 1.0f);//Earth - 1 - 24 - 67
	MeshPX mesh2 = MeshBuilder::CreateSpherePX(60, 60, 11.0f);//Jupiter - 11 - 648 - 804
	MeshPX mesh3 = MeshBuilder::CreateSpherePX(60, 60, 0.5f);//Mars - 0.5
	MeshPX mesh4 = MeshBuilder::CreateSpherePX(60, 60, 0.35f);//Mercury - 0.35
	MeshPX mesh5 = MeshBuilder::CreateSpherePX(60, 60, 4.0f);//Neptune - 4
	MeshPX mesh6 = MeshBuilder::CreateSpherePX(60, 60, 0.2f);//Pluto - 0.2
	MeshPX mesh7 = MeshBuilder::CreateSpherePX(60, 60, 10.0f);//Saturn 10
	MeshPX mesh8 = MeshBuilder::CreateSpherePX(60, 60, 109.0f);//Sun 109
	MeshPX mesh9 = MeshBuilder::CreateSpherePX(60, 60, 4.0f);//Uranus 4
	MeshPX mesh10 = MeshBuilder::CreateSpherePX(60, 60, 0.9f);//Venus 0.9

	mMeshBuffer[0].Initialize<MeshPX>(mesh0);
	mMeshBuffer[1].Initialize<MeshPX>(mesh1);
	mMeshBuffer[2].Initialize<MeshPX>(mesh2);
	mMeshBuffer[3].Initialize<MeshPX>(mesh3);
	mMeshBuffer[4].Initialize<MeshPX>(mesh4);
	mMeshBuffer[5].Initialize<MeshPX>(mesh5);
	mMeshBuffer[6].Initialize<MeshPX>(mesh6);
	mMeshBuffer[7].Initialize<MeshPX>(mesh7);
	mMeshBuffer[8].Initialize<MeshPX>(mesh8);
	mMeshBuffer[9].Initialize<MeshPX>(mesh9);
	mMeshBuffer[10].Initialize<MeshPX>(mesh10);

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexture.fx";
	for (int i = 0; i < 11; i++) {
		mConstantBuffer[i].Initialize(sizeof(Matrix4));
		mVertexShader.Initialize<VertexPX>(shaderFile);
		mPixelShader.Initialize(shaderFile);
	}
	mDiffuseTexture[0].Initialize("../../Assets/Images/skysphere/space.jpg");
	mDiffuseTexture[1].Initialize("../../Assets/Images/planets/earth.jpg");
	mDiffuseTexture[2].Initialize("../../Assets/Images/planets/jupiter.jpg");
	mDiffuseTexture[3].Initialize("../../Assets/Images/planets/mars.jpg");
	mDiffuseTexture[4].Initialize("../../Assets/Images/planets/mercury.jpg");
	mDiffuseTexture[5].Initialize("../../Assets/Images/planets/neptune.jpg");
	mDiffuseTexture[6].Initialize("../../Assets/Images/planets/pluto.jpg");
	mDiffuseTexture[7].Initialize("../../Assets/Images/planets/saturn.jpg");
	mDiffuseTexture[8].Initialize("../../Assets/Images/planets/sun.jpg");
	mDiffuseTexture[9].Initialize("../../Assets/Images/planets/uranus.jpg");
	mDiffuseTexture[10].Initialize("../../Assets/Images/planets/venus.jpg");

	
	
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	constexpr uint32_t size = 512;
	mRenderTarget.Initialize(size, size, Texture::Format::RGBA_U32);



	//Space
	/*MeshPX mesh0 = MeshBuilder::CreateSkySpherePX(100, 100, 60.0f);
	mMeshBuffer.Initialize<MeshPX>(mesh0);
	std::filesystem::path shaderFile0 = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderFile0);
	mPixelShader.Initialize(shaderFile0);
	mDiffuseTexture.Initialize("../../Assets/Images/skysphere/space.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);*/
}

void GameState::Terminate()
{
	mRenderTarget.Terminate();
	mSampler.Terminate();
	for (int i = 0; i < 11; i++) {
		mDiffuseTexture[i].Terminate();
		mConstantBuffer[i].Terminate();
		mMeshBuffer[i].Terminate();
	}
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void GameState::UpdateCamera(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 250.0f : 50.0f) * deltaTime;
	const float turnSpeed = 0.2f * deltaTime;
	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}
}

float rotationDay = 0.0f;
float rotationYear = 0.0f;
float rotationDaySpeed = 0.001;
float rotationYearSpeed = 0.001;
float targetDistance = -400.0f;
bool planetRings = true;
bool orbitRings = true;
int current = 0;

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
	//rotationDay += Math::Constants::HalfPi * deltaTime * rotationDaySpeed;
	//rotationYear += Math::Constants::HalfPi * deltaTime * rotationYearSpeed;
	rotationDay += deltaTime * rotationDaySpeed;
	rotationYear += deltaTime * rotationYearSpeed;

	//for (int i = 0; i < 11; i++) {
	//	rotationDay += planetRotationSpeed[i] * deltaTime;// *rotationDaySpeed;
	//}
}

void GameState::Render()
{
	if (orbitRings)
	{
		for (int i = 0; i < 11; i++)
		{
			SimpleDraw::AddGroundCircle(100, planetDistance[i], { 0,0,0 }, Colors::White);
		}
	}

	/*if (planetRings)
	{
		for (int i = 0; i < 11; i++)
		{
			Matrix4 ringWorld = Matrix4::RotationY(planetRotationSpeed[i] * rotationDay) * Matrix4::Translation(Vector3::ZAxis * planetDistance[i]) * Matrix4::RotationY(planetOrbitSpeed[i] * rotationYear);
			Vector3 ringPosition = { ringWorld._41,ringWorld._42,ringWorld._43 };

			SimpleDraw::AddGroundCircle(100, 25, ringPosition, Colors::White);
		}
	}*/
	SimpleDraw::Render(mCamera);
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS(0);

	for (int i = 0; i < 11; i++) {
		mDiffuseTexture[i].BindPS(0);
		Matrix4 matWorld = Matrix4::RotationY(planetRotationSpeed[i] * rotationDay) * Matrix4::Translation(Vector3::ZAxis * planetDistance[i]) * Matrix4::RotationY(planetOrbitSpeed[i] * rotationYear);
		Matrix4 matView = mCamera.GetViewMatrix();
		Matrix4 matProj = mCamera.GetProjectionMatrix();
		Matrix4 matFinal = matWorld * matView * matProj;
		Matrix4 wvp = Transpose(matFinal);
		mConstantBuffer[i].Update(&wvp);
		mConstantBuffer[i].BindVS(0);

		mMeshBuffer[i].Render();
	}


	Matrix4 matWorld1 = Matrix4::RotationY(planetRotationSpeed[current] * rotationDay);
	Matrix4 matView1 = mRenderTargetCamera.GetViewMatrix();
	Matrix4 matProj1 = mRenderTargetCamera.GetProjectionMatrix();
	Matrix4 matFinal1 = matWorld1 * matView1 * matProj1;
	Matrix4 wvp1 = Transpose(matFinal1);
	mConstantBuffer[current].Update(&wvp1);
	mConstantBuffer[current].BindVS(0);

	mRenderTargetCamera.SetPosition({ 0.0f, 0.0f, targetDistance});

	mRenderTarget.BeginRender();
	mMeshBuffer[current].Render();
	mRenderTarget.EndRender();
}

bool buttonValue = false;
int intValue = 0;
void GameState::DebugUI()
{

	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	current = static_cast<int>(mSolarSystem);
	if (ImGui::Combo("Solar System", &current, gSolarSystemNames, static_cast<int>(std::size(gSolarSystemNames))))
	{
		mSolarSystem = (SolarSystem)current;
	}

	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 256, 256 },
		{ 0, 0 },	//uv0
		{ 1, 1 },	//uv1
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 });

	if (mSolarSystem == SolarSystem::Sun)
	{
		if (ImGui::CollapsingHeader("Rotation Speeds")) {
			//ImGui::DragFloat("Planet Rotation Speed", &planetRotationSpeed[9], 0.01f);
			ImGui::DragFloat("Planet Rotation Speed", &rotationDaySpeed, 0.01f);
		}
	}
	else if (mSolarSystem == SolarSystem::Mercury) {
		if (ImGui::CollapsingHeader("Rotation Speeds")) {
			ImGui::DragFloat("Planet Rotation Speed", &rotationDaySpeed, 0.01f);
			ImGui::DragFloat("Orbit Rotation Speed", &rotationYearSpeed, 0.01f);
		}
	}
	else if (mSolarSystem == SolarSystem::Venus) {
		if (ImGui::CollapsingHeader("Rotation Speeds")) {
			ImGui::DragFloat("Planet Rotation Speed", &rotationDaySpeed, 0.01f);
			ImGui::DragFloat("Orbit Rotation Speed", &rotationYearSpeed, 0.01f);
		}
	}
	else if (mSolarSystem == SolarSystem::Earth) {
		if (ImGui::CollapsingHeader("Rotation Speeds")) {
			ImGui::DragFloat("Planet Rotation Speed", &rotationDaySpeed, 0.01f);
			ImGui::DragFloat("Orbit Rotation Speed", &rotationYearSpeed, 0.01f);
		}
	}
	else if (mSolarSystem == SolarSystem::Mars) {
		if (ImGui::CollapsingHeader("Rotation Speeds")) {
			ImGui::DragFloat("Planet Rotation Speed", &rotationDaySpeed, 0.01f);
			ImGui::DragFloat("Orbit Rotation Speed", &rotationYearSpeed, 0.01f);
		}
	}
	else if (mSolarSystem == SolarSystem::Jupiter) {
		if (ImGui::CollapsingHeader("Rotation Speeds")) {
			ImGui::DragFloat("Planet Rotation Speed", &rotationDaySpeed, 0.01f);
			ImGui::DragFloat("Orbit Rotation Speed", &rotationYearSpeed, 0.01f);
		}
	}
	else if (mSolarSystem == SolarSystem::Saturn) {
		if (ImGui::CollapsingHeader("Rotation Speeds")) {
			ImGui::DragFloat("Planet Rotation Speed", &rotationDaySpeed, 0.01f);
			ImGui::DragFloat("Orbit Rotation Speed", &rotationYearSpeed, 0.01f);
		}
		if (ImGui::CollapsingHeader("Ring Toggle")) {
			ImGui::Checkbox("Saturn's Rings", &planetRings);
		}
	}
	else if (mSolarSystem == SolarSystem::Neptune) {
		if (ImGui::CollapsingHeader("Rotation Speeds")) {
			ImGui::DragFloat("Planet Rotation Speed", &rotationDaySpeed, 0.01f);
			ImGui::DragFloat("Orbit Rotation Speed", &rotationYearSpeed, 0.01f);
		}
	}
	else if (mSolarSystem == SolarSystem::Uranus) {
		if (ImGui::CollapsingHeader("Rotation Speeds")) {
			ImGui::DragFloat("Planet Rotation Speed", &rotationDaySpeed, 0.01f);
			ImGui::DragFloat("Orbit Rotation Speed", &rotationYearSpeed, 0.01f);
		}
	}
	else if (mSolarSystem == SolarSystem::Pluto) {
		if (ImGui::CollapsingHeader("Rotation Speeds")) {
			ImGui::DragFloat("Planet Rotation Speed", &rotationDaySpeed, 0.01f);
			ImGui::DragFloat("Orbit Rotation Speed", &rotationYearSpeed, 0.01f);
		}
	}
	ImGui::DragFloat("Target Distance", &targetDistance, 0.5f, -400.0f, 0.0f);
	ImGui::Checkbox("Orbit Rings", &orbitRings);
	ImGui::End();
}