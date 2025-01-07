#include <ENgines/Inc/ENgines.h>

#include "GameState.h"

using namespace ENgines;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Terrain";

	App& myApp = MainApp();
	myApp.AddState<GameState>("Cube");
	myApp.Run(config);
	return(0);
}