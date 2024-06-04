#pragma once
#include "Scripts.h"
class SunScript :public Scripts
{
public:
	virtual void Update() override;

private:
	float _lotate{};
};

