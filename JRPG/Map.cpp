
#include "_PCH.h"

#include "Map.h"
#include "Tile.h"

bool Map::Load(const std::string& path)
{
	std::ifstream fileIn(path.c_str(), std::ifstream::in);
	//if (!fileIn.is_open() || !fileIn.good()) return false;
	auto error = [&fileIn]() { fileIn.close(); return false; };

	m_pTexture = m_pResourceManager->Load<Texture>("Textures\\Tilesets\\Exterior_01.png");
	if (!m_pTexture) return error();
	m_textures.push_back(m_pTexture);

	Layer* pBackground = new Layer();
	pBackground->SetType(Layer::Type::BACKGROUND);
	
	uint32_t count = m_dimensions.X * m_dimensions.Y;
	for (uint32_t i = 0; i < count; ++i)
	{
		pBackground->AddTile(0, i);
	}
	m_layers.push_back(pBackground);

	Layer* pForeground = new Layer();
	pForeground->SetType(Layer::Type::FOREGROUND);
	pForeground->AddTile(0, 0);
	m_layers.push_back(pForeground);

	m_camera.SetScale(Vector2::ONE * 0.5f);
	m_camera.SetBounds(Region(0, 0, m_dimensions.X * Tile::SIZE, m_dimensions.Y * Tile::SIZE));

	fileIn.close();
	return true;
}

void Map::SetMapComponent(MapComponent* pMapComponent)
{
	m_pMapComponent = pMapComponent;
	m_camera.SetTarget(pMapComponent, true);
}

void Map::HandleInput(const InputState& inputState)
{
	m_pMapComponent->HandleInput(inputState);
}

void Map::Update(const GameTime& gameTime)
{
	m_pMapComponent->Update(gameTime);
	m_camera.Update(gameTime);
}

void Map::Draw(SpriteBatch& spriteBatch)
{
	Layer::Type type = Layer::Type::BACKGROUND;

	spriteBatch.Begin(SpriteSortMode::DEFERRED, BlendState::ALPHA, &m_camera.GetTransform());

	Vector2 scaledTileSize = Tile::SIZE * m_camera.GetScale();
	Vector2 cameraTilePosition = m_camera.GetPosition() / Tile::SIZE;

	Vector2 tilesToCorner = (Game::GetScreenSize() / scaledTileSize / 2);// +Vector2::ONE;
	Vector2 cameraTopLeft = cameraTilePosition - tilesToCorner;
	Vector2 cameraBottomRight = cameraTilePosition + tilesToCorner;

	// clamp to map bounds
	cameraTopLeft.X = Math::Clamp(cameraTopLeft.X, 0, m_dimensions.X) - 1;
	cameraTopLeft.Y = Math::Clamp(cameraTopLeft.Y, 0, m_dimensions.Y) - 1;
	cameraBottomRight.X = Math::Clamp(cameraBottomRight.X, 0, m_dimensions.X);
	cameraBottomRight.Y = Math::Clamp(cameraBottomRight.Y, 0, m_dimensions.Y);

	for (Layer* layer : m_layers)
	{
		if (type != layer->GetType())
		{
		    type = layer->GetType();
		    if (type == Layer::Type::FOREGROUND)
		    {
		        // draw character (for now)
				m_pMapComponent->Draw(spriteBatch);
		    }
		}

		for (Tile& tile : *layer)
		{
			int x = (tile.tileIndex % (int)m_dimensions.X);
			int y = (tile.tileIndex / (int)m_dimensions.X);

			// check if we should draw the tile
			if (x < cameraTopLeft.X - 1 || x >= cameraBottomRight.X) continue;
			if (y < cameraTopLeft.Y - 1 || y >= cameraBottomRight.Y) continue;
			
			Region source(0, 0, Tile::SIZE, Tile::SIZE);
			Vector2 position(x * Tile::SIZE, y * Tile::SIZE);
			Color c = Color::WHITE;
			bool xEnd = (x == m_dimensions.X - 1 || x == 0);
			bool yEnd =  (y == m_dimensions.Y - 1 || y == 0);

			if (xEnd) c = Color::RED;
			if (yEnd) c = Color::BLUE;
			if (xEnd && yEnd) c = Color::PURPLE;
		
			spriteBatch.Draw(m_pTexture, position, source, c);
		}
	}
	spriteBatch.End();
}