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
	static wchar_t titleText[128] = { L"\0" };
	
	wchar_t* temp = ParseToUnicode(csvFile.Items[id][1]);

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
	if (ParseToUnicode(csvFile.Items[id][1]))
	{
		return false;
	}

	return true;
}

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

wchar_t* ReturnSelect1(int32 id)
{
	wchar_t* select1;

	select1 = ParseToUnicode(csvFile.Items[id][3]);

	return select1;
}

wchar_t* ReturnSelect2(int32 id)
{
	wchar_t* select2;

	select2 = ParseToUnicode(csvFile.Items[id][4]);

	return select2;
}

wchar_t* ReturnSelect3(int32 id)
{
	wchar_t* select3;

	select3 = ParseToUnicode(csvFile.Items[id][5]);

	return select3;
}

int32 ReturnSelect1Index(int32 id)
{
	int Select1Index;

	Select1Index = ParseToInt(csvFile.Items[id][6]);

	return Select1Index;
}

int32 ReturnSelect2Index(int32 id)
{
	int Select2Index;

	Select2Index = ParseToInt(csvFile.Items[id][7]);

	return Select2Index;
}

int32 ReturnSelect3Index(int32 id)
{
	int Select3Index;

	Select3Index = ParseToInt(csvFile.Items[id][8]);

	return Select3Index;
}

char* ReturnBGM(int32 id)
{
	char* BGM;

	BGM = ParseToAscii(csvFile.Items[id][9]);

	return BGM;
}

char* ReturnSoundEffect1(int32 id)
{
	char* SoundEffect1;

	SoundEffect1 = ParseToAscii(csvFile.Items[id][10]);

	return SoundEffect1;
}

char* ReturnSoundEffect2(int32 id)
{
	char* SoundEffect2;

	SoundEffect2 = ParseToAscii(csvFile.Items[id][11]);

	return SoundEffect2;
}

char* ReturnBackGroundImage(int32 id)
{
	char* BackGroundImageName;

	BackGroundImageName = ParseToAscii(csvFile.Items[id][12]);

	return BackGroundImageName;
}