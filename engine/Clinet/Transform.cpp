#include "pch.h"
#include "Transform.h"
#include "Core.h"
#include "ConstantBuffer.h"
#include "CameraManager.h"
void Transform::Update()
{
	Matrix matTranslationBack = Matrix::CreateTranslation(-(_totalCenter));
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRotation = Matrix::CreateRotationX(XMConvertToRadians(_localRotation.x));
	matRotation *= Matrix::CreateRotationY(XMConvertToRadians(_localRotation.y));
	matRotation *= Matrix::CreateRotationZ(XMConvertToRadians(_localRotation.z));
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);


	_matLocal = matScale * matRotation * matTranslation;
	_matWorld = _matLocal; 


	shared_ptr<Transform> parent = GetParent().lock();
	if (parent != nullptr)
	{
		_matWorld *= parent->GetLocalToWorldMatrix();
	}


	TransformParams transformParams = {};
	transformParams.matWorld = _matWorld;
	transformParams.matView = CameraManager::S_MatView;
	transformParams.matProjection = CameraManager::S_MatProjection;

	core->GetConstantBuffer(CBV_REGISTER::b1)->PushData(&transformParams, sizeof(transformParams));

}


