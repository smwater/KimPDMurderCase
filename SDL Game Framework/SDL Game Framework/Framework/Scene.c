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

	// 커서 이동범위 제한 
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

	// 커서 위치에 따라 다음 씬 출력
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

	// 등장인물 사진, 증거물 사진
	Image PortraitImage;
	Image EvidenceImage;

	// 연출 효과 데이터
	float timerTitle;
	float timerContent;
	float timerImage;

	float timerPortraitImage;
	float timerEvidenceImage;

	bool isTextTitleEffect;
	bool isTextLineEffect;
	bool isTextLineMaintain;

	bool isPortraitImageFix;
	bool isEvidenceImageFix;

	
	int32 TextLineCount;
	int32 TimerCount;

	Uint8 Alpha;

} ContentSceneData;

// 다음씬의 id를 저장하는 변수
// 처음에는 첫 장면을 출력하기 위해 1을 입력한다.
int32 storedId = 1;
char prevBGM = 'B';

void init_content(void)
{
	g_Scene.Data = malloc(sizeof(ContentSceneData));
	memset(g_Scene.Data, 0, sizeof(ContentSceneData));

	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;

	data->id = storedId;

	Image_LoadImage(&data->BackGroundImage, ReturnBackGroundImage(data->id));
	Image_LoadImage(&data->BackPaper, "BackPaper.png");
	Image_LoadImage(&data->CursorImage, "CursorImage.png");


	Image_LoadImage(&data->PortraitImage, ReturnPortraitImg(data->id)); // 등장인물 사진 가져오기
	Image_LoadImage(&data->EvidenceImage, ReturnEvidenceImg(data->id)); // 증거물 사진 가져오기


	data->CursorPos.X = 0;
	data->CursorPos.Y = 0;

	// 연출 효과 초기화.
	data->timerTitle = 0.0f;
	data->timerContent = 1.0f;
	data->timerImage = 0.0f;

	data->timerPortraitImage = 0.0f;
	data->timerEvidenceImage = 0.0f;

	data->isTextTitleEffect = true; 
	data->isTextLineEffect = false; 
	data->isTextLineMaintain = false;

	data->isPortraitImageFix = false;
	data->isEvidenceImageFix = false;


	data->TextLineCount = ReturnContentTextRow(data->id);
	data->TimerCount = 0;

	data->Alpha = 50;

	// 이전 씬과 음악이 다르다면 다른 음악을 출력한다.
	char* nowBGM = ReturnBGM(data->id);
	if (*nowBGM != prevBGM)
	{
		Audio_LoadMusic(&data->BGM, nowBGM);
		Audio_Play(&data->BGM, INFINITY_LOOP);
		
		prevBGM = *nowBGM;
	}
	
	//for (int32 i = 0; i < 2; i++)
	//{
	//	if (SoundEffectExisted(data->id, i))
	//	{
	//		Audio_LoadSoundEffect(&data->Effect[i], ReturnSoundEffect(data->id, i));
	//		Audio_PlaySoundEffect(&data->Effect[i], INFINITY_LOOP);
	//	}
	//}

	//if (TitleExisted(data->id))
	//{
	//	wchar_t* title = ReturnTitleText(data->id);
	//	Text_CreateText(&data->TitleLine[0], "GongGothicMedium.ttf", 40, title, wcslen(title));
	//}

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

#define LimitContentTextRow 9

void update_content(void)
{
	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;
	
	// 선택지 갯수에 따른 커서 이동범위 제한
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

	// 인물 사진 효과

	if (!(data->isPortraitImageFix))
	{
		data->timerPortraitImage += Timer_GetDeltaTime() * 1000;
		Renderer_DrawImage(&data->PortraitImage, 1000, 900 - data->timerPortraitImage);

		if (data->timerPortraitImage >= 840)
		{
			data->isPortraitImageFix = true;
		}
	}

	if (data->isPortraitImageFix)
	{
		Renderer_DrawImage(&data->PortraitImage, 1000, 900 - data->timerPortraitImage);
	}
	

	//// 증거물 사진 효과

	if (!(data->isEvidenceImageFix))
	{
		data->timerEvidenceImage += Timer_GetDeltaTime() * 1000;
		Renderer_DrawImage(&data->EvidenceImage, 850, 800 - data->timerEvidenceImage);

		if (data->timerEvidenceImage >= 500)
		{
			data->isEvidenceImageFix = true;
		}
	}

	if (data->isEvidenceImageFix)
	{
		Renderer_DrawImage(&data->EvidenceImage, 850, 800 - data->timerEvidenceImage);
	}



	if (data->CursorPos.Y != 0) {
		Renderer_DrawImage(&data->CursorImage, data->CursorPos.X, data->CursorPos.Y);
	}

	//if (TitleExisted(data->id))
	//{
	//	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	//	Renderer_DrawTextSolid(&data->TitleLine[0], 100, 30, color);
	//}

	//for (int32 i = 0; i < TEXTLINE_COUNT; ++i)
	//{
	//	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	//	Renderer_DrawTextSolid(&data->TextLine[i], 100, 150 + 40 * i, color);
	//}

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

	// 씬전환 백그라운드 이미지 Fade / IN

	data->timerImage += Timer_GetDeltaTime() * 20;

	data->Alpha = Clamp(0, data->Alpha + data->timerImage, 255);
	Image_SetAlphaValue(&data->BackGroundImage, data->Alpha);

	if (data->Alpha > 253)
	{
		data->timerImage = 0.0f;
	}


	// 한 글자씩 출력하는 효과

	if (data->isTextTitleEffect)
	{
		data->timerTitle += Timer_GetDeltaTime();

		if (data->timerTitle > 0.1f)
		{
			if (TitleExisted(data->id))
			{
				wchar_t* title = ReturnTitleText(data->id);
				Text_CreateText(&data->TitleLine[0], "GongGothicMedium.ttf", 40, title, data->TimerCount);

				if ((int)data->timerTitle == wcslen(title))
				{
					data->isTextTitleEffect = false;
					data->isTextLineEffect = true;
				}

				data->timerTitle = 0;
			}
			data->TimerCount++;
		}
	}

	if (TitleExisted(data->id))
	{
		SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextSolid(&data->TitleLine[0], 100, 30, color);
	}


	// 한줄씩 출력하는 효과

	if (data->isTextLineEffect = true || !(TitleExisted(data->id)))
	{
		data->timerContent += Timer_GetDeltaTime();
		for (int32 i = 0; i < (int)data->timerContent; ++i)
		{
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = data->timerContent * 256 };
			Renderer_DrawTextSolid(&data->TextLine[i], 100, 150 + 40 * i, color);
		}

		for (int32 i = 0; i < (int)data->timerContent - 1; ++i)
		{
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
			Renderer_DrawTextSolid(&data->TextLine[i], 100, 150 + 40 * i, color);
		}
	}

	if ((data->isTextLineMaintain))
	{
		for (int32 i = 0; i < TEXTLINE_COUNT; ++i)
		{
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
			Renderer_DrawTextSolid(&data->TextLine[i], 100, 150 + 40 * i, color);
		}
	}

	if ((int)data->timerContent == data->TextLineCount)
	{
		data->isTextLineMaintain = true;
		data->timerContent = 0;
	}

}


