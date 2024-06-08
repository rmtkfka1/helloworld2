#pragma once

class GameObject;

class Scene
{

public:
	Scene();
	virtual ~Scene();

	virtual void Init(); 
	virtual void Update();  //��ü����
	virtual void LateUpdate(); //��ü �޸� �߰� ����
	virtual void Render(); //������
	virtual void ClearScene(); //������ , ���̵� , �����ִ� �޸𸮻���

	vector<shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }
	void ReserveAddGameObject(shared_ptr<GameObject> object);
	void ReserveDeleteGameObject(shared_ptr<GameObject> object);
	void AddGameObject(shared_ptr<GameObject> object);
	void DeleteGameObject(shared_ptr<GameObject> object);

protected:
	vector<shared_ptr<GameObject>> _gameObjects;
	queue<shared_ptr<GameObject>> _reserveAddQueue;
	queue<shared_ptr<GameObject>> _reserveDeleteQueue;
	
public:

	bool _sceneEnd = false;

};

