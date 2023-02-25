
#pragma once

class Camera
{

private:

	ITargetable* m_pTarget = nullptr;

	Vector2 m_position = Vector2(0, 0);

	Transform m_transform;

	Region m_bounds;

	Vector2 m_scale = Vector2::ONE;

	float m_speed = 1;

public:

	void Update(const GameTime& gameTime);

	void SetTarget(ITargetable* pTarget) { m_pTarget = pTarget; }

	void SetPosition(const Vector2& position) { m_position = position; }

	void SetBounds(const Region& bounds) { m_bounds = bounds; }

	void SetScale(const Vector2& scale) { m_scale = scale; }

	void SetScale(const float scale) { m_scale = Vector2(scale, scale); }

	void SetSpeed(const float speed) { m_speed = speed; }

	const Vector2& GetScale() const { return m_scale; }

	const Vector2& GetPosition() const { return m_position; }

	const Transform& GetTransform() const { return m_transform; }

};

