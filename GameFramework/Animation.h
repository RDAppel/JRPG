#pragma once

#include "_PCH.h"

class Animation : public Resource
{

private:

	int m_currentIndex = 0;

	double m_secondsPerFrame = 0.16;
	double m_currentFrameTime = 0;

	int m_loopCount = 0;

	bool m_isPlaying = false;

	Texture* m_pTexture = nullptr;

	std::vector<Region> m_frames;

public:

	Animation() {}
	Animation(const Animation& other);
	virtual ~Animation() {}

	virtual bool IsCloneable() { return true; }

	virtual bool Load(const std::string& path);

	virtual bool IsPlaying() const { return m_isPlaying; }

	virtual void Play() { m_isPlaying = true; }
	virtual void Pause() { m_isPlaying = false; }
	virtual void Stop();

	virtual void Update(const GameTime& gameTime);

	virtual void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

	virtual Texture* GetTexture() const { return m_pTexture; }

	virtual const Region& GetCurrentFrame() const { return m_frames[m_currentIndex]; }

};

