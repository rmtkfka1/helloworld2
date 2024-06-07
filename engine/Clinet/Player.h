#pragma once
#include "GameObject.h"



class Player : public GameObject
{

public:

	Player();
	virtual ~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:

	float _speed = 0;

	virtual void OnComponentBeginOverlap(shared_ptr<BaseCollider> collider, shared_ptr<BaseCollider>other);
	virtual void OnComponentEndOverlap(shared_ptr<BaseCollider> collider, shared_ptr<BaseCollider> other);

};

