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
wchar_t** ReturnContentText(int id)
{
	wchar_t str[10][1024] = {'0'};

	wchar_t* text;
	text = ParseToUnicode(csvFile.Items[id][2]);

	for (int i = 0; *text != L'\0';)
	{
		for (int j = 0; j < 1024; j++)
		{
			if (*text == L'\n')
			{
				i++;
				j = 0;
			}
			else
			{
				str[i][j] = *text;
			}
			text++;
		}
	}

	return str;
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