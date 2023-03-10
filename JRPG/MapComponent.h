#pragma once

#include "_PCH.h"
#include "Component.h"

class MapComponent : public Component, public ITargetable
{
	enum class MovementState { IDLE, WALKING, RUNNING };

	// todo: remove this when we can load properly
	friend class JRPG;

private:

	const float TURN_THRESHOLD = 0.1f;

	typedef std::unordered_map<Direction, Animation*> AnimationMap;
	AnimationMap m_idleAnimations;
	AnimationMap m_walkAnimations;
	AnimationMap m_runAnimations;
	std::unordered_map<MovementState, AnimationMap*> m_animationMaps;

	Animation* m_pCurrentAnimation = m_pCurrentAnimation = nullptr;
	Animation* m_pPreviousAnimation = m_pCurrentAnimation = nullptr;

	Vector2 m_position;
	MovementState m_state = MovementState::IDLE;

	Direction m_inputDirection = Direction::NONE;
	Direction m_previousInputDirection = Direction::DOWN;
	Direction m_currentDirection = Direction::DOWN;

	float m_movementTime = 0;

	float m_walkSpeed = 70.0;
	float m_runSpeed = 230.0;

	bool m_isRunning = false;
	bool m_isInteracting = false;

public:

	MapComponent();
	MapComponent(const MapComponent&) = delete;
	virtual ~MapComponent();

	MapComponent& operator=(const MapComponent&) = delete;

	virtual Type GetType() const { return Type::MAP; }

	virtual void HandleInput(const InputState& input);

	virtual void Update(const GameTime& gameTime);

	virtual void Draw(SpriteBatch& spriteBatch);

	virtual Vector2 GetPosition() const { return m_position; }


};

