#pragma once

#include "Window.h"

#include "..\RPGLibrary\_PCH.h"

class TexturesWindow : public Window
{

private:

	int m_selectedIndex = 0;

	Texture* m_pTestTexture = nullptr;

public:

	virtual void LoadContent(ResourceManager& resourceManager)
	{
		m_pTestTexture = resourceManager.Load<Texture>("Textures\\Tilesets\\Exterior_01.png");
	}

	virtual void Update(const GameTime& gameTime)
	{
		if (!m_isOpen) return;

		Vector2 size = m_pTestTexture->GetSize();
		ImVec2 textureSize(size.X, size.Y);

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_HorizontalScrollbar;
		ImGui::SetNextWindowContentSize(textureSize);
		ImGui::Begin("Textures##Window", &m_isOpen, flags);

		const char* items[] = { "Texture 1", "Texture 2" };

		ImGui::Text("Texture:", m_selectedIndex);
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::Combo("##Textures#Combo", &m_selectedIndex, items, 2);

		if (ImGui::Button("Add Texture##Button")) { }

		ImGui::Image(m_pTestTexture->GetAllegroBitmap(), ImVec2(size.X, size.Y));


		ImGui::End();
	}


};