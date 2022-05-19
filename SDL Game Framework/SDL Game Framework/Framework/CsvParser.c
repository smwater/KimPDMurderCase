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

Text ReturnContentText(int id)
{
	Text	 paragraph;
	wchar_t* text;

	text = ParseToUnicode(csvFile.Items[id][2]);
	// 

	return paragraph;
}

int ReturnNextSceneNum(int id)
{
	int nextSceneNum;

	nextSceneNum = ParseToUnicode(csvFile.Items[id][5]);

	return nextSceneNum;
}