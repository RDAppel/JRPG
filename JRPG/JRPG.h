
#pragma once

#include "MapScreen.h"
#include "Character.h"
#include "MapComponent.h"


class JRPG : public Game
{

private:


public:

	JRPG()
	{
		SetRequireVSync(true);
		SetTargetFramesPerSecond(60);
		SetClearColor(Color::BLACK);
		SetUseImGui();
	}

	virtual ~JRPG() {}

	virtual void LoadContent(ResourceManager& resourceManager)
	{
		// todo: move this to a loading screen

		// todo: finish character.load
		Character* pCharacter = new Character;
		MapComponent* pMC = new MapComponent;

		std::string path;
		Texture* pTexture;
		Animation* pAnimation;

		path = "Textures\\Spritesheets\\Characters\\Character_0002.png";
		pTexture = resourceManager.Load<Texture>(path);

		path = "Animations\\Characters\\Idle\\Up.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_idleAnimations[Direction::UP] = pAnimation;

		path = "Animations\\Characters\\Idle\\Down.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_idleAnimations[Direction::DOWN] = pAnimation;

		path = "Animations\\Characters\\Idle\\Left.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_idleAnimations[Direction::LEFT] = pAnimation;

		path = "Animations\\Characters\\Idle\\Right.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_idleAnimations[Direction::RIGHT] = pAnimation;

		path = "Animations\\Characters\\Walk\\Up.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_walkAnimations[Direction::UP] = pAnimation;

		path = "Animations\\Characters\\Walk\\Down.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_walkAnimations[Direction::DOWN] = pAnimation;

		path = "Animations\\Characters\\Walk\\Left.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_walkAnimations[Direction::LEFT] = pAnimation;

		path = "Animations\\Characters\\Walk\\Right.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_walkAnimations[Direction::RIGHT] = pAnimation;

		path = "Animations\\Characters\\Run\\Up.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_runAnimations[Direction::UP] = pAnimation;

		path = "Animations\\Characters\\Run\\Down.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_runAnimations[Direction::DOWN] = pAnimation;

		path = "Animations\\Characters\\Run\\Left.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_runAnimations[Direction::LEFT] = pAnimation;

		path = "Animations\\Characters\\Run\\Right.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		pMC->m_runAnimations[Direction::RIGHT] = pAnimation;



		MapScreen *pMapScreen = new MapScreen;
		GetScreenManager().AddScreen(pMapScreen);
		pMapScreen->SetMapComponent(pMC);
	}

	virtual void Update(const GameTime& gameTime) override
	{
		Game::Update(gameTime);


	/*	ImGui::Begin("Hi");
		ImGui::End();*/
	}


	virtual void Draw(SpriteBatch& spriteBatch)
	{
		Game::Draw(spriteBatch);

		ImGui::Render();
		ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
	}

};

