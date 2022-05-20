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
/// <returns>���� �ؽ�Ʈ�� ��ȯ�Ѵ�.</returns>
wchar_t** ReturnContentText(int id);

/// <summary>
/// ������1�� �Ѿ�� ȭ���� �ε����� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>������1�� �Ѿ�� ȭ���� �ε����� ��ȯ�Ѵ�.</returns>
int ReturnSelect1Index(int id);

/// <summary>
/// ���� ���� ���� �̸��� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� ���� ���� �̸��� ��ȯ�Ѵ�.</returns>
char* ReturnBGMName(int id);

/// <summary>
/// ���� ���� ��� �̹��� �̸��� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� ���� ��� �̹��� �̸��� ��ȯ�Ѵ�.</returns>
char* ReturnBackGroundImage(int id);