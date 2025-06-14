#include <ENgines/Inc/ENgines.h>

#include "GameState.h"
#include "EditTemplateState.h"

using namespace ENgines;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Editor";

	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.AddState<EditTemplateState>("EditTemplateState");
	myApp.Run(config);
	return(0);
}