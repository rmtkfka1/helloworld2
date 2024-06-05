#include "pch.h"
#include "CameraManager.h"
#include "Core.h"
#include "ConstantBuffer.h"
#include "Scene.h"
#include "SceneManger.h"
#include "GameObject.h"
#include "Transform.h"


using namespace DirectX::SimpleMath;

Matrix CameraManager::S_MatView;
Matrix CameraManager::S_MatProjection;


void CameraManager::Clear()
{

}

void CameraManager::Init()
{
    _width = static_cast<float>(core->GetWindowInfo().width);
    _height = static_cast<float>(core->GetWindowInfo().height);
    SetCursor(LoadCursor(NULL, IDC_ARROW)); // 기본 화살표 커서로 변경
    GetWindowRect(GetForegroundWindow(), &_rect);
    _centerScreen = { (_rect.right + _rect.left) / 2, (_rect.bottom + _rect.top) / 2 };
    _mousePos = _centerScreen;
    _cameraLook = vec3(0, 1.0f, 1.0f);
    _cameraUp = vec3(0, 1.0f, 0);
}

void CameraManager::Update()
{
    MouseUpdate();

    S_MatView = DirectX::XMMatrixLookToLH(_cameraPos, _cameraLook, _cameraUp);

    if (_type == PROJECTION_TYPE::PERSPECTIVE)
        S_MatProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
    else
        S_MatProjection = ::XMMatrixOrthographicLH(_width * _scale, _height * _scale, _near, _far);

    _matView = S_MatView;
    _matProjection = S_MatProjection;
}

void CameraManager::MouseUpdate()
{

    _mousePos = KeyManager::GetInstance()->GetMousePos();

    float deltaPosX = static_cast<float>(_mousePos.x - _centerScreen.x);
    float deltaPosY = static_cast<float>(_mousePos.y - _centerScreen.y);

    float dt = TimeManager::GetInstance()->GetDeltaTime();

    _cameraYaw += deltaPosX * _cameraSpeed * dt;
    _cameraPitch -= deltaPosY * _cameraSpeed * dt;

    if (_cameraPitch > 89.0f) _cameraPitch = 89.0f;
    if (_cameraPitch < -89.0f) _cameraPitch = -89.0f;

    vec3 look = vec3(0, 0, 1.0f);
    vec3 pos = vec3(0, 0, -50.0f);
    Matrix  mat = Matrix::CreateRotationY(XMConvertToRadians(_cameraYaw));

    _cameraLook = vec3::Transform(look, mat);
    _cameraPos = vec3::Transform(pos, mat);

    SetCursorPos(_centerScreen.x, _centerScreen.y);
}