void release_content(void)
{
	ContentSceneData* data = (ContentSceneData*)g_Scene.Data;

	// 이전 음악과 다를 때만 정리해준다
	char* nowBGM = ReturnBGM(data->id);
	if (*nowBGM != prevBGM)
	{
		Audio_FreeMusic(&data->BGM);
	}
	
	//for (int32 i = 0; i < 2; i++)
	//{
	//	if (SoundEffectExisted(data->id, i))
	//	{
	//		Audio_FreeSoundEffect(&data->Effect[i]);
	//	}
	//}

	Text_FreeText(&data->TitleLine[0]);

	for (int32 i = 0; i < TEXTLINE_COUNT; i++)
	{
		Text_FreeText(&data->TextLine[i]);
	}

	for (int32 i = 0; i < 3; i++)
	{
		Text_FreeText(&data->SelectLine[i]);
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
	Text		EndingLine[ENDINGLINE_COUNT];
	Music		BGM;
	float		Volume;
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

	for (int32 i = 0; i < ENDINGLINE_COUNT; ++i)
	{
		Text_CreateText(&data->EndingLine[i], "GongGothicBold.ttf", 40, str2[i], wcslen(str2[i]));
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

// 엔딩씬 위로 상승하는 효과를 위한 변수
int upPixel = 0;

void render_ending(void)
{
	EndingSceneData* data = (EndingSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->BackGround, 0, 0);
	Renderer_DrawImage(&data->BackPaper, 0, 0);

	for (int32 i = 0; i < ENDINGLINE_COUNT; ++i)
	{
		if (900 - upPixel > 50)
		{
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
			Renderer_DrawTextSolid(&data->EndingLine[i], 75, 900 + 40 * i - upPixel, color);
		}
		else
		{
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
			Renderer_DrawTextSolid(&data->EndingLine[i], 75, 50 + 40 * i, color);
		}
	}

	upPixel += 5;
}

void release_ending(void)
{
	EndingSceneData* data = (EndingSceneData*)g_Scene.Data;

	for (int32 i = 0; i < ENDINGLINE_COUNT; ++i)
	{
		Text_FreeText(&data->EndingLine[i]);
	}
	Audio_FreeMusic(&data->BGM);

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