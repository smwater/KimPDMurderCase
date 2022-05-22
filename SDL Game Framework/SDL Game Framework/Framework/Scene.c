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

	data->CursorPos.X = 0;
	data->CursorPos.Y = 0;

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
	Renderer_DrawImage(&data->GameStartImage, 559, 545);

	if (data->CursorPos.X != 0 && data->CursorPos.Y != 0)
	{
		Renderer_DrawImage(&data->CursorImage, data->CursorPos.X, data->CursorPos.Y);
	}
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region ContentScene
typedef struct tagConetentSceneData {
	int32 id;
	Image BackGroundImage;
	Image BackPaper;
	Image CursorImage;
	COORD CursorPos;
	Music BGM;
	SoundEffect Effect[2];
	Text TitleLine[1];
	Text TextLine[TEXTLINE_COUNT];
	Text SelectLine[3];
	int32 X;
	int32 Y;
} ContentSceneData;

// 다음씬의 id를 저장하는 변수
// 처음에는 첫 장면을 출력하기 위해 1을 입력한다.
int32 storedId = 1;
char prevBGM[] = "Background.mp3";

void init_content(void)
{
	g_Scene.Data = malloc(sizeof(ContentSceneData));
	memset(g_Scene.Data, 0, sizeof(ContentSceneData));

	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;

	data->id = storedId;

	Image_LoadImage(&data->BackGroundImage, ReturnBackGroundImage(data->id));
	Image_LoadImage(&data->BackPaper, "BackPaper.png");
	Image_LoadImage(&data->CursorImage, "CursorImage.png");

	data->CursorPos.X = 0;
	data->CursorPos.Y = 0;

	char* nowBGM = ReturnBGM(data->id);
	if (*nowBGM != prevBGM)
	{
		Audio_LoadMusic(&data->BGM, nowBGM);
		Audio_Play(&data->BGM, INFINITY_LOOP);
		
		/*for (int i = 0; nowBGM != '\0'; i++)
		{
			prevBGM[i] = *nowBGM;
			nowBGM++;
		}*/
	}
	
	for (int32 i = 0; i < 2; i++)
	{
		if (SoundEffectExisted(data->id, i))
		{
			Audio_LoadSoundEffect(&data->Effect[i], ReturnSoundEffect(data->id, i));
			Audio_PlaySoundEffect(&data->Effect[i], INFINITY_LOOP);
		}
	}

	if (TitleExisted(data->id))
	{
		wchar_t* title = ReturnTitleText(data->id);
		Text_CreateText(&data->TitleLine[0], "GongGothicMedium.ttf", 40, title, wcslen(title));
	}

	for (int32 i = 0; i < TEXTLINE_COUNT; i++)
	{
		wchar_t* content = ReturnContentText(data->id, i);
		Text_CreateText(&data->TextLine[i], "GongGothicLight.ttf", 20, content, wcslen(content));
	}

	for (int32 i = 0; i < 3; i++)
	{
		if (SelectExisted(data->id, i)) {
			Text_CreateText(&data->SelectLine[i], "GongGothicMedium.ttf", 30, ReturnSelect(data->id, i), wcslen(ReturnSelect(data->id, i)));
		}
	}
}

#define SelectPosY 485
#define SelectPosY_1 545
#define SelectPosY_2 605 

#define LimitContentTextRow 10

