#pragma once

#include <ENgines/Inc/ENgines.h>

class EditTemplateState : public ENgines::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;
	void DebugUI() override;
	void Update(float deltaTime);

protected:
	ENgines::GameWorld mGameWorld;
};
