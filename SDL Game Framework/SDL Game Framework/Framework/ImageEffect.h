#pragma once

#include "Type.h"
#include "Image.h"

// 랜덤 초기화
void ImageEffect_Init(void);

/// <summary>
/// 이미지 흐림효과를 처리한다.
/// </summary>
/// <param name="BackGround">이미지 소스</param>
/// <param name="maxExclusive">이미지 투명도</param>
void Fade_InOut(Image* BackGround, int32 Alpha);

/// <summary>
/// 이미지 사이즈를 자동으로 조절한다.
/// </summary>
/// <param name="BackGround">이미지 소스</param>
void Scale_UpDown(Image* BackGround);

/// <summary>
/// 이미지를 자동으로 이동한다.
/// </summary>
/// <param name="X">X 좌표</param>
void Move_LeftRight(int32 X);

