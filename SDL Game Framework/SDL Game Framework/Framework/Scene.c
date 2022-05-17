#include "stdafx.h"
#include "Scene.h"
#include "time.h"
#include "Framework.h"
#include "Common.h"
#include "Text.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

bool isScaleDown = false; // 사진 점점 작아짐 효과
bool isScaleUp = false; // 사진 점점 커짐
bool isFadeIn = false; // 사진 밝아지는 효과
bool isFadeOut = false; // 사진 흐려지는 효과
bool isLeftDisappear = false; // 사진 왼쪽으로 없어지는 효과
bool isRightDisappear = false; // 사진 오른쪽으로 없어지는 효과

bool isShake = false; //사진 지진 효과
bool isTextCon = false; // 텍스트 출력하는 효과

int32 fadeCount = 0;
int32 moveCount = 0;
int32 scaleCount = 0;
int32 i = 0;

wchar_t str[100] = L"안녕하세요.";
wchar_t newStr[100] = { '\0' };

const WCHAR* strJung = L"Hellow JUNG HUYNG DON";

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

const wchar_t* str[] = {
	L"여기는 타이틀씬입니다. 텍스트와 관련된 여러가지를 테스트해봅시다.",
	L"B키를 누르면 폰트가 굵게 변합니다.",
	L"I키를 누르면 폰트가 이탤릭체로 변합니다.",
	L"U키를 누르면 텍스트에 밑줄이 생깁니다.",
	L"S키를 누르면 텍스트에 취소선이 생깁니다.",
	L"N키를 누르면 다시 원래대로 돌아옵니다.",
	L"C키를 누르면 렌더 모드가 바뀝니다. (Solid -> Shaded -> Blended)",
	L"1키를 누르면 텍스트가 작아집니다.",
	L"2키를 누르면 텍스트가 커집니다.",
	L"스페이스 키를 누르면 다음 씬으로 넘어갑니다."
};

typedef struct TitleSceneData
{
	Text	GuideLine[10];
	Text	TestText;
	int32	FontSize;
	int32	RenderMode;
	Image	TestImage;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	for (int32 i = 0; i < 10; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str[i], wcslen(str[i]));
	}

	data->FontSize = 24;
	Text_CreateText(&data->TestText, "d2coding.ttf", data->FontSize, L"이 텍스트가 변합니다.", 13);
	data->RenderMode = SOLID;

	Image_LoadImage(&data->TestImage, "Background.jfif");
}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	if (Input_GetKeyDown('B'))
	{
		Text_SetFontStyle(&data->TestText, FS_BOLD);
	}

	if (Input_GetKeyDown('I'))
	{
		Text_SetFontStyle(&data->TestText, FS_ITALIC);
	}

	if (Input_GetKeyDown('U'))
	{
		Text_SetFontStyle(&data->TestText, FS_UNDERLINE);
	}

	if (Input_GetKeyDown('S'))
	{
		Text_SetFontStyle(&data->TestText, FS_STRIKETHROUGH);
	}

	if (Input_GetKeyDown('N'))
	{
		Text_SetFontStyle(&data->TestText, FS_NORMAL);
	}

	if (Input_GetKeyDown('C'))
	{
		data->RenderMode = (data->RenderMode + 1) % 3;
	}

	if (Input_GetKeyDown('R'))
	{
		for (int i = 0; i < 10; i++)
		{
			Text_SetFontStyle(&data->GuideLine[i], FS_STRIKETHROUGH);
		}
	}

	if (Input_GetKey('1'))
	{
		--data->FontSize;
		Text_SetFont(&data->TestText, "d2coding.ttf", data->FontSize);
	}

	if (Input_GetKey('2'))
	{
		++data->FontSize;
		Text_SetFont(&data->TestText, "d2coding.ttf", data->FontSize);
	}

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	for (int32 i = 0; i < 10; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);

	}

	switch (data->RenderMode)
	{
	case SOLID:
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->TestText, 400, 400, color);
	}
	break;
	case SHADED:
	{
		SDL_Color bg = { .a = 255 };
		SDL_Color fg = { .r = 255, .g = 255, .a = 255 };
		Renderer_DrawTextShaded(&data->TestText, 400, 400, fg, bg);
	}
	break;
	case BLENDED:
	{
		Renderer_DrawImage(&data->TestImage, 400, 400);
		SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextBlended(&data->TestText, 400, 400, color);
	}
	break;
	}
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	for (int32 i = 0; i < 10; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Text_FreeText(&data->TestText);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region MainScene


const wchar_t* str2[] = {
	L"여기서는 사운드와 이미지 블렌딩에 대해서 알아봅시다.",
	L"화살표키로 이미지를 이동시킬 수 있습니다.",
	L"E키를 누르면 이펙트를 재생시킬 수 있습니다. 이펙트 소리가 작으니 볼륨을 낮춘 후 진행하세요.",
	L"M키로 음악을 끄거나 켤 수 있습니다.",
	L"P키로 음악을 멈추거나 재개할 수 있습니다.",
	L"1번과 2번으로 볼륨을 조절할 수 있습니다.",
	L"WASD로 이미지의 스케일을 조정할 수 있습니다.",
	L"KL키로 이미지의 투명도를 조절할 수 있습니다."
};

const wchar_t* strMain[] = {
	L"2022년 6월 17일",
	L"MTBC 예능국 유한챌린지 팀 회의실 (사건 현장)",
	L"강형사님, 이번 사건 파일입니다. 확인해보십시오.(후임 형사)",
	L"용의자들을 불렀으니 곧 현장으로 올겁니다. (후임 형사)",
	L"피해자 : 김PD / 남성 / 47세 남성 / 미혼 / SBC 공채 출신 PD",
	L"사망장소 : MTBC 예능국 유한챌린지 팀 회의실"
};

#define GUIDELINE_COUNT 8
#define MAINLINE_COUNT 6

typedef struct MainSceneData
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

	Text		ConsecutiveText[6][128];

} MainSceneData;

