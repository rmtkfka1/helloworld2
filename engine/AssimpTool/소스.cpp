#include "pc.h"
#include "Converter.h"


int main()
{
	Converter converter;
	converter.ReadAssetFile(L"Tank/Tank.fbx");
	converter.ExportMaterialData(L"Tank/Tank");
	converter.ExportModelData(L"Tank/Tank");



};