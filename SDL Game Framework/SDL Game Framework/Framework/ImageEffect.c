#include <stdafx.h>
#include "Common.h"
#include "Input.h"
#include "ImageEffect.h"

bool isScaleDown = false; // 사진 점점 작아짐 효과
bool isScaleUp = false; // 사진 점점 커짐
bool isFadeIn = false; // 사진 밝아지는 효과
bool isFadeOut = false; // 사진 흐려지는 효과
bool isLeftDisappear = false; // 사진 왼쪽으로 없어지는 효과
bool isRightDisappear = false; // 사진 오른쪽으로 없어지는 효과

float addSecond = 0.0f;

void Scale_Down(Image* BackGround)
{


	if (Input_GetKey(VK_F1))
	{
		isScaleDown = true;
	}

	if (isScaleDown)
	{
		addSecond += Timer_GetDeltaTime();
		BackGround->ScaleX -= 0.1 * (int)Timer_GetDeltaTime();
		BackGround->ScaleY -= 0.1 * (int)Timer_GetDeltaTime();
		if (addSecond > 40)
		{
			isScaleDown = false;
			addSecond = 0;
		}
	}
}

void Scale_Up(Image* BackGround)
{


	if (Input_GetKey(VK_F2))
	{
		isScaleUp = true;
	}

	if (isScaleUp)
	{
		addSecond += Timer_GetDeltaTime();
		BackGround->ScaleX += 0.1 * (int)Timer_GetDeltaTime();
		BackGround->ScaleY += 0.1 * (int)Timer_GetDeltaTime();
		if (addSecond > 40)
		{
			isScaleUp = false;
			addSecond = 0;
		}
	}
}

void Fade_Out(Image* BackGround, int32 Alpha)
{
	if (Input_GetKey(VK_F3))
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
}

void Fade_In(Image* BackGround, int32 Alpha)
{


	if (Input_GetKey(VK_F4))
	{
		isFadeIn = true;
	}

	if (isFadeIn)
	{
		Alpha = 20;
		addSecond += Timer_GetDeltaTime();
		Alpha = Clamp(0, Alpha + addSecond, 255);
		Image_SetAlphaValue(BackGround, Alpha);
		if (Alpha > 253)
		{
			isFadeIn = false;
			addSecond = 0.0f;
		}
	}
}

//void Move_Left(Image* BackGround, int32 X, int32 Y)
//{
//
//
//	if (Input_GetKey(VK_F5))
//	{
//		isLeftDisappear = true;
//	}
//
//	if (isLeftDisappear)
//	{
//		addSecond += Timer_GetDeltaTime();
//		X -= (int)Timer_GetDeltaTime() * 0.3;
//		if (X < 100)
//		{
//			isLeftDisappear = false;
//			addSecond = 0;
//		}
//	}
//}
//
//void Move_Right(Image* BackGround, int32 X, int32 Y)
//{
//
//
//	if (Input_GetKey(VK_F6))
//	{
//		isRightDisappear = true;
//	}
//
//	if (isRightDisappear)
//	{
//		addSecond += Timer_GetDeltaTime();
//		X += (int)Timer_GetDeltaTime() * 0.3;
//		if (X > 600)
//		{
//			isRightDisappear = false;
//			addSecond = 0;
//		}
//	}
//}

