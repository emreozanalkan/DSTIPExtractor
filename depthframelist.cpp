#include "depthframelist.h"

DepthFrameList::DepthFrameList()
{

}

DepthFrameList::~DepthFrameList()
{

}

void DepthFrameList::addFrame(DepthFrame* depthFrame)
{
    _depthFrameList.push_back(depthFrame);
}

DepthFrame* DepthFrameList::getFrame(int index) const
{
    return _depthFrameList[index];
}

void DepthFrameList::removeFrame(int index)
{
    _depthFrameList.erase(_depthFrameList.begin() + index);
}

int DepthFrameList::getFrameCount() const
{
    return _depthFrameList.size();
}

std::vector<DepthFrame*>::const_iterator DepthFrameList::begin() const
{
    return _depthFrameList.begin();
}

std::vector<DepthFrame*>::const_iterator DepthFrameList::end() const
{
    return _depthFrameList.end();
}
