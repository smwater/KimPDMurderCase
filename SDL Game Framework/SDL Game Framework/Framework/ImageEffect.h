#pragma once

#include "Type.h"
#include "Image.h"

// ���� �ʱ�ȭ
void ImageEffect_Init(void);

/// <summary>
/// �̹��� �帲ȿ���� ó���Ѵ�.
/// </summary>
/// <param name="BackGround">�̹��� �ҽ�</param>
/// <param name="maxExclusive">�̹��� ����</param>
void Fade_InOut(Image* BackGround, int32 Alpha);

/// <summary>
/// �̹��� ����� �ڵ����� �����Ѵ�.
/// </summary>
/// <param name="BackGround">�̹��� �ҽ�</param>
void Scale_UpDown(Image* BackGround);

/// <summary>
/// �̹����� �ڵ����� �̵��Ѵ�.
/// </summary>
/// <param name="X">X ��ǥ</param>
void Move_LeftRight(int32 X);

