#pragma once
class Transform
{
public:

	void Update();



public:
	// Parent 기준
	const vec3& GetLocalPosition() { return _localPosition; }
	const vec3& GetLocalRotation() { return _localRotation; }
	const vec3& GetLocalScale() { return _localScale; }

	const Matrix& GetLocalToWorldMatrix() { return _matWorld; }
	vec3 GetWorldPosition() { return _matWorld.Translation(); }

	vec3 GetRight() { return _matWorld.Left(); }
	vec3 GetUp() { return _matWorld.Up(); }
	vec3 GetLook() { return _matWorld.Forward(); }
	void SetLocalPosition(const vec3& position) { _localPosition = position; }
	void SetLocalRotation(const vec3& rotation) { _localRotation = rotation; }
	void SetLocalScale(const vec3& scale) { _localScale = scale; }
	Matrix& GetMatrix() { return _matWorld; }


public:
	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }
	weak_ptr<Transform> GetParent() { return _parent; }

	void SetTotalCenter(vec3 center) { _totalCenter = center; }
	void SetSize(vec3 size) { _totalSize = size; }

private:
	// Parent 기준
	vec3 _localPosition = {};
	vec3 _localRotation = {};
	vec3 _localRotation2 = {};
	vec3 _localScale = { 1.f, 1.f, 1.f };

	Matrix _matLocal = {};
	Matrix _matWorld = {};

	weak_ptr<Transform> _parent;

	vec3 _totalCenter{};
	vec3 _totalSize{};
	float _totalRadius{};
	
};

