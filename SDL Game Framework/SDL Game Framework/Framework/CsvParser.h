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
/// <returns>제목 텍스트를 반환한다.</returns>
wchar_t* ReturnTitleText(int32 id);

/// <summary>
/// 현재 씬에서 타이틀이 존재하는지 확인한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>타이틀이 존재하면 true, 아니면 false.</returns>
bool TitleExisted(int32 id);

/// <summary>
/// 현재 씬의 내용 텍스트를 한 줄 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <param name="RowNum">반환하고 싶은 줄 수</param>
/// <returns>내용 텍스트를 한 줄 반환한다.</returns>
wchar_t* ReturnContentText(int32 id, int32 RowNum);

/// <summary>
/// 현재 씬의 내용 텍스트가 몇 줄인지 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>내용 텍스트의 줄 수를 반환한다.</returns>
int32 ReturnContentTextRow(int32 id);

/// <summary>
/// 현재 씬의 선택지의 내용을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <param name="selectNum">출력하고 싶은 선택지의 번호</param>
/// <returns>현재 씬의 선택지 내용을 반환한다.</returns>
wchar_t* ReturnSelect(int32 id, int32 selectNum);

/// <summary>
/// 현재 씬에서 선택지가 존재하는지 확인한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <param name="selectNum">존재하는지 확인하고 싶은 선택지의 번호</param>
/// <returns>선택지가 존재하면 true, 아니면 false.</returns>
bool SelectExisted(int32 id, int32 selectNum);

/// <summary>
/// 선택지로 넘어가는 화면의 인덱스를 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <param name="selectNum">선택지의 번호</param>
/// <returns>선택지로 넘어가는 화면의 인덱스를 반환한다.</returns>
int32 ReturnSelectIndex(int32 id, int32 selectNum);

/// <summary>
/// 현재 씬의 음악 이름을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>현재 씬의 음악 이름을 반환한다.</returns>
char* ReturnBGM(int32 id);

/// <summary>
/// 현재 씬의 효과음의 이름을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <param name="selectNum">출력하고 싶은 효과음의 번호</param>
/// <returns>현재 씬의 효과음의 이름을 반환한다.</returns>
char* ReturnSoundEffect(int32 id, int32 effectNum);

/// <summary>
/// 현재 씬에서 효과음이 존재하는지 확인한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <param name="selectNum">존재하는지 확인하고 싶은 효과음의 번호</param>
/// <returns>효과음이 존재하면 true, 아니면 false.</returns>
bool SoundEffectExisted(int32 id, int32 effectNum);

/// <summary>
/// 현재 씬의 배경 이미지 이름을 반환한다.
/// </summary>
/// <param name="id">현재 씬의 인덱스</param>
/// <returns>현재 씬의 배경 이미지 이름을 반환한다.</returns>
char* ReturnBackGroundImage(int32 id);

char* ReturnPortraitImg(int32 id);

char* ReturnEvidenceImg(int32 id);

bool portraitImageExisted(int32 id);

bool EvidenceImgeExisted(int32 id);