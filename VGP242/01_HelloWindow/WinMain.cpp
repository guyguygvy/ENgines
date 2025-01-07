#include <ENgines/Inc/ENgines.h>

class GameState :public ENgines::AppState
{
public:
    void Initialize() override
    {
        LOG("Game State Initialized");
    }

    void Terminate() override
    {
        LOG("Game State Terminated");
    }
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int) 
{
	ENgines::AppConfig config;
	config.appName = L"Hello WIndow";

	ENgines::App& myApp = ENgines::MainApp();
    myApp.AddState<GameState>("GameState");
	myApp.Run(config);
	return(0);
}