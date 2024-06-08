#pragma once
#include "GameObject.h"
class Ghost:public GameObject
{

public:

	Ghost();
	virtual ~Ghost();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	float _speed = 250.0f;

	virtual void OnComponentBeginOverlap(shared_ptr<BaseCollider> collider, shared_ptr<BaseCollider>other);
	virtual void OnComponentEndOverlap(shared_ptr<BaseCollider> collider, shared_ptr<BaseCollider> other);
	
};

