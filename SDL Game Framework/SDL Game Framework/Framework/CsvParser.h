#pragma once
#include "csv.h"

/// <summary>
/// csv������ �и��ؼ� �����͸� �����Ѵ�.
/// </summary> 
void InitCsvParse(void);

/// <summary>
/// ���� ���� ���� �ؽ�Ʈ�� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� �ؽ�Ʈ�� �� �پ� ��ȯ�Ѵ�.</returns>
wchar_t* ReturnTitleText(int32 id);

/// <summary>
/// ���� ���� ���� �ؽ�Ʈ�� �� �پ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� �ؽ�Ʈ�� �� �پ� ��ȯ�Ѵ�.</returns>
wchar_t* ReturnContentText(int32 id, int32 RowNum);

/// <summary>
/// ���� ���� ù��° �������� ������ ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>ù��° �������� ������ ��ȯ�Ѵ�.</returns>
wchar_t* ReturnSelect1(int32 id);

/// <summary>
/// ���� ���� �ι�° �������� ������ ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>�ι�° �������� ������ ��ȯ�Ѵ�.</returns>
wchar_t* ReturnSelect2(int32 id);

/// <summary>
/// ���� ���� ����° �������� ������ ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>����° �������� ������ ��ȯ�Ѵ�.</returns>
wchar_t* ReturnSelect3(int32 id);

/// <summary>
/// ������1�� �Ѿ�� ȭ���� �ε����� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>������1�� �Ѿ�� ȭ���� �ε����� ��ȯ�Ѵ�.</returns>
int32 ReturnSelect1Index(int32 id);

/// <summary>
/// ������2�� �Ѿ�� ȭ���� �ε����� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>������2�� �Ѿ�� ȭ���� �ε����� ��ȯ�Ѵ�.</returns>
int32 ReturnSelect2Index(int32 id);

/// <summary>
/// ������3���� �Ѿ�� ȭ���� �ε����� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>������3���� �Ѿ�� ȭ���� �ε����� ��ȯ�Ѵ�.</returns>
int32 ReturnSelect3Index(int32 id);

/// <summary>
/// ���� ���� ���� �̸��� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� ���� ���� �̸��� ��ȯ�Ѵ�.</returns>
char* ReturnBGM(int32 id);

/// <summary>
/// ���� ���� ù��° ȿ������ �̸��� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� ���� ù��° ȿ������ �̸��� ��ȯ�Ѵ�.</returns>
char* ReturnSoundEffect1(int32 id);

/// <summary>
/// ���� ���� �ι�° ȿ������ �̸��� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� ���� �ι�° ȿ������ �̸��� ��ȯ�Ѵ�.</returns>
char* ReturnSoundEffect2(int32 id);

/// <summary>
/// ���� ���� ��� �̹��� �̸��� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� ���� ��� �̹��� �̸��� ��ȯ�Ѵ�.</returns>
char* ReturnBackGroundImage(int32 id);