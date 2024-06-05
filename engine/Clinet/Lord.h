#pragma once
#include "GameObject.h"

class StructedBuffer;

struct InstanceData
{
	Matrix worldmat;
};

class Lord : public GameObject
{

public:

	Lord();
	virtual ~Lord();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	vector<InstanceData> _data;

public:
	void BufferInit(uint32 elementSize, uint32 elementCount);
	void CreateBuffer();
	void PushData();

private:
	ComPtr<ID3D12Resource>		_buffer;
	D3D12_VERTEX_BUFFER_VIEW	_bufferView;

	uint32 _elementSize{};
	uint32 _elementCount{};
};

