#pragma once
#include "csv.h"

/// <summary>
/// csv파일을 분리해서 데이터를 저장한다.
/// </summary> 
void InitCsvParse(void);

/// <summary>
/// 내용 텍스트를 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>내용 텍스트를 반환한다.</returns>
Text ReturnContentText(int id);

/// <summary>
/// 다음 씬의 인덱스를 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>다음 씬의 인덱스를 반환한다.</returns>
int ReturnNextSceneNum(int id);