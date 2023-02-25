
#include "_PCH.h"
#include "Map.h"
#include "Tile.h"

bool Map::Load(const std::string& path)
{
	std::ifstream fileIn(path.c_str(), std::ifstream::in);
	if (!fileIn.is_open() || !fileIn.good()) return false;

	std::string line;
	std::vector<std::string> lines;
	while (std::getline(fileIn, line))
	{
		Trim(line);
		if (line.empty() || line[0] == '#') continue;
		lines.push_back(line);
	}
	fileIn.close();
	std::vector<std::string>::iterator it = lines.begin();

	// load dimensions
	std::vector<std::string> splitItems;
	SplitLine(*it, splitItems, ',');
	if (splitItems.size() < 2) return false;
	m_dimensions.X = std::stoi(splitItems[0]);
	m_dimensions.Y = std::stoi(splitItems[1]);
	++it;

	// load textures
	uint8_t texturesLeft = std::stoi(*it);
	++it;
	while (texturesLeft)
	{
		Texture* pTexture = m_pResourceManager->Load<Texture>(*it);
		if (!pTexture) return false;
		m_textures.push_back(pTexture);

		--texturesLeft;
		++it;
	}

	// load layers
	uint8_t layersLeft = std::stoi(*it);
	Layer::Type layerType = Layer::Type::NONE;
	uint32_t tilesLeft = 0;
	++it;

	while (layersLeft)
	{
		layerType = Layer::GetTypeByName(*it);
		if (layerType == Layer::Type::NONE) return false;

		Layer* pLayer = new Layer;
		pLayer->SetType(layerType);
		m_layers.push_back(pLayer);
		++it;

		// temp tiles for testing
		if (layerType == Layer::Type::BACKGROUND)
		{
			for (uint32_t y = 0; y < m_dimensions.Y; ++y)
			{
				for (uint32_t x = 0; x < m_dimensions.X; ++x)
				{
					Tile tile;
					tile.X = x;
					tile.Y = y;
					tile.TilesetIndex = 0;
					tile.TileIndex = 0;
					pLayer->AddTile(tile);
				}
			}
		}

		tilesLeft = std::stoi(*it);
		++it;
		while (tilesLeft)
		{
			splitItems.clear();
			SplitLine(*it, splitItems, ',');
			if (splitItems.size() < 4) return false;

			Tile tile;
			tile.X = std::stoi(splitItems[0]);
			tile.Y = std::stoi(splitItems[1]);
			tile.TilesetIndex = std::stoi(splitItems[2]);
			tile.TileIndex = std::stoi(splitItems[3]);
			pLayer->AddTile(tile);

			--tilesLeft;
			++it;
		}

		--layersLeft;
	}


	// setup camera
	m_camera.SetScale(2.0f);
	m_camera.SetBounds(Region(0, 0, m_dimensions.X * Tile::SIZE, m_dimensions.Y * Tile::SIZE));

	return true;
}

void Map::SetMapComponent(MapComponent* pMapComponent)
{
	m_pMapComponent = pMapComponent;
	m_camera.SetTarget(pMapComponent);
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
	spriteBatch.Begin(SpriteSortMode::DEFERRED, BlendState::ALPHA, &m_camera.GetTransform());
	Texture* pTexture = nullptr;

	Vector2 scaledTileSize = Tile::SIZE * m_camera.GetScale();
	Vector2 cameraTilePosition = m_camera.GetPosition() / Tile::SIZE;

	Vector2 tilesToCorner = Game::GetScreenSize() / scaledTileSize / 2;
	Vector2 cameraTopLeft = cameraTilePosition - tilesToCorner;
	Vector2 cameraBottomRight = cameraTilePosition + tilesToCorner;

	// clamp to map bounds
	cameraTopLeft.X = Math::Clamp(cameraTopLeft.X, 0.0f, m_dimensions.X);
	cameraTopLeft.Y = Math::Clamp(cameraTopLeft.Y, 0.0f, m_dimensions.Y);
	cameraBottomRight.X = Math::Clamp(cameraBottomRight.X, 0.0f, m_dimensions.X);
	cameraBottomRight.Y = Math::Clamp(cameraBottomRight.Y, 0.0f, m_dimensions.Y);


	Layer::Type layerType = Layer::Type::NONE;
	for (Layer* pLayer : m_layers)
	{
		layerType = pLayer->GetType();
		if (layerType == Layer::Type::NONE) continue;

		if (layerType == Layer::Type::FOREGROUND)
		{
			m_pMapComponent->Draw(spriteBatch);
		}

		for (Tile& tile : *pLayer)
		{
			if (tile.X < cameraTopLeft.X - 1 || tile.X > cameraBottomRight.X) continue;
			if (tile.Y < cameraTopLeft.Y - 1 || tile.Y > cameraBottomRight.Y) continue;

			pTexture = m_textures[tile.TilesetIndex];
			int tilesWide = pTexture->GetWidth() / Tile::SIZE;

			Vector2 position(tile.X * Tile::SIZE, tile.Y * Tile::SIZE);
			int tileX = tile.TileIndex % tilesWide * Tile::SIZE;
			int tileY = tile.TileIndex / tilesWide * Tile::SIZE;
			Region source(tileX, tileY, Tile::SIZE, Tile::SIZE);

			bool xEnd = tile.X == m_dimensions.X - 1 || tile.X == 0;
			bool yEnd = tile.Y == m_dimensions.Y - 1 || tile.Y == 0;

			Color color = Color::WHITE;
			if (xEnd) color = Color::RED;
			if (yEnd) color = Color::BLUE;
			if (xEnd && yEnd) color = Color::PURPLE;

			spriteBatch.Draw(pTexture, position, source, color);

		}
	}

	spriteBatch.End();
}