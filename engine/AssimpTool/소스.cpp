#include "pc.h"
#include "Converter.h"
#include <random>
default_random_engine dre;

uniform_int_distribution<int> uid(0, 3);
int main()
{
	Converter converter;
	converter.ReadAssetFile(L"horror/source/KepleriansTeam_Madeline.fbx");
	converter.ExportMaterialData(L"horror/horror");
	converter.ExportModelData(L"horror/horror");

	
};