

#include "_PCH.h"


Camera::Camera()
{
}

void Camera::SetTarget(ITargetable* pTarget, const bool moveTo)
{
	m_pTarget = pTarget;
	if (moveTo) m_position = m_pTarget->GetPosition();
}

void Camera::Update(const GameTime& gameTime)
{
	if (m_pTarget) m_position = m_pTarget->GetPosition();

	Vector2 halfScreen = Game::GetScreenSize() / 2 / m_scale;
	if (m_position.X > m_bounds.Width - halfScreen.X) m_position.X = m_bounds.Width - halfScreen.X;
	if (m_position.Y > m_bounds.Height - halfScreen.Y) m_position.Y = m_bounds.Height - halfScreen.Y;
	if (m_position.X < m_bounds.X + halfScreen.X) m_position.X = m_bounds.X + halfScreen.X;
	if (m_position.Y < m_bounds.Y + halfScreen.Y) m_position.Y = m_bounds.Y + halfScreen.Y;

	m_transform.Reset();
	m_transform.Translate(-m_position);
	m_transform.Scale(m_scale);
	m_transform.Rotate(0);
	m_transform.Translate(Game::GetScreenSize() / 2);

}