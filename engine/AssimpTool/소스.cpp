#include "pc.h"
#include "Converter.h"


int main()
{
	Converter converter;
	converter.ReadAssetFile(L"cutespaceship.fbx");
	converter.ExportMaterialData(L"car/car");
	converter.ExportModelData(L"car/car");




};