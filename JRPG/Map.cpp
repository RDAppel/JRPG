
#include "_PCH.h"

#include "Map.h"
#include "Tile.h"

bool Map::Load(const std::string& path)
{
	std::ifstream fileIn(path.c_str(), std::ifstream::in);
	//if (!fileIn.is_open() || !fileIn.good()) return false;
	auto error = [&fileIn]() { fileIn.close(); return false; };

	// read in all lines
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(fileIn, line))
	{
		if (line.empty()) continue;

		Trim(line);
		if (line[0] == '#') continue;

		lines.push_back(line);
	}

	if (lines.size() < 2) return error();

	std::vector<std::string>::iterator it = lines.begin();
	std::vector<std::string> splitItems;

	// read in dimensions
	splitItems.clear();
	SplitLine(*it, splitItems, ',');
	if (splitItems.size() != 2) return error();
	m_dimensions.X = std::stoi(splitItems[0]);
	m_dimensions.Y = std::stoi(splitItems[1]);
	++it;

	// read in textures
	splitItems.clear();
	uint8_t textureCount = std::stoi(*it);
	for (uint8_t i = 0; i < textureCount; ++i)
	{
		++it;
		Texture* pTexture = m_pResourceManager->Load<Texture>(*it);
		if (!pTexture) return error();
		m_textures.push_back(pTexture);
	}

	// layers
	++it;
	uint8_t layersLeft = std::stoi(*it);
	Layer::Type layerType = Layer::Type::NONE;
	uint32_t tilesLeft = 0;

	// read in layers
	while (layersLeft)
	{
		++it;
		layerType = Layer::GetTypeByName(*it);
		if (layerType == Layer::Type::NONE) return error();

		Layer* pLayer = new Layer();
		pLayer->SetType(layerType);

		++it;
		tilesLeft = std::stoi(*it);
		while (tilesLeft)
		{
			++it;
			splitItems.clear();
			SplitLine(*it, splitItems, ',');
			if (splitItems.size() < 4) return error();
			Tile t;
			t.X = std::stoi(splitItems[0]);
			t.Y = std::stoi(splitItems[1]);
			t.TilesetIndex = std::stoi(splitItems[2]);
			t.TileIndex = std::stoi(splitItems[3]);
			pLayer->AddTile(t);
			--tilesLeft;
		}
		m_layers.push_back(pLayer);

		--layersLeft;
	}




	/**

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

	/**/

	m_camera.SetScale(Vector2::ONE * 2.0f);
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
	Texture* pTexture = nullptr;

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
			pTexture = m_textures[tile.TilesetIndex];

			int x = tile.X;
			int y = tile.Y;

			// check if we should draw the tile
			if (x < cameraTopLeft.X - 1 || x >= cameraBottomRight.X) continue;
			if (y < cameraTopLeft.Y - 1 || y >= cameraBottomRight.Y) continue;

			int tileX = tile.TileIndex % 8 * Tile::SIZE;
			int tileY = tile.TileIndex / 8 * Tile::SIZE;

			Region source(tileX + 1, tileY + 1, Tile::SIZE - 2, Tile::SIZE - 2);
			Vector2 position(x * Tile::SIZE, y * Tile::SIZE);
			Color c = Color::WHITE;
			bool xEnd = (x == m_dimensions.X - 1 || x == 0);
			bool yEnd = (y == m_dimensions.Y - 1 || y == 0);

			//if (xEnd) c = Color::RED;
			//if (yEnd) c = Color::BLUE;
			//if (xEnd && yEnd) c = Color::PURPLE;

			spriteBatch.Draw(pTexture, position, source, c);
		}
	}
	spriteBatch.End();
}

void Map::PrintToConsole() const
{
	std::cout << "# Dimensions\n";
	std::cout << m_dimensions.X << ", " << m_dimensions.Y << "\n";

	std::cout << "\n# Textures\n";
	std::cout << m_textures.size() << "\n";
	for (Texture* pTexture : m_textures)
	{
		std::cout << pTexture->GetPath() << "\n";

	}

	std::cout << "\n# Layers\n";
	std::cout << m_layers.size() << "\n";
	int layerIndex = 0;
	for (Layer* layer : m_layers)
	{
		std::cout << "\n# ----- Layer " << layerIndex << " -----\n";
		std::cout << Layer::GetTypeName(layer->GetType()) << "\n";
		std::cout << layer->GetSize() << "\n";
		for (Tile& tile : *layer)
		{
			std::cout << tile.X << ", " << tile.Y << ", ";
			std::cout << (int)tile.TilesetIndex << ", " << tile.TileIndex << "\n";
		}

		layerIndex++;
	}
}

bool Map::AddTileAtPosition(const int layerIndex, Tile tile, bool stack)
{
	if (!stack)
	{
		// check if there is already a tile at this position
		for (Tile& t : *m_layers[layerIndex])
		{
			if (t.X == tile.X && t.Y == tile.Y) return false;
		}
	}

	m_layers[layerIndex]->AddTile(tile);
	return true;
}