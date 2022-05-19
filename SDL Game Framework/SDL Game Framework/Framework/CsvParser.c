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

// ù��° ���� ��Ե� ���ڴµ� �ι�° ���� �� ������
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

int ReturnNextSceneNum(int id)
{
	int nextSceneNum;

	nextSceneNum = ParseToUnicode(csvFile.Items[id][5]);

	return nextSceneNum;
}

// ����� ��µȴ� Overture.mp3�� ���� �̻��ѵ�?
char* ReturnMusicName(int id)
{
	char* musicName;

	musicName = ParseToAscii(csvFile.Items[id][4]);

	return musicName;
}