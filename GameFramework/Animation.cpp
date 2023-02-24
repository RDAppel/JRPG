
#include "_PCH.h"


bool Animation::Load(const std::string& path)
{
    std::ifstream fileIn(path.c_str(), std::ifstream::in);
    if (!fileIn.is_open() || !fileIn.good()) return false;
    auto error = [&fileIn] { fileIn.close(); return false; };

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
            for (size_t i = 0; i < splitItems.size(); ++i)
            {
				m_frameTimes.push_back(stod(splitItems[i]));
			}
        }
        else if (currentStep == TileSize)
        {
            if (splitItems.size() != 2) return error();
            width = stoi(splitItems[0]);
            height = stoi(splitItems[1]);
            if (width <= 0 || height <= 0) return error();
        }
        else if (currentStep == TilesWide)
        {
            tilesWide = stoi(splitItems[0]);
            if (tilesWide <= 0) return error();
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

            if (m_frames.size() == 0) return error();

            // expand the frame times if necessary to match the number of frames
            if (m_frameTimes.size() < m_frames.size())
            {
                double lastFrameTime = m_frameTimes[m_frameTimes.size() - 1];
                for (size_t i = m_frameTimes.size(); i < m_frames.size(); ++i)
                {
					m_frameTimes.push_back(lastFrameTime);
				}
            }
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
    m_currentFrameTime = 0;
}

void Animation::Update(const GameTime& gameTime)
{
    if (!m_isPlaying) return;

    m_currentFrameTime += gameTime.GetTimeElapsed();
    if (m_currentFrameTime >= m_frameTimes[m_currentIndex])
    {
        m_currentFrameTime -= m_frameTimes[m_currentIndex];
        m_currentIndex = (m_currentIndex + 1) % m_frames.size();
    }
}

Animation* Animation::Clone()
{
	Animation* pClone = new Animation();
	pClone->m_frames = m_frames;
    pClone->m_path = m_path;
	pClone->m_frameTimes = m_frameTimes;
	pClone->m_loopCount = m_loopCount;
	return pClone;
}