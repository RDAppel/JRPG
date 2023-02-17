
#include "_PCH.h"

Animation::Animation(const Animation& other)
{
    m_frames = other.m_frames;
    m_loopCount = other.m_loopCount;
    m_secondsPerFrame = other.m_secondsPerFrame;
}

bool Animation::Load(const std::string& path)
{
    std::ifstream fileIn(path.c_str(), std::ifstream::in);

    if (!fileIn.is_open() || !fileIn.good()) return false;

    enum Step { FrameTime, TileSize, TilesWide, FrameIndices, LoopCount, Done };

    Step currentStep = FrameTime;

    std::string line;
    std::vector<std::string> splitItems;

    int width = 0;
    int height = 0;
    int tilesWide = 0;

    while (currentStep != Done && getline(fileIn, line))
    {
        if (line.empty()) continue;

        splitItems.clear();
        SplitLine(line, splitItems);

        if (currentStep == FrameTime)
        {
            m_secondsPerFrame = stod(splitItems[0]);
        }
        else if (currentStep == TileSize)
        {
            if (splitItems.size() != 2) return false;
            width = stoi(splitItems[0]);
            height = stoi(splitItems[1]);
            if (width <= 0 || height <= 0) return false;
        }
        else if (currentStep == TilesWide)
        {
            tilesWide = stoi(splitItems[0]);
            if (tilesWide <= 0) return false;
        }
        else if (currentStep == FrameIndices)
        {
            for (size_t i = 0; i < splitItems.size(); ++i)
            {
                int index = stoi(splitItems[i]);
                int x = (index % tilesWide) * width;
                int y = (index / tilesWide) * height;
                m_frames.push_back(Region(x, y, width, height));
            }

            if (m_frames.size() == 0) return false;
        }
        else if (currentStep == LoopCount)
        {
            if (splitItems.size() > 0)
            {
                m_loopCount = stoi(splitItems[0]);
            }
        }

        currentStep = (Step)((int)currentStep + 1);
    }

    return true;
}

void Animation::Stop()
{
    Pause();
    m_currentIndex = 0;
}

void Animation::Update(const GameTime& gameTime)
{
    if (!m_isPlaying) return;

    m_currentFrameTime += gameTime.GetTimeElapsed();
    if (m_currentFrameTime >= m_secondsPerFrame)
    {
        m_currentIndex++;
        m_currentFrameTime -= m_secondsPerFrame;

        if (m_currentIndex >= m_frames.size())
        {
            m_currentIndex = 0;
        }
    }
}