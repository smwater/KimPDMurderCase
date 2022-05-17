#include <stdafx.h>
#include "Common.h"
#include "Input.h"
#include "ImageEffect.h"

bool isScaleDown = false; // ���� ���� �۾��� ȿ��
bool isScaleUp = false; // ���� ���� Ŀ��
bool isFadeIn = false; // ���� ������� ȿ��
bool isFadeOut = false; // ���� ������� ȿ��
bool isLeftDisappear = false; // ���� �������� �������� ȿ��
bool isRightDisappear = false; // ���� ���������� �������� ȿ��


float addSecond = 0.0f;

void Fade_InOut(Image* BackGround, int32 Alpha)
{

	if (Input_GetKey(VK_F3) && !isFadeOut)
	{
		isFadeOut = true;
	}

	if (isFadeOut)
	{
		addSecond += Timer_GetDeltaTime();
		Alpha = Clamp(0, Alpha - addSecond, 255);
		Image_SetAlphaValue(BackGround, Alpha);
		if (Alpha < 50)
		{
			isFadeOut = false;
			addSecond = 0.0f;
		}
	}

	if (Input_GetKey(VK_F4) && !isFadeIn)
	{
		isFadeIn = true;
	}

	if (isFadeIn)
	{
		addSecond += Timer_GetDeltaTime();
		Alpha = Clamp(0, Alpha + addSecond, 50);
		Image_SetAlphaValue(BackGround, Alpha);
		if (Alpha > 253)
		{
			isFadeIn = false;
			addSecond = 0.0f;
		}
	}
}

void Scale_UpDown(Image* BackGround)
{
	addSecond += Timer_GetDeltaTime();

	if (Input_GetKey(VK_F1))
	{
		isScaleUp = true;
	}

	if (Input_GetKey(VK_F2))
	{
		isScaleDown = true;
	}


	if (isScaleDown)
	{
		BackGround->ScaleX -= (0.05f * Timer_GetDeltaTime());
		BackGround->ScaleY -= (0.05f * Timer_GetDeltaTime());
		if (addSecond > 40)
		{
			isScaleDown = false;
			addSecond = 0;
		}
	}

	if (isScaleUp)
	{
		BackGround->ScaleX += (0.05f * Timer_GetDeltaTime());
		BackGround->ScaleY += (0.05f * Timer_GetDeltaTime());
		if (addSecond > 40)
		{
			isScaleUp = false;
			addSecond = 0;
		}
	}
}

void Move_LeftRight(Image* BackGround, int32 X, int32 Y)
{
	addSecond += Timer_GetDeltaTime();

	if (Input_GetKey(VK_F5))
	{
		isLeftDisappear = true;
	}

	if (Input_GetKey(VK_F6))
	{
		isRightDisappear = true;
	}


	if (isLeftDisappear)
	{
		X -= Timer_GetDeltaTime() * 0.3;
		if (X < 100)
		{
			isLeftDisappear = false;
			addSecond = 0;
		}
	}

	if (isRightDisappear)
	{
		X += Timer_GetDeltaTime() * 0.3;
		if (X > 600)
		{
			isRightDisappear = false;
			addSecond = 0;
		}
	}
}
