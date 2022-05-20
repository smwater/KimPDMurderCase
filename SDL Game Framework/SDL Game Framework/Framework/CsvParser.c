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

// 첫번째 줄은 어떻게든 빼겠는데 두번째 줄이 안 빠진다
// 당연함 Text는 한 줄만 받음
wchar_t* ReturnContentText(int32 id, int32 RowNum)
{
	static wchar_t finishedText[128] = { L"\0" };
	
	for (int32 i = 0; i < 128; i++)
	{
		finishedText[i] = L'\0';
	}

	wchar_t* nowCharacter;
	nowCharacter = ParseToUnicode(csvFile.Items[id][2]);

	int32 row = 0;

	while (*nowCharacter != L'\0')
	{
		for (int32 lineText = 0; lineText < 128; lineText++)
		{
			if (*nowCharacter == L'\0')
			{
				return finishedText;
			}
			else if (*nowCharacter == L'\n')
			{
				row++;
				lineText = -1;
			}
			else if (row == RowNum)
			{
				if (*nowCharacter == L'\"')
				{
					lineText--;
				}
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

// ParseToUnicord : L"1"
// ParseToAscii   :  "1"
// ParseToInt     :   1
int ReturnSelect1Index(int id)
{
	int Select1Index;

	Select1Index = ParseToInt(csvFile.Items[id][4]);

	return Select1Index;
}

int ReturnSelect2Index(int id)
{
	int Select2Index;

	Select2Index = ParseToInt(csvFile.Items[id][5]);

	return Select2Index;
}

char* ReturnBGMName(int id)
{
	char* BGMName;

	BGMName = ParseToAscii(csvFile.Items[id][7]);

	return BGMName;
}

char* ReturnBackGroundImage(int id)
{
	char* BackGroundImageName;

	BackGroundImageName = ParseToAscii(csvFile.Items[id][8]);

	return BackGroundImageName;
}