#ifndef DEPTHFRAMELIST_H
#define DEPTHFRAMELIST_H

#include <vector>

#include "depthframe.h"

class DepthFrameList
{
public:
    DepthFrameList();
    ~DepthFrameList();

    void addFrame(DepthFrame* depthFrame);
    DepthFrame* getFrame(int index) const;
    void removeFrame(int index);

    int getFrameCount() const;

    std::vector<DepthFrame*>::const_iterator begin() const;
    std::vector<DepthFrame*>::const_iterator end() const;

private:
    std::vector<DepthFrame*> _depthFrameList;
};

#endif // DEPTHFRAMELIST_H
