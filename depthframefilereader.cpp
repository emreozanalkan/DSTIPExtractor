#include "depthframefilereader.h"

DepthFrameFileReader::DepthFrameFileReader()
{
    _filePath = "";

    _depthFrameList = new DepthFrameList();

    _frameCount = 0;
    _cols = 0;
    _rows = 0;

    _fileStream = 0;
}

DepthFrameFileReader::DepthFrameFileReader(std::string filePath)
{
    _filePath = filePath;

    _depthFrameList = new DepthFrameList();

    _frameCount = 0;
    _cols = 0;
    _rows = 0;

    _fileStream = 0;
}

DepthFrameFileReader::DepthFrameFileReader(std::string filePath, bool readFile)
{
    _filePath = filePath;

    _depthFrameList = new DepthFrameList();

    _frameCount = 0;
    _cols = 0;
    _rows = 0;

    _fileStream = 0;

    if(readFile)
        this->readFile();
}

DepthFrameFileReader::~DepthFrameFileReader()
{
    if(this->isFileOpen())
            this->closeFile();

    delete _fileStream;
    _fileStream = 0;

    _depthFrameList = 0;
}

std::string DepthFrameFileReader::getFilePath() const
{
    return _filePath;
}

void DepthFrameFileReader::setFilePath(std::string filePath)
{
    this->_filePath = filePath;
}

int DepthFrameFileReader::getFrameCount() const
{
    return _frameCount;
}

int DepthFrameFileReader::getColsCount() const
{
    return _cols;
}

int DepthFrameFileReader::getRowsCount() const
{
    return _rows;
}

DepthFrameList* DepthFrameFileReader::getDepthFrameList() const
{
    return _depthFrameList;
}

bool DepthFrameFileReader::openFile()
{
    if(this->isFileOpen())
        return true;

    if(_filePath.empty())
        return false;

    if(!_fileStream)
        _fileStream = new std::ifstream();

    _fileStream->open(_filePath, std::ios::in | std::ios::binary);

    if(_fileStream->is_open())
        return true;

    return false;
}

bool DepthFrameFileReader::isFileOpen()
{
    if(!_fileStream)
        return false;

    return _fileStream->is_open();
}

bool DepthFrameFileReader::closeFile()
{
    if(!_fileStream)
        return true;

    if(this->isFileOpen())
        _fileStream->close();

    return !_fileStream->is_open();
}

bool DepthFrameFileReader::readHeader()
{
    if(!this->isFileOpen())
        if(!this->openFile())
            return false;

    _fileStream->seekg(0, std::ios::beg);

    _fileStream->read((char*)&_frameCount, sizeof(_frameCount));
    _fileStream->read((char*)&_cols, sizeof(_cols));
    _fileStream->read((char*)&_rows, sizeof(_rows));

    return true;
}

bool DepthFrameFileReader::readFile()
{
    if(!this->readHeader())
        return false;

    for(int i = 0; i < _frameCount; i++)
    {
        DepthFrame* depthFrame = new DepthFrame(_rows, _cols);

        int* tempRow = new int[_cols];
        uint8_t* tempRowID = new uint8_t[_cols];

        for(int i = 0; i < _rows; i++)
        {
            _fileStream->read((char*)tempRow, _cols);
            _fileStream->read((char*)tempRowID, _cols);

            for(int j = 0; j < _cols; j++)
            {
                int temp = tempRow[j];
                depthFrame->setValue(i, j, (float)temp);
                depthFrame->setSkeletonIDValue(i, j, tempRowID[j]);
            }
        }
        _depthFrameList->addFrame(depthFrame);

        delete [] tempRow;
        tempRow = 0;
        delete [] tempRowID;
        tempRowID = 0;
    }

    return true;
}
