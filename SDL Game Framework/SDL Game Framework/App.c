#include "stdafx.h"
#include "App.h"

#include "Framework.h"
#include "Framework/Scene.h"
#include "Framework/Window.h"

App g_App;

bool App_Init(void)
{
	if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		LogWithErrorCode("Fail to initialize SDL", SDL_GetError());

		return false;
	}

	if (NULL == Window_Init())
	{
		LogWithErrorCode("Fail to intialize window", SDL_GetError());

		return false;
	}

	if (NULL == Renderer_Init())
	{
		LogWithErrorCode("Fail to initialize renderer", SDL_GetError());

		return false;
	}

	if (false == Image_Init())
	{
		LogWithErrorCode("Fail to initalize image library", IMG_GetError());

		return false;
	}

	Random_Init();

	if (false == Audio_Init())
	{
		LogWithErrorCode("Fail to intialize audio library", Mix_GetError());

		return false;
	}

	if (false == Text_Init())
	{
		LogWithErrorCode("Fail to initialize font library", TTF_GetError());

		return false;
	}

	return true;
}

void cleanup(void)
{
	Text_Cleanup();
	Audio_Cleanup();
	Image_Cleanup();
	Renderer_Cleanup();
	Window_Cleanup();
	SDL_Quit();
}

void processInput(void)
{
	Input_Update();
}

void update(void)
{
	g_Scene.Update();
}

void render(void)
{
	g_Scene.Render();
	Renderer_Flip();
}

int32 App_Run(void)
{
	atexit(cleanup);

	Timer_Init(FPS);

	Scene_SetNextScene(SCENE_TITLE);

	SDL_Event event;
	while (true)
	{
		if (SDL_PollEvent(&event)) // sdl 실행창 띄우는 명령어, SDL_QUIT값을 반환하면 실행종료
		{
			if (event.type == SDL_QUIT)
			{
				break;
			}
		}
		else
		{
			if (Scene_IsSetNextScene())
			{
				Scene_Change(); // s_nextScene값을 받아서 switch문에 따라서 각 신데이터를 초기화 시킨다.
			}

			if (Timer_Update())
			{
				processInput(); // 플레이어로부터의 입력을 업데이트 시킨다.
				update(); // 신데이터들을 실시간으로 업데이트 시킨다.
				render(); // 신데이터들을 실시간으로 랜더링 시킨다.
			}
		}
	}


	return 0;
}