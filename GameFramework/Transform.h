#pragma once

class Transform
{

private:

	ALLEGRO_TRANSFORM m_transform;

public:

	static const Transform IDENTITY;

	Transform() { al_identity_transform(&m_transform); }

	void Scale(Vector2 scale) { al_scale_transform(&m_transform, scale.X, scale.Y); }

	void Rotate(float angle) { al_rotate_transform(&m_transform, angle); }

	void Translate(Vector2 translation) { al_translate_transform(&m_transform, translation.X, translation.Y); }

	void Reset() { al_identity_transform(&m_transform); }

	void Apply() const { al_use_transform(&m_transform); }
};
