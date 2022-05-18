#pragma once

#include "Type.h"
#include "Image.h"



/// <summary>
/// 이미지 사이즈를 줄인다.
/// </summary>
/// <param name="BackGround">이미지 소스</param>
void Scale_Down(Image* BackGround);


/// <summary>
/// 이미지 사이즈를 올린다.
/// </summary>
/// <param name="BackGround">이미지 소스</param>
void Scale_Up(Image* BackGround);



/// <summary>
/// 이미지 점점 투명하게 처리한다.
/// </summary>
/// <param name="BackGround">이미지 소스</param>
/// <param name="maxExclusive">이미지 투명도</param>
void Fade_Out(Image* BackGround, int32 Alpha);



/// <summary>
/// 이미지를 점점 뚜렷하게 처리한다.
/// </summary>
/// <param name="BackGround">이미지 소스</param>
/// <param name="maxExclusive">이미지 투명도</param>
void Fade_In(Image* BackGround, int32 Alpha);



/// <summary>
/// 이미지를 왼쪽으로 이동
/// </summary>
/// <param name="X">X 좌표</param>
void Move_Left(Image* BackGround, int32 X, int32 Y);



/// <summary>
/// 이미지를 오른쪽으로 이동.
/// </summary>
/// <param name="X">X 좌표</param>
void Move_Right(Image* BackGround, int32 X, int32 Y);