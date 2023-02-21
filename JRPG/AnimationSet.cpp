
#include "_PCH.h"

#include "AnimationSet.h"


AnimationSet::~AnimationSet()
{
    for (Animation* pAnimation : m_animations)
    {
		m_pResourceManager->RemoveResource(pAnimation->GetId());
    }
}

bool AnimationSet::Load(const std::string& path)
{
    std::ifstream fileIn(path.c_str(), std::ifstream::in);
    if (!fileIn.is_open() || !fileIn.good()) return false;

    std::string line;
    while (getline(fileIn, line))
    {
		if (line.empty()) continue;

        Trim(line);
        if (line[0] == '#') continue;

        Animation* pAnimation = m_pResourceManager->Load<Animation>(line);
        if (!pAnimation) return false;
        m_animations.push_back(pAnimation);
	}

    return true;
}

Resource* AnimationSet::Clone()
{
    AnimationSet* pClone = new AnimationSet;
    for (Animation* pAnimation : m_animations)
    {
        pClone->m_animations.push_back(static_cast<Animation*>(pAnimation->Clone()));
    }

    return pClone;
}

void AnimationSet::SetTexture(Texture* pTexture)
{
    for (Animation* pAnimation : m_animations)
    {
		pAnimation->SetTexture(pTexture);
	}
}