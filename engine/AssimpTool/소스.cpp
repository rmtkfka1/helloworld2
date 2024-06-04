#include "pc.h"
#include "Converter.h"


int main()
{
	Converter converter;
	converter.ReadAssetFile(L"pressenter.fbx");
	converter.ExportMaterialData(L"pressenter6/pressenter");
	converter.ExportModelData(L"pressenter6/pressenter");
	converter.Clear();

};