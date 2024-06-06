#pragma once
#include "GameObject.h"
class Lamp :public GameObject
{

public:

	Lamp();
	virtual ~Lamp();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	vector<InstanceData> _data;
	shared_ptr<StructedBuffer> _buffer;
	const int InstanceCount = 40;

};

