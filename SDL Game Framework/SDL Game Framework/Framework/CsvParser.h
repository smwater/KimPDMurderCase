#pragma once
#include "csv.h"

/// <summary>
/// csv������ �и��ؼ� �����͸� �����Ѵ�.
/// </summary> 
void InitCsvParse(void);

/// <summary>
/// ���� ���� ���� �ؽ�Ʈ�� �� �پ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� �ؽ�Ʈ�� �� �پ� ��ȯ�Ѵ�.</returns>
wchar_t* ReturnContentText(int32 id, int32 RowNum);

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
/// ���� ���� ���� �̸��� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� ���� ���� �̸��� ��ȯ�Ѵ�.</returns>
char* ReturnBGMName(int32 id);

/// <summary>
/// ���� ���� ��� �̹��� �̸��� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� ���� ��� �̹��� �̸��� ��ȯ�Ѵ�.</returns>
char* ReturnBackGroundImage(int32 id);