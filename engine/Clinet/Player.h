#pragma once
#include "GameObject.h"

enum class state
{
	one,
	two,
	three,
	four
};

class Player : public GameObject
{

public:

	Player();
	virtual ~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:

	float _speed = 0;


};

