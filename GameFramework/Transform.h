
#pragma once

class Transform
{

private:

	ALLEGRO_TRANSFORM m_transform;

public:

	static const Transform IDENTITY;

	Transform() { Reset(); }

	void Reset() { al_identity_transform(&m_transform); }

	void Translate(Vector2 translation) { al_translate_transform(&m_transform, translation.X, translation.Y); }

	void Scale(Vector2 scale) { al_scale_transform(&m_transform, scale.X, scale.Y); }

	void Scale(float scale) { al_scale_transform(&m_transform, scale, scale); }

	void Rotate(float angle) { al_rotate_transform(&m_transform, angle); }

	void Apply() const { al_use_transform(&m_transform); }

};

