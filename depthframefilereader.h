#ifndef DEPTHFRAMEFILEREADER_H
#define DEPTHFRAMEFILEREADER_H

#include <iostream>
#include <string>
#include <fstream>

#include "depthframelist.h"

class DepthFrameFileReader
{
public:
    DepthFrameFileReader();
    DepthFrameFileReader(std::string filePath);
    DepthFrameFileReader(std::string filePath, bool readFile = false);

    ~DepthFrameFileReader();

    std::string getFilePath() const;
    void setFilePath(std::string filePath);

    int getFrameCount() const;
    int getColsCount() const;
    int getRowsCount() const;

    DepthFrameList* getDepthFrameList() const;

    bool readHeader();
    bool readFile();

protected:
    bool openFile();
    bool isFileOpen();
    bool closeFile();

private:
    std::string _filePath;

    DepthFrameList* _depthFrameList;

    int _frameCount;
    int _cols;
    int _rows;

    std::ifstream* _fileStream;
};

#endif // DEPTHFRAMEFILEREADER_H
