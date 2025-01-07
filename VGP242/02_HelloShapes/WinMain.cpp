#include <ENgines/Inc/ENgines.h>
#include "ShapeState.h"

using namespace ENgines;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Shapes";
	config.winWidth = 800;
	config.winHeight = 800;

	App& myApp = MainApp();
	myApp.AddState<HeartShapeState>("HeartShapeState");
	myApp.AddState<DiamondShapeState>("DiamondShapeState");
	myApp.AddState<TriforceShapeState>("TriforceShapeState");
	myApp.AddState<SquareShapeState>("SquareShapeState");
	myApp.AddState<TriangleShapeState>("TriangleShapeState");


	myApp.Run(config);
	return(0);
}

