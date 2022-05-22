#include "stdafx.h"
#include "CsvParser.h"
#include "Text.h"

#include <crtdbg.h>

CsvFile csvFile;

void InitCsvParse(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	memset(&csvFile, 0, sizeof(CsvFile));
	CreateCsvFile(&csvFile, "test.csv");
}

wchar_t* ReturnTitleText(int32 id)
{
	// 함수 밖에서도 주소값이 존재하게 만들기 위해 static 선언
	static wchar_t titleText[128] = { L"\0" };

	// static 변수는 매번 초기화되지 않으므로 수동 초기화
	for (int32 i = 0; i < 128; i++)
	{
		titleText[i] = L'\0';
	}
	
	wchar_t* temp = ParseToUnicode(csvFile.Items[id][1]);

	// 문자열 복사
	int count = 0;
	while (*temp != L'\0')
	{
		titleText[count] = *temp;
		count++;
		temp++;
	}

	return titleText;
}

bool TitleExisted(int32 id)
{
	if (NULL == *(ParseToUnicode(csvFile.Items[id][1])))
	{
		return false;
	}

	return true;
}

wchar_t* ReturnContentText(int32 id, int32 RowNum)
{
	// 함수 밖에서도 주소값이 존재하게 만들기 위해 static 선언
	static wchar_t finishedText[128] = { L"\0" };
	
	// static 변수는 매번 초기화되지 않으므로 수동 초기화
	for (int32 i = 0; i < 128; i++)
	{
		finishedText[i] = L'\0';
	}

	wchar_t* nowCharacter = ParseToUnicode(csvFile.Items[id][2]);

	// 원하는 줄에 도달했다면 데이터를 저장하기 위해 줄 세는 변수 추가
	int32 row = 0;

	while (*nowCharacter != L'\0')
	{
		for (int32 lineText = 0; lineText < 128; lineText++)
		{
			if (*nowCharacter == L'\0')
			{
				return finishedText;
			}
			// 개행을 만나면 줄 수 추가
			// 다음 줄로 넘어갔을 때 다른 자리에서 시작하지 않기 위해 -1로 초기화
			else if (*nowCharacter == L'\n')
			{
				row++;
				lineText = -1;
			}
			else if (row == RowNum)
			{
				// 줄 구분용 쌍따옴표는 인식하지 않는다
				if (*nowCharacter == L'\"')
				{
					lineText--;
				}
				// 목표로 하는 가로줄과 현재 가로줄의 수가 동일할 때 텍스트 저장
				else
				{
					finishedText[lineText] = *nowCharacter;
				}
			}
			if (row > RowNum)
			{
				return finishedText;
			}
			nowCharacter++;
		}
	}

	return finishedText;
}

int32 ReturnContentTextRow(int32 id)
{
	wchar_t* nowCharacter = ParseToUnicode(csvFile.Items[id][2]);

	int32 row = 0;

	while (*nowCharacter != L'\0')
	{
		if (*nowCharacter == L'\n')
		{
			row++;
		}
		nowCharacter++;
	}

	return row + 1;
}

wchar_t* ReturnSelect(int32 id, int32 selectNum)
{
	// 함수 밖에서도 주소값이 존재하게 만들기 위해 static 선언
	static wchar_t selectText[128] = { L"\0" };

	// static 변수는 매번 초기화되지 않으므로 수동 초기화
	for (int32 i = 0; i < 128; i++)
	{
		selectText[i] = L'\0';
	}

	wchar_t* temp = ParseToUnicode(csvFile.Items[id][3 + selectNum]);

	// 문자열 복사
	int count = 0;
	while (*temp != L'\0')
	{
		selectText[count] = *temp;
		count++;
		temp++;
	}

	return selectText;
}

bool SelectExisted(int32 id, int32 selectNum)
{
	if (NULL == *(ParseToUnicode(csvFile.Items[id][3 + selectNum])))
	{
		return false;
	}

	return true;
}

int32 ReturnSelectIndex(int32 id, int32 selectNum)
{
	int SelectIndex;

	SelectIndex = ParseToInt(csvFile.Items[id][6 + selectNum]);

	return SelectIndex + 1;
}

char* ReturnBGM(int32 id)
{
	char* BGM;

	BGM = ParseToAscii(csvFile.Items[id][9]);

	return BGM;
}

char* ReturnSoundEffect(int32 id, int32 effectNum)
{
	char* SoundEffect;

	SoundEffect = ParseToAscii(csvFile.Items[id][10 + effectNum]);

	return SoundEffect;
}

// 갓중재께서 해결해주심
bool SoundEffectExisted(int32 id, int32 effectNum)
{
	if (NULL == *(ParseToUnicode(csvFile.Items[id][10 + effectNum])))
	{
		return false;
	}

	return true;
}

char* ReturnBackGroundImage(int32 id)
{
	char* BackGroundImageName;

	BackGroundImageName = ParseToAscii(csvFile.Items[id][12]);

	return BackGroundImageName;
}