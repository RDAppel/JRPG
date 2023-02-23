
#include "_PCH.h"
#include "MapComponent.h"

MapComponent::MapComponent()
{
	// todo: remove this
	m_position = Vector2(100, 100);
}

MapComponent::~MapComponent()
{
	delete m_pIdleAnimations;
	delete m_pWalkAnimations;
	delete m_pRunAnimations;
}

void MapComponent::HandleInput(const InputState& input)
{
	m_previousInputDirection = m_inputDirection;
	m_inputDirection = Direction::NONE;

	double upSeconds = input.GetPressedKeySeconds(Key::UP);
	double downSeconds = input.GetPressedKeySeconds(Key::DOWN);
	double leftSeconds = input.GetPressedKeySeconds(Key::LEFT);
	double rightSeconds = input.GetPressedKeySeconds(Key::RIGHT);

	bool moving = upSeconds || downSeconds || leftSeconds || rightSeconds;
	if (!moving) return;

	m_isRunning = input.IsKeyModifierDown(KeyModifier::SHIFT);

	constexpr double MAX = (std::numeric_limits<double>::max)();
	if (!upSeconds) upSeconds = MAX;
	if (!downSeconds) downSeconds = MAX;
	if (!leftSeconds) leftSeconds = MAX;
	if (!rightSeconds) rightSeconds = MAX;

	double min = (std::min)({ upSeconds, downSeconds, leftSeconds, rightSeconds });
	if (min == upSeconds) m_inputDirection = Direction::UP;
	else if (min == downSeconds) m_inputDirection = Direction::DOWN;
	else if (min == leftSeconds) m_inputDirection = Direction::LEFT;
	else if (min == rightSeconds) m_inputDirection = Direction::RIGHT;
}

void MapComponent::Update(const GameTime& gameTime)
{
	m_pPreviousAnimation = m_pCurrentAnimation;
	uint8_t index = (uint8_t)m_currentDirection;
	if (m_state == MovementState::IDLE) m_pCurrentAnimation = (*m_pIdleAnimations)[index];
	else if (m_state == MovementState::WALKING) m_pCurrentAnimation = (*m_pWalkAnimations)[index];
	else if (m_state == MovementState::RUNNING) m_pCurrentAnimation = (*m_pRunAnimations)[index];

	m_state = MovementState::IDLE;

	if (m_pPreviousAnimation != m_pCurrentAnimation)
	{
		if (m_pPreviousAnimation)
			m_pPreviousAnimation->Stop();
		m_pCurrentAnimation->Play();
	}

	if (m_inputDirection == Direction::NONE)
	{
		m_pCurrentAnimation->Update(gameTime);
		m_movementTime = 0;
		return;
	}

	// if you're already facing the direction you started going you can instantly
	// start moving that direction
	if (m_inputDirection == m_currentDirection
		&& m_previousInputDirection == Direction::NONE) m_movementTime = TURN_THRESHOLD;
	else m_currentDirection = m_inputDirection;

	if (m_movementTime < TURN_THRESHOLD)
	{
		m_movementTime += (float)gameTime.GetTimeElapsed();
		m_pCurrentAnimation->Update(gameTime);
		return;
	}

	// actually moving
	Vector2 move;
	if (m_currentDirection == Direction::UP) move += -Vector2::UNIT_Y;
	if (m_currentDirection == Direction::DOWN) move += Vector2::UNIT_Y;
	if (m_currentDirection == Direction::LEFT) move += -Vector2::UNIT_X;
	if (m_currentDirection == Direction::RIGHT) move += Vector2::UNIT_X;

	float speed = m_isRunning ? m_runSpeed : m_walkSpeed;
	move *= speed * gameTime.GetTimeElapsed();
	m_position += move;

	m_state = m_isRunning
		? MovementState::RUNNING
		: MovementState::WALKING;

	m_pCurrentAnimation->Update(gameTime);
	m_previousInputDirection = Direction::NONE;
}

void MapComponent::Draw(SpriteBatch& spriteBatch)
{
	Vector2 center = m_pCurrentAnimation->GetCenter();
	spriteBatch.Draw(m_pCurrentAnimation, m_position, Color::WHITE, center);
}