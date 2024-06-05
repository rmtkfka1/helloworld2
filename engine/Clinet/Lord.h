#pragma once
#include "GameObject.h"

class StructedBuffer;

namespace LordInstance
{
	struct InstanceData
	{
		Matrix worldmat;
	};
}

class Lord : public GameObject
{

public:

	Lord();
	virtual ~Lord();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	vector<LordInstance::InstanceData> _data;
	shared_ptr<StructedBuffer> _buffer;
	const int InstanceCount = 50;


};