void logOnFinished(void)
{
	LogInfo("You can show this log on stopped the music");
}

void log2OnFinished(int32 channel)
{
	LogInfo("You can show this log on stopped the effect");
}

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, sizeof(MainSceneData));

	// ************* TEST *******************
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	// ************* TEST *******************

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str2[i], wcslen(str2[i]));
	}

	// ********************** 연속적인 텍스트 출력 초기화 작업 ********************** 
	for (int32 i = 0; i < MAINLINE_COUNT; ++i)
	{
		Text_CreateText(&data->ConsecutiveText[i], "d2coding.ttf", 16, strMain[i], wcslen(strMain[i]));
	}

	// ********************** 연속적인 텍스트 출력 초기화 작업 ********************** 

	Image_LoadImage(&data->BackGround, "jung.jfif");

	Audio_LoadMusic(&data->BGM, "powerful.mp3");
	Audio_HookMusicFinished(logOnFinished);
	Audio_LoadSoundEffect(&data->Effect, "effect2.wav");
	Audio_HookSoundEffectFinished(log2OnFinished);
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);

	data->Volume = 1.0f;

	data->Speed = 400.0f;
	data->X = 500;
	data->Y = 200;
	data->Alpha = 255;
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	clock_t currentTick = clock();

	if (Input_GetKeyDown('E'))
	{
		Audio_PlaySoundEffect(&data->Effect, 1);
	}

	if (Input_GetKeyDown('M'))
	{
		if (Audio_IsMusicPlaying())
		{
			Audio_Stop();
		}
		else
		{
			Audio_Play(&data->BGM, INFINITY_LOOP);
		}
	}

	if (Input_GetKeyDown('P'))
	{
		if (Audio_IsMusicPaused())
		{
			Audio_Resume();
		}
		else
		{
			Audio_Pause();
		}
	}

	if (Input_GetKey('1'))
	{
		data->Volume -= 0.01f;
		Audio_SetVolume(data->Volume);
	}

	if (Input_GetKey('2'))
	{
		data->Volume += 0.01f;
		Audio_SetVolume(data->Volume);
	}

	if (Input_GetKey(VK_DOWN))
	{
		data->Y += data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_UP))
	{
		data->Y -= data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_LEFT))
	{
		data->X -= data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_RIGHT))
	{
		data->X += data->Speed * Timer_GetDeltaTime();
	}

	// ****************** Image Scale Effect ******************************
	if (Input_GetKey('W'))
	{
		data->BackGround.ScaleY -= 0.05f;
	}

	if (Input_GetKey('S'))
	{
		data->BackGround.ScaleY += 0.05f;
	}

	if (Input_GetKey('A'))
	{
		data->BackGround.ScaleX -= 0.05f;
	}

	if (Input_GetKey('D'))
	{
		data->BackGround.ScaleX += 0.05f;
	}

	if (Input_GetKey(VK_F1))
	{
		isScaleUp = true;
		isScaleDown = false;
	}

	if (Input_GetKey(VK_F2))
	{
		isScaleDown = true;
		isScaleUp = false;
	}
	++scaleCount;
	if (isScaleDown)
	{
		data->BackGround.ScaleX -= (0.0005f * scaleCount);
		data->BackGround.ScaleY -= (0.0005f * scaleCount);
		if (scaleCount > 40)
		{
			isScaleDown = false;
			scaleCount = 0;
		}
	}

	if (isScaleUp)
	{
		data->BackGround.ScaleX += (0.0005f * scaleCount);
		data->BackGround.ScaleY += (0.0005f * scaleCount);
		if (scaleCount > 40)
		{
			isScaleUp = false;
			scaleCount = 0;
		}
	}
	// ****************** Image Scale Effect ******************************





	// ****************** Image Fade Effect ******************************

	++fadeCount;
	if (Input_GetKey('K'))
	{
		data->Alpha = Clamp(0, data->Alpha - 1, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
	}

	if (Input_GetKey('L'))
	{
		data->Alpha = Clamp(0, data->Alpha + 1, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
	}

	if (Input_GetKey(VK_F3) && !isFadeOut)
	{
		isFadeOut = true;
		isFadeIn = false;
	}

	if (Input_GetKey(VK_F4) && !isFadeIn)
	{
		isFadeIn = true;
		isFadeOut = false;
	}

	if (isFadeOut)
	{
		data->Alpha = Clamp(0, data->Alpha - Timer_GetDeltaTime() * 50, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
		if (data->Alpha < 50)
		{
			isFadeOut = false;
		}
	}

	if (isFadeIn)
	{
		data->Alpha = Clamp(0, data->Alpha + Timer_GetDeltaTime() * 100, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
		if (data->Alpha > 253)
		{
			isFadeIn = false;
		}
	}

	// ****************** Image Fade Effect ******************************



	// ****************** Image Left / RightDisappear Effect ******************************

	if (Input_GetKey(VK_F5))
	{
		isLeftDisappear = true;
	}

	if (Input_GetKey(VK_F6))
	{
		isRightDisappear = true;
	}

	++moveCount;
	if (isLeftDisappear)
	{
		data->X -= moveCount * 0.3;
		if (data->X < 100)
		{
			isLeftDisappear = false;
		}
	}

	if (isRightDisappear)
	{
		data->X += moveCount * 0.3;
		if (data->X > 600)
		{
			isRightDisappear = false;
		}
	}

	// ****************** Image LeftDisappear Effect ******************************



	// ****************** Text Effect ******************************
	if (Input_GetKey(VK_RETURN))
	{
		isTextCon = true;
		//s_prevTick = clock();
	}
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);
	}

	// ****************** Font Effect ******************************

	if (isTextCon)
	{
		setlocale(LC_ALL, "kr_KR.utf8");
		wcsncpy(newStr, str, i);
		TTF_Font* font = TTF_OpenFont("UnDotum.ttf", 28);
		SDL_Color color = { .a = 255 };

		Renderer_DrawTextSolid2(newStr, 10, 20 * i, color, font);

		if (str[i] != '\0')
		{
			isTextCon = false;
			i = 0;
		}
		i++;
	}

	// ****************** Font Effect ******************************

	Renderer_DrawImage(&data->BackGround, data->X, data->Y);
}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

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
	case SCENE_MAIN:
		g_Scene.Init = init_main;
		g_Scene.Update = update_main;
		g_Scene.Render = render_main;
		g_Scene.Release = release_main;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}