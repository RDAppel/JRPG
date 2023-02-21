#pragma once

class AnimationSet : public Resource
{

private:

	std::vector<Animation*> m_animations;

public:

	AnimationSet() {}
	AnimationSet(const AnimationSet&) = delete;
	virtual ~AnimationSet();

	AnimationSet& operator=(const AnimationSet&) = delete;

	virtual bool Load(const std::string& path);

	virtual bool IsCloneable() const { return true; }

	virtual Resource* Clone();

	Animation* operator[](const int index) const { return m_animations[index]; }

	virtual void SetTexture(Texture *pTexture);

};

