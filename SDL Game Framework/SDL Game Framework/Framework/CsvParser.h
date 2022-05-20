#pragma once
#include "csv.h"

/// <summary>
/// csv파일을 분리해서 데이터를 저장한다.
/// </summary> 
void InitCsvParse(void);

/// <summary>
/// 현재 씬의 제목 텍스트를 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>제목 텍스트를 한 줄씩 반환한다.</returns>
wchar_t* ReturnTitleText(int32 id);

/// <summary>
/// 현재 씬의 내용 텍스트를 한 줄씩 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>내용 텍스트를 한 줄씩 반환한다.</returns>
wchar_t* ReturnContentText(int32 id, int32 RowNum);

/// <summary>
/// 현재 씬의 첫번째 선택지의 내용을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>첫번째 선택지의 내용을 반환한다.</returns>
wchar_t* ReturnSelect1(int32 id);

/// <summary>
/// 현재 씬의 두번째 선택지의 내용을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>두번째 선택지의 내용을 반환한다.</returns>
wchar_t* ReturnSelect2(int32 id);

/// <summary>
/// 현재 씬의 세번째 선택지의 내용을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>세번째 선택지의 내용을 반환한다.</returns>
wchar_t* ReturnSelect3(int32 id);

/// <summary>
/// 선택지1로 넘어가는 화면의 인덱스를 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>선택지1로 넘어가는 화면의 인덱스를 반환한다.</returns>
int32 ReturnSelect1Index(int32 id);

/// <summary>
/// 선택지2로 넘어가는 화면의 인덱스를 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>선택지2로 넘어가는 화면의 인덱스를 반환한다.</returns>
int32 ReturnSelect2Index(int32 id);

/// <summary>
/// 선택지3으로 넘어가는 화면의 인덱스를 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>선택지3으로 넘어가는 화면의 인덱스를 반환한다.</returns>
int32 ReturnSelect3Index(int32 id);

/// <summary>
/// 현재 씬의 음악 이름을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>현재 씬의 음악 이름을 반환한다.</returns>
char* ReturnBGM(int32 id);

/// <summary>
/// 현재 씬의 첫번째 효과음의 이름을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>현재 씬의 첫번째 효과음의 이름을 반환한다.</returns>
char* ReturnSoundEffect1(int32 id);

/// <summary>
/// 현재 씬의 두번째 효과음의 이름을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>현재 씬의 두번째 효과음의 이름을 반환한다.</returns>
char* ReturnSoundEffect2(int32 id);

/// <summary>
/// 현재 씬의 배경 이미지 이름을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>현재 씬의 배경 이미지 이름을 반환한다.</returns>
char* ReturnBackGroundImage(int32 id);