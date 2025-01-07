#include <ENgines/Inc/ENgines.h>
#include "GameState.h"

using namespace ENgines;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Solar System";

	App& myApp = MainApp();
	myApp.AddState<GameState>("SolarSystem");
	myApp.Run(config);
	return(0);
}

