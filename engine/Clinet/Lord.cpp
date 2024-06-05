#include "pch.h"
#include "Lord.h"
#include "StructedBuffer.h"
#include "Core.h"
#include "Component.h"
#include "Model.h"
#include "Mesh.h"
#include "Transform.h"
#include "TableHeap.h"
#include "Material.h"
Lord::Lord()
{
}

Lord::~Lord()
{
}

void Lord::Init()
{

	GameObject::Init();

	_data.resize(100);



	BufferInit(sizeof(InstanceData), 100);


	for (int i = 0; i < 100; ++i)
	{
		_data[i].worldmat = Matrix::CreateTranslation(vec3(0, 0, i*380));
	}

	PushData();
}

void Lord::Update()
{

	GameObject::Update();

}

void Lord::Render()
{

	
	for (auto& compoent : _component)
	{
		compoent->Render();
	}

	vector<shared_ptr<ModelMesh>>& meshData = _model->GetMeshes();

	for (auto& data : meshData)
	{
		core->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		D3D12_VERTEX_BUFFER_VIEW pVertexBufferViews[] = { data->meshes->GetVertexView(), _bufferView };
		core->GetCmdList()->IASetVertexBuffers(0, _countof(pVertexBufferViews), pVertexBufferViews);
		core->GetCmdList()->IASetIndexBuffer(&data->meshes->GetIndexView());

		_transform->Update();

		if (data->material)
		{
			data->material->Update();
		}

		core->GetCmdList()->SetGraphicsRootShaderResourceView(2, _buffer->GetGPUVirtualAddress());
		core->GetTableHeap()->SetGraphicsRootDescriptorTable();
		core->GetCmdList()->DrawIndexedInstanced(data->meshes->GetIndexCount(), 100, 0, 0, 0);
	}

}

void Lord::BufferInit(uint32 elementSize, uint32 elementCount)
{
	_elementSize = elementSize;
	_elementCount = elementCount;

	CreateBuffer();

}

void Lord::CreateBuffer()
{
	const uint64 bufferSize = _elementSize * _elementCount;
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	core->GetDevice()->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_buffer));
}

void Lord::PushData()
{
	const uint64 bufferSize = _elementSize * _elementCount;

	void* dataBuffer = nullptr;
	D3D12_RANGE readRange{ 0, 0 };
	_buffer->Map(0, &readRange, &dataBuffer);
	memcpy(dataBuffer, _data.data(), bufferSize);

	_bufferView.BufferLocation = _buffer->GetGPUVirtualAddress();
	_bufferView.StrideInBytes = _elementSize;
	_bufferView.SizeInBytes = bufferSize;

}
