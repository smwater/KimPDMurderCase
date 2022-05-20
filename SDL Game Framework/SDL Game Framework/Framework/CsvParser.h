#pragma once
#include "csv.h"

/// <summary>
/// csv파일을 분리해서 데이터를 저장한다.
/// </summary> 
void InitCsvParse(void);

/// <summary>
/// 현재 씬의 내용 텍스트를 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>내용 텍스트를 반환한다.</returns>
wchar_t** ReturnContentText(int id);

/// <summary>
/// 선택지1로 넘어가는 화면의 인덱스를 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>선택지1로 넘어가는 화면의 인덱스를 반환한다.</returns>
int ReturnSelect1Index(int id);

/// <summary>
/// 현재 씬의 음악 이름을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>현재 씬의 음악 이름을 반환한다.</returns>
char* ReturnBGMName(int id);

/// <summary>
/// 현재 씬의 배경 이미지 이름을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>현재 씬의 배경 이미지 이름을 반환한다.</returns>
char* ReturnBackGroundImage(int id);