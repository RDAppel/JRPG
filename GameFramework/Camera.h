#pragma once

#include "_PCH.h"

class Camera
{

private:

	ITargetable* m_pTarget = nullptr;

	Region m_bounds;
	Vector2 m_position;

	Vector2 m_scale = Vector2::ONE;
	float m_speed = 1;

	Transform m_transform;

public:

	Camera();

	void Update(const GameTime& gameTime);

	void SetTarget(ITargetable* pTarget, bool moveTo = false);

	void SetBounds(const Region& bounds) { m_bounds = bounds; }

	void SetPosition(const Vector2& position) { m_position = position; }

	void SetScale(const Vector2& scale) { m_scale = scale; }

	void SetSpeed(const float speed) { m_speed = speed; }

	const Transform& GetTransform() const { return m_transform; }

	const Vector2& GetPosition() const { return m_position; }

	const Vector2& GetScale() const { return m_scale; }

	Vector2 GetScreenToWorldPosition(const Vector2& screenPosition) const;

};

