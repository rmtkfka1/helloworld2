#include "pch.h"
#include "CameraManager.h"
#include "Core.h"
#include "ConstantBuffer.h"
#include "Scene.h"
#include "SceneManger.h"
#include "GameObject.h"
#include "Transform.h"
#include "ImguiManager.h"

using namespace DirectX::SimpleMath;

Matrix CameraManager::S_MatView;
Matrix CameraManager::S_MatProjection;

void CameraManager::Clear()
{
    // Clear function implementation (if needed)
}

void CameraManager::Init()
{
    _width = static_cast<float>(core->GetWindowInfo().width);
    _height = static_cast<float>(core->GetWindowInfo().height);
    SetCursor(LoadCursor(NULL, IDC_ARROW)); // �⺻ ȭ��ǥ Ŀ���� ����
    GetWindowRect(GetForegroundWindow(), &_rect);
    _centerScreen = { (_rect.right + _rect.left) / 2, (_rect.bottom + _rect.top) / 2 };
    _mousePos = _centerScreen;
    _cameraPos = vec3(0, 0, 0);
    _cameraLook = vec3(0, 0, -1.0f); // �⺻���� �ٶ󺸴� �������� ���� (0, 0, -1)
    _cameraUp = vec3(0, 1.0f, 0);
}

void CameraManager::Update()
{
    if (KeyManager::GetInstance()->GetButtonDown(KEY_TYPE::Q)) {
        flag = !flag;
    }

    if (flag)
    {
        return;
    }

    MouseUpdate();

    // ȸ�� ��� ���� �� ī�޶� ���� ���� ������Ʈ
    Matrix rotationMatrix = Matrix::CreateRotationX(XMConvertToRadians(_cameraPitch));
    rotationMatrix *= Matrix::CreateRotationY(XMConvertToRadians(_cameraYaw));
    _cameraLook = Vector3::TransformNormal(vec3(0, 0, 1.0f), rotationMatrix);

    // �̵� ó��
    float speed = 1000.0f * TimeManager::GetInstance()->GetDeltaTime();

    if (KeyManager::GetInstance()->GetButton(KEY_TYPE::W))
    {
        _cameraPos += _cameraLook * speed;
    }
    if (KeyManager::GetInstance()->GetButton(KEY_TYPE::S))
    {
        _cameraPos -= _cameraLook * speed;
    }

    vec3 _cameraRight = -_cameraLook.Cross(_cameraUp);

    if (KeyManager::GetInstance()->GetButton(KEY_TYPE::D))
    {
        _cameraPos += _cameraRight * speed;
    }
    if (KeyManager::GetInstance()->GetButton(KEY_TYPE::A))
    {
        _cameraPos -= _cameraRight * speed;
    }

    // �� ��� ������Ʈ
    S_MatView = DirectX::XMMatrixLookToLH(_cameraPos, _cameraLook, _cameraUp);

    // �������� ��� ������Ʈ
    if (_type == PROJECTION_TYPE::PERSPECTIVE)
        S_MatProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
    else
        S_MatProjection = ::XMMatrixOrthographicLH(_width * _scale, _height * _scale, _near, _far);

    _matView = S_MatView;
    _matProjection = S_MatProjection;


    ImguiManager::GetInstance()->_temp = _cameraPos;
}

void CameraManager::MouseUpdate()
{
    // ���콺 ��ġ ������Ʈ
    _mousePos = KeyManager::GetInstance()->GetMousePos();

    // ȭ�� �߽ɰ��� ���� ���
    float deltaPosX = static_cast<float>(_mousePos.x - _centerScreen.x);
    float deltaPosY = static_cast<float>(_mousePos.y - _centerScreen.y);

    // �ð� ���� ���
    float dt = TimeManager::GetInstance()->GetDeltaTime();

    // Yaw�� Pitch ������Ʈ
    _cameraYaw += deltaPosX * _cameraSpeed * dt;
    _cameraPitch += deltaPosY * _cameraSpeed * dt;

    // Pitch ����
    if (_cameraPitch > 89.0f) _cameraPitch = 89.0f;
    if (_cameraPitch < -89.0f) _cameraPitch = -89.0f;

    if (_cameraYaw < 0.0f) _cameraYaw += 360.0f;
    if (_cameraYaw > 360.0f) _cameraYaw -= 360.0f;

    // ���콺 Ŀ�� ��ġ �缳��
    SetCursorPos(static_cast<int>(_centerScreen.x), static_cast<int>(_centerScreen.y));
}