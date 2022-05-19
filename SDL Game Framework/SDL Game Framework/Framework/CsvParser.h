#pragma once
#include "csv.h"

/// <summary>
/// csv������ �и��ؼ� �����͸� �����Ѵ�.
/// </summary> 
void InitCsvParse(void);

/// <summary>
/// ���� �ؽ�Ʈ�� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� �ؽ�Ʈ�� ��ȯ�Ѵ�.</returns>
Text ReturnContentText(int id);

/// <summary>
/// ���� ���� �ε����� ��ȯ�Ѵ�.
/// </summary>
/// <param name="id">���� ���� �ε���</param>
/// <returns>���� ���� �ε����� ��ȯ�Ѵ�.</returns>
int ReturnNextSceneNum(int id);