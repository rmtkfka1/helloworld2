#include "pch.h"
#include "CameraManager.h"
#include "Core.h"
#include "ConstantBuffer.h"
#include "Scene.h"
#include "SceneManger.h"
#include "GameObject.h"
#include "Transform.h"
#include "ImguiManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include <random>

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);


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

    _cameraUp = vec3(0, 1.0f, 0);
}

void CameraManager::Update()
{

    //MouseUpdate();
    Animation();

    if (SceneManger::GetInstance()->GetSceneType() == SceneType::STAGE1)
    {
        if (KeyManager::GetInstance()->GetButtonDown(KEY_TYPE::Q))
        {
            flag = !flag;
        }

        if (flag)
        {
            _cameraLook = vec3(0, -0.5f, 1.0f);
            _cameraPos.x = ObjectManager::GetInstance()->player->_transform->GetLocalPosition().x;
            _cameraPos.y = ObjectManager::GetInstance()->player->_transform->GetLocalPosition().y + 300.0f;
            _cameraPos.z = ObjectManager::GetInstance()->player->_transform->GetLocalPosition().z - 600.0f;
        }
        else
        {
            _cameraLook = vec3(0.4f, -0.5f, -0.5f);
            _cameraPos.x = ObjectManager::GetInstance()->player->_transform->GetLocalPosition().x - 300.0f;
            _cameraPos.y = ObjectManager::GetInstance()->player->_transform->GetLocalPosition().y + 600.0f;
            _cameraPos.z = ObjectManager::GetInstance()->player->_transform->GetLocalPosition().z + 500.0f;
        }

        // �� ��� ������Ʈ
        S_MatView = DirectX::XMMatrixLookToLH(_cameraPos + _shake, _cameraLook, _cameraUp);

        // �������� ��� ������Ʈ
        if (_type == PROJECTION_TYPE::PERSPECTIVE)
            S_MatProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
        else
            S_MatProjection = ::XMMatrixOrthographicLH(_width * _scale, _height * _scale, _near, _far);

        _matView = S_MatView;
        _matProjection = S_MatProjection;

        ImguiManager::GetInstance()->_temp = _cameraPos;
    }


    else
    {
        _cameraLook = vec3(0, 0, 1.0f);
        _cameraPos = vec3(200.0f, 100.0f, -1000.0f);

        S_MatView = DirectX::XMMatrixLookToLH(_cameraPos, _cameraLook, _cameraUp);

        // �������� ��� ������Ʈ
        if (_type == PROJECTION_TYPE::PERSPECTIVE)
            S_MatProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
        else
            S_MatProjection = ::XMMatrixOrthographicLH(_width * _scale, _height * _scale, _near, _far);

        _matView = S_MatView;
        _matProjection = S_MatProjection;
    }

    ImguiManager::GetInstance()->_temp = _cameraPos;
}

void CameraManager::MouseUpdate()
{
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

void CameraManager::Animation()
{

    float dt = TimeManager::GetInstance()->GetDeltaTime();;

    if (_elaspedTime > 1.5f)
    {
        _animationflag = false;
        _elaspedTime = 0;
    }

    if (_animationflag)
    {
        float intenisty = 1000.0f;
        _shake.x = distribution(generator) * intenisty * dt;
        _shake.y = distribution(generator) * intenisty * dt;

        _elaspedTime += dt;
    }

}

