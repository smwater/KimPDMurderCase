#include "stdafx.h"
#include "Scene.h"
#include "time.h"
#include "Framework.h"
#include "Common.h"
#include "Text.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

bool isScaleDown = false; // ���� ���� �۾��� ȿ��
bool isScaleUp = false; // ���� ���� Ŀ��
bool isFadeIn = false; // ���� ������� ȿ��
bool isFadeOut = false; // ���� ������� ȿ��
bool isLeftDisappear = false; // ���� �������� �������� ȿ��
bool isRightDisappear = false; // ���� ���������� �������� ȿ��

bool isShake = false; //���� ���� ȿ��
bool isTextCon = false; // �ؽ�Ʈ ����ϴ� ȿ��

int32 fadeCount = 0;
int32 moveCount = 0;
int32 scaleCount = 0;
int32 i = 0;

wchar_t str[100] = L"�ȳ��ϼ���.";
wchar_t newStr[100] = { '\0' };

const WCHAR* strJung = L"Hellow JUNG HUYNG DON";

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

const wchar_t* str[] = {
	L"����� Ÿ��Ʋ���Դϴ�. �ؽ�Ʈ�� ���õ� ���������� �׽�Ʈ�غ��ô�.",
	L"BŰ�� ������ ��Ʈ�� ���� ���մϴ�.",
	L"IŰ�� ������ ��Ʈ�� ���Ÿ�ü�� ���մϴ�.",
	L"UŰ�� ������ �ؽ�Ʈ�� ������ ����ϴ�.",
	L"SŰ�� ������ �ؽ�Ʈ�� ��Ҽ��� ����ϴ�.",
	L"NŰ�� ������ �ٽ� ������� ���ƿɴϴ�.",
	L"CŰ�� ������ ���� ��尡 �ٲ�ϴ�. (Solid -> Shaded -> Blended)",
	L"1Ű�� ������ �ؽ�Ʈ�� �۾����ϴ�.",
	L"2Ű�� ������ �ؽ�Ʈ�� Ŀ���ϴ�.",
	L"�����̽� Ű�� ������ ���� ������ �Ѿ�ϴ�."
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
	Text_CreateText(&data->TestText, "d2coding.ttf", data->FontSize, L"�� �ؽ�Ʈ�� ���մϴ�.", 13);
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
	L"���⼭�� ����� �̹��� ������ ���ؼ� �˾ƺ��ô�.",
	L"ȭ��ǥŰ�� �̹����� �̵���ų �� �ֽ��ϴ�.",
	L"EŰ�� ������ ����Ʈ�� �����ų �� �ֽ��ϴ�. ����Ʈ �Ҹ��� ������ ������ ���� �� �����ϼ���.",
	L"MŰ�� ������ ���ų� �� �� �ֽ��ϴ�.",
	L"PŰ�� ������ ���߰ų� �簳�� �� �ֽ��ϴ�.",
	L"1���� 2������ ������ ������ �� �ֽ��ϴ�.",
	L"WASD�� �̹����� �������� ������ �� �ֽ��ϴ�.",
	L"KLŰ�� �̹����� ������ ������ �� �ֽ��ϴ�."
};

const wchar_t* strMain[] = {
	L"2022�� 6�� 17��",
	L"MTBC ���ɱ� ����ç���� �� ȸ�ǽ� (��� ����)",
	L"�������, �̹� ��� �����Դϴ�. Ȯ���غ��ʽÿ�.(���� ����)",
	L"�����ڵ��� �ҷ����� �� �������� �ð̴ϴ�. (���� ����)",
	L"������ : ��PD / ���� / 47�� ���� / ��ȥ / SBC ��ä ��� PD",
	L"������ : MTBC ���ɱ� ����ç���� �� ȸ�ǽ�"
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

	// ********************** �������� �ؽ�Ʈ ��� �ʱ�ȭ �۾� ********************** 
	for (int32 i = 0; i < MAINLINE_COUNT; ++i)
	{
		Text_CreateText(&data->ConsecutiveText[i], "d2coding.ttf", 16, strMain[i], wcslen(strMain[i]));
	}

	// ********************** �������� �ؽ�Ʈ ��� �ʱ�ȭ �۾� ********************** 

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