#pragma once

#include "Type.h"
#include "Image.h"



/// <summary>
/// �̹��� ����� ���δ�.
/// </summary>
/// <param name="BackGround">�̹��� �ҽ�</param>
void Scale_Down(Image* BackGround);


/// <summary>
/// �̹��� ����� �ø���.
/// </summary>
/// <param name="BackGround">�̹��� �ҽ�</param>
void Scale_Up(Image* BackGround);



/// <summary>
/// �̹��� ���� �����ϰ� ó���Ѵ�.
/// </summary>
/// <param name="BackGround">�̹��� �ҽ�</param>
/// <param name="maxExclusive">�̹��� ����</param>
void Fade_Out(Image* BackGround, int32 Alpha);



/// <summary>
/// �̹����� ���� �ѷ��ϰ� ó���Ѵ�.
/// </summary>
/// <param name="BackGround">�̹��� �ҽ�</param>
/// <param name="maxExclusive">�̹��� ����</param>
void Fade_In(Image* BackGround, int32 Alpha);



/// <summary>
/// �̹����� �������� �̵�
/// </summary>
/// <param name="X">X ��ǥ</param>
void Move_Left(Image* BackGround, int32 X, int32 Y);



/// <summary>
/// �̹����� ���������� �̵�.
/// </summary>
/// <param name="X">X ��ǥ</param>
void Move_Right(Image* BackGround, int32 X, int32 Y);