#include "stdafx.h"
#include "Scene.h"
#include "Framework.h"
#include "CsvParser.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

typedef struct TitleSceneData
{
	Image	TitleBackGroundImage;
	Image	GameStartImage;
	Image	CursorImage;
	COORD	CursorPos;
	Music	BGM;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Image_LoadImage(&data->TitleBackGroundImage, "TitleImage.png");
	Image_LoadImage(&data->GameStartImage, "GameStartImage.png");
	Image_LoadImage(&data->CursorImage, "CursorImage.png");

	Audio_LoadMusic(&data->BGM, "Background.mp3");
	Audio_Play(&data->BGM, INFINITY_LOOP);
}

#define GameStartPosX 528
#define GameStartPosY 533

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	if ((Input_GetKeyDown(VK_UP) || Input_GetKeyDown(VK_DOWN)) && data->CursorPos.X == 0 && data->CursorPos.Y == 0)
	{
		data->CursorPos.X = GameStartPosX;
		data->CursorPos.Y = GameStartPosY;
	}
	else if ((Input_GetKeyDown(VK_UP) || Input_GetKeyDown(VK_DOWN)) && data->CursorPos.X != 0 && data->CursorPos.Y != 0)
	{
		data->CursorPos.X = 0;
		data->CursorPos.Y = 0;
	}

	if (Input_GetKeyDown(VK_SPACE) && data->CursorPos.X == GameStartPosX && data->CursorPos.Y == GameStartPosY)
	{
		Scene_SetNextScene(SCENE_CONTENT);
	}
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->TitleBackGroundImage, 0, 0);
	Renderer_DrawImage(&data->GameStartImage, 559, 540);

	if (data->CursorPos.X != 0 && data->CursorPos.Y != 0)
	{
		Renderer_DrawImage(&data->CursorImage, data->CursorPos.X, data->CursorPos.Y);
	}
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Audio_FreeMusic(&data->BGM);
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region ContentScene

typedef struct tagSelect {
	wchar_t* selectContent;
	int nextIndex;
} Select;

typedef struct tagConetentSceneData {
	Image BackGroundImage;
	Image BackPaper;
	Text GuideLine[GUIDELINE_COUNT];
	int id;
	wchar_t* contentText;	// GuideLine.String에 집어넣어야 함
	Music BGM;
	int32 X;
	int32 Y;
} ContentSceneData;

int32 id = 30;

void init_content(void)
{
	g_Scene.Data = malloc(sizeof(ContentSceneData));
	memset(g_Scene.Data, 0, sizeof(ContentSceneData));

	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;

	Image_LoadImage(&data->BackGroundImage, ReturnBackGroundImage(id));
	Image_LoadImage(&data->BackPaper, "BackPaper.png");

	Audio_LoadMusic(&data->BGM, ReturnBGM(id));
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);

	for (int32 i = 0; i < GUIDELINE_COUNT; i++)
	{
		wchar_t* myStr = ReturnContentText(id, i);
		Text_CreateText(&data->GuideLine[i], "GongGothicLight.ttf", 20, myStr, wcslen(myStr));
	}

}

void update_content(void)
{
	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;
	
}
void render_content(void)
{
	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->BackGroundImage, 0, 0);
	Renderer_DrawImage(&data->BackPaper, 0, 0);

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 50, 100 + 30 * i, color);
	}

}

void release_content(void)
{
	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;

	Audio_FreeMusic(&data->BGM);
}
#pragma endregion

#pragma region EndingScene
const wchar_t* str2[] = {
	L"김 PD 살인사건",
	L"",
	L"하이파이브",
	L"",
	L"제작",
	L"",
	L"기획",
	L"",
	L"김 태희",
	L"장 건",
	L"",
	L"프로그래밍",
	L"",
	L"박 현수",
	L"성 권문",
	L"김 동현",
	L"",
	L"The End"
};

typedef struct EndingSceneData
{
	Text		GuideLine[GUIDELINE_COUNT];
	Music		BGM;
	float		Volume;
	SoundEffect Effect;
	Image		BackGround;
	float		Speed;
	int32		X;
	int32		Y;
	int32		Alpha;
} EndingSceneData;

void init_ending(void)
{
	g_Scene.Data = malloc(sizeof(EndingSceneData));
	memset(g_Scene.Data, 0, sizeof(EndingSceneData));

	EndingSceneData* data = (EndingSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "GongGothicBold.ttf", 20, str2[i], wcslen(str2[i]));
	}

	Audio_LoadMusic(&data->BGM, "Denouement.mp3");
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);

	data->Volume = 1.0f;

	data->Speed = 400.0f;
	data->X = 400;
	data->Y = 400;
	data->Alpha = 255;
}

void update_ending(void)
{
	EndingSceneData* data = (EndingSceneData*)g_Scene.Data;

}

int upPixel = 0;

void render_ending(void)
{
	EndingSceneData* data = (EndingSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 600, 900 + 30 * i - upPixel, color);
	}

	upPixel += 5;
}

void release_ending(void)
{
	EndingSceneData* data = (EndingSceneData*)g_Scene.Data;

	for (int32 i = 0; i < 10; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Audio_FreeMusic(&data->BGM);
	Audio_FreeSoundEffect(&data->Effect);

	SafeFree(g_Scene.Data);
}
#pragma endregion

bool Scene_IsSetNextScene(void)
{
	if (SCENE_NULL == s_nextScene)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Scene_SetNextScene(ESceneType scene)
{
	assert(s_nextScene == SCENE_NULL);
	assert(SCENE_NULL < scene&& scene < SCENE_MAX);

	s_nextScene = scene;
}

void Scene_Change(void)
{
	assert(s_nextScene != SCENE_NULL);

	if (g_Scene.Release)
	{
		g_Scene.Release();
	}

	switch (s_nextScene)
	{
	case SCENE_TITLE:
		g_Scene.Init = init_title;
		g_Scene.Update = update_title;
		g_Scene.Render = render_title;
		g_Scene.Release = release_title;
		break;
	case SCENE_CONTENT:
		g_Scene.Init = init_content;
		g_Scene.Update = update_content;
		g_Scene.Render = render_content;
		g_Scene.Release = release_content;
		break;
	case SCENE_ENDING:
		g_Scene.Init = init_ending;
		g_Scene.Update = update_ending;
		g_Scene.Render = render_ending;
		g_Scene.Release = release_ending;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}