#include <ENgines/Inc/ENgines.h>
#include "GameState.h"

using namespace ENgines;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Shape Swap";

	App& myApp = MainApp();
	myApp.AddState<MeshPCCube>("Cube");
	myApp.AddState<MeshPCRect>("Rectangle");
	myApp.AddState<MeshPCPlane>("Plane");
	myApp.AddState<MeshPCSphere>("Sphere");
	myApp.AddState<MeshPCCylinder>("Cylinder");
	myApp.AddState<MeshPXSkybox>("Skybox");
	myApp.AddState<MeshPXSkysphere>("Skysphere");
	myApp.Run(config);
	return(0);
}