void update_content(void)
{
	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;
	
	// 선택지 갯수에 따른 이동범위 제한
	if (SelectExisted(data->id, 2))
	{
		if (Input_GetKeyDown(VK_DOWN) && data->CursorPos.Y == 0)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY;
		}
		else if (Input_GetKeyDown(VK_DOWN) && data->CursorPos.Y == SelectPosY)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY_1;
		}
		else if (Input_GetKeyDown(VK_DOWN) && data->CursorPos.Y == SelectPosY_1)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY_2;
		}
		else if (Input_GetKeyDown(VK_DOWN) && data->CursorPos.Y == SelectPosY_2)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = 0;
		}
		else if (Input_GetKeyDown(VK_UP) && data->CursorPos.Y == SelectPosY_2)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY_1;
		}
		else if (Input_GetKeyDown(VK_UP) && data->CursorPos.Y == SelectPosY_1)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY;
		}
		else if (Input_GetKeyDown(VK_UP) && data->CursorPos.Y == SelectPosY)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = 0;
		}
		else if (Input_GetKeyDown(VK_UP) && data->CursorPos.Y == 0)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY_2;
		}
	}
	else if (SelectExisted(data->id, 1))
	{
		if (Input_GetKeyDown(VK_DOWN) && data->CursorPos.Y == 0)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY;
		}
		else if (Input_GetKeyDown(VK_DOWN) && data->CursorPos.Y == SelectPosY)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY_1;
		}
		else if (Input_GetKeyDown(VK_DOWN) && data->CursorPos.Y == SelectPosY_1)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = 0;
		}
		else if (Input_GetKeyDown(VK_UP) && data->CursorPos.Y == SelectPosY_1)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY;
		}
		else if (Input_GetKeyDown(VK_UP) && data->CursorPos.Y == SelectPosY)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = 0;
		}
		else if (Input_GetKeyDown(VK_UP) && data->CursorPos.Y == 0)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY_1;
		}
	}
	// 한 화면에 텍스트가 10줄 이상일 때 예외 처리
	else if(ReturnContentTextRow(data->id) >= LimitContentTextRow)
	{
		if ((Input_GetKeyDown(VK_UP) || Input_GetKeyDown(VK_DOWN)) && data->CursorPos.Y == 0)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY_2;
		}
		else if ((Input_GetKeyDown(VK_UP) || Input_GetKeyDown(VK_DOWN)) && data->CursorPos.Y != 0)
		{
			data->CursorPos.X = 0;
			data->CursorPos.Y = 0;
		}
	}
	else
	{
		if ((Input_GetKeyDown(VK_UP) || Input_GetKeyDown(VK_DOWN)) && data->CursorPos.Y == 0)
		{
			data->CursorPos.X = 30;
			data->CursorPos.Y = SelectPosY;
		}
		else if ((Input_GetKeyDown(VK_UP) || Input_GetKeyDown(VK_DOWN)) && data->CursorPos.Y != 0)
		{
			data->CursorPos.X = 0;
			data->CursorPos.Y = 0;
		}
	}

	// 현재 씬이 컨텐츠씬에서 마지막 씬일 경우 엔딩을 출력
	if (Input_GetKeyDown(VK_SPACE) && data->CursorPos.Y == SelectPosY && data->id == 83)
	{
		Scene_SetNextScene(SCENE_ENDING);
	}
	// 한 화면에 텍스트가 10줄 이상일 때 예외처리
	else if (ReturnContentTextRow(data->id) >= LimitContentTextRow && Input_GetKeyDown(VK_SPACE) && data->CursorPos.Y == SelectPosY_2)
	{
		storedId = ReturnSelectIndex(data->id, 0);
		Scene_SetNextScene(SCENE_CONTENT);
	}
	// 커서가 어느 선택지를 가리키는지에 따라 다른 씬 출력
	else if (Input_GetKeyDown(VK_SPACE) && data->CursorPos.Y == SelectPosY)
	{
		storedId = ReturnSelectIndex(data->id, 0);
		Scene_SetNextScene(SCENE_CONTENT);
	}
	else if (Input_GetKeyDown(VK_SPACE) && data->CursorPos.Y == SelectPosY_1)
	{
		storedId = ReturnSelectIndex(data->id, 1);
		Scene_SetNextScene(SCENE_CONTENT);
	}
	else if (Input_GetKeyDown(VK_SPACE) && data->CursorPos.Y == SelectPosY_2)
	{
		storedId = ReturnSelectIndex(data->id, 2);
		Scene_SetNextScene(SCENE_CONTENT);
	}
}

void render_content(void)
{
	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->BackGroundImage, 0, 0);
	Renderer_DrawImage(&data->BackPaper, 0, 0);

	if (data->CursorPos.Y != 0) {
		Renderer_DrawImage(&data->CursorImage, data->CursorPos.X, data->CursorPos.Y);
	}

	if (TitleExisted(data->id))
	{
		SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextSolid(&data->TitleLine[0], 100, 30, color);
	}

	for (int32 i = 0; i < TEXTLINE_COUNT; ++i)
	{
		SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextSolid(&data->TextLine[i], 100, 150 + 40 * i, color);
	}

	for (int32 i = 0; i < 3; ++i) {
		// 한 화면에 텍스트가 10줄 이상일 때 예외 처리
		if (SelectExisted(data->id, i) && ReturnContentTextRow(data->id) >= LimitContentTextRow)
		{
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
			Renderer_DrawTextSolid(&data->SelectLine[i], 70, 620 + 60 * i, color);
		}
		else if (SelectExisted(data->id, i)) {
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
			Renderer_DrawTextSolid(&data->SelectLine[i], 70, 500 + 60 * i, color);
		}
	}

}

void release_content(void)
{
	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;

	Audio_FreeMusic(&data->BGM);
	for (int32 i = 0; i < 2; i++)
	{
		if (SoundEffectExisted(data->id, i))
		{
			Audio_FreeSoundEffect(&data->Effect[i]);
		}
	}
	
	SafeFree(g_Scene.Data);
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
	Image		BackPaper;
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
	Image_LoadImage(&data->BackGround, "TitleImage.png");
	Image_LoadImage(&data->BackPaper, "BackPaper.png");

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "GongGothicBold.ttf", 40, str2[i], wcslen(str2[i]));
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
int count = 0;

void render_ending(void)
{
	EndingSceneData* data = (EndingSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->BackGround, 0, 0);
	Renderer_DrawImage(&data->BackPaper, 0, 0);

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		if (900 - upPixel > 50)
		{
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
			Renderer_DrawTextSolid(&data->GuideLine[i], 75, 900 + 40 * i - upPixel, color);
		}
		else
		{
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
			Renderer_DrawTextSolid(&data->GuideLine[i], 75, 50 + 40 * i, color);
		}
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