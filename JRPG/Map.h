#pragma once

#include "_PCH.h"
#include "Layer.h"
#include "MapComponent.h"

class Map : public Resource
{

private:

	Vector2 m_dimensions = Vector2(80, 60);

	std::vector<Layer*> m_layers;

	std::vector<Texture*> m_textures;

	MapComponent* m_pMapComponent = nullptr;

	Camera m_camera;

public:

	virtual bool Load(const std::string& path) override;

	virtual void SetMapComponent(MapComponent* pMapComponent);

	virtual void HandleInput(const InputState& inputState);

	virtual void Update(const GameTime& gameTime);

	virtual void Draw(SpriteBatch& spriteBatch);

};

