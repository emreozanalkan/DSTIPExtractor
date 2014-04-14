#include "depthframe.h"
#include <cmath>

DepthFrame::DepthFrame()
{
    _rows = 0;
    _cols = 0;
    _depthValues = 0;
    _skeletonIDValues = 0;
}

DepthFrame::DepthFrame(int rows, int cols)
{
    this->_rows = rows;
    this->_cols = cols;

    _depthValues = new float[rows * cols];
    _skeletonIDValues = new uint8_t[rows * cols];
}

DepthFrame::DepthFrame(int rows, int cols, unsigned char* rawData)
{
    this->_rows = rows;
    this->_cols = cols;

    _depthValues = new float[rows * cols];

    uint16_t* data = (uint16_t*)rawData;

    int index = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            index = (i * cols) + j;
            this->_depthValues[index] = data[index];
        }
    }
}

DepthFrame::~DepthFrame()
{
    delete [] _depthValues;
    _depthValues = 0;

    delete [] _skeletonIDValues;
    _skeletonIDValues = 0;
}

void DepthFrame::setSize(int rows, int cols)
{
    if(_depthValues)
    {
        delete [] _depthValues;
        _depthValues = 0;
    }

    if(_skeletonIDValues)
    {
        delete [] _skeletonIDValues;
        _skeletonIDValues = 0;
    }

    this->_rows = rows;
    this->_cols = cols;

    _depthValues = new float[rows * cols];
    _skeletonIDValues = new uint8_t[rows * cols];
}

inline int DepthFrame::getRowCount() const
{
    return _rows;
}

inline int DepthFrame::getColCount() const
{
    return _cols;
}

inline float* DepthFrame::getDepthValues() const
{
    return _depthValues;
}

inline uint8_t* DepthFrame::getSkeletonIDValues() const
{
    return _skeletonIDValues;
}

void DepthFrame::setSkeletonIDValues(uint8_t* skeletonValues)
{
    _skeletonIDValues = skeletonValues;
}

inline float DepthFrame::getValue(int row, int col) const
{
    return _depthValues[(row * _cols) + col];
}

void DepthFrame::setValue(int row, int col, float value)
{
    _depthValues[(row * _cols) + col] = value;
}

inline float DepthFrame::getSkeletonIDValue(int row, int col) const
{
    return _skeletonIDValues[(row * _cols) + col];
}

void DepthFrame::setSkeletonIDValue(int row, int col, uint8_t value)
{
    _skeletonIDValues[(row * _cols) + col] = value;
}

void DepthFrame::copyTo(DepthFrame* depthFrame)
{
    depthFrame->setSize(_cols, _rows);

    for(int i = 0; i < _rows; i++)
        for(int j = 0; j < _cols; j++)
            depthFrame->setValue(i, j, getValue(i, j));
}

void DepthFrame::copyTo(DepthFrame& depthFrame)
{
    depthFrame.setSize(_cols, _rows);

    for(int i = 0; i < _rows; i++)
        for(int j = 0; j < _cols; j++)
            depthFrame.setValue(i, j, getValue(i, j));
}

void DepthFrame::convertToChar(unsigned char* destination)
{
    int index = 0;

    for(int i = 0; i < _rows; i++)
    {
        for(int j = 0; j < _cols; j++)
        {
            index = (i * _cols) + j;
            destination[index] = (uint8_t) (_depthValues[index] / 16.0);
        }
    }
}

void DepthFrame::convertToInt(uint8_t* destination)
{
    uint16_t* destinationInt = (uint16_t*) destination;

    int index = 0;

    for(int i = 0; i < _rows; i++)
    {
        for(int j = 0; j < _cols; j++)
        {
            index = (i * _cols) + j;
            destinationInt[index] = ((uint16_t)(_depthValues[index]) & 0xfff8) >> 3;
        }
    }
}

void DepthFrame::scaleSize(float scale)
{
    int newCols = std::floor(_cols * scale);
    int newRows = std::floor(_rows * scale);

    float* newDepthValues = new float[newCols * newRows];

    for(int i = 0; i < newRows; i++)
    {
        for(int j = 0; j < newCols; j++)
        {
            int r = std::floor(i / scale);
            int c = std::floor(j / scale);
            newDepthValues[(i * newCols) + j] = _depthValues[(r * _cols) + c];
        }
    }

    delete [] _depthValues;

    _depthValues = newDepthValues;

    _cols = newCols;
    _rows = newRows;
}

void DepthFrame::scaleValues(float scale)
{
    int index = 0;

    for(int i = 0; i < _rows; i++)
    {
        for(int j = 0; j < _cols; j++)
        {
            index = (i * _cols) + j;
            _depthValues[index] = _depthValues[index] * scale;
        }
    }
}

int DepthFrame::numberOfNonZeroPoints() const
{
    int count = 0;

    int index = 0;

    for(int i = 0; i < _rows; i++)
    {
        for(int j = 0; j < _cols; j++)
        {
            index = (i * _cols) + j;

            if(_depthValues[index])
                ++count;
        }
    }

    return count;
}

float DepthFrame::avgNonZeroPoints() const
{
    int count = 0;
    int sum = 0;

    int index = 0;

    for(int i = 0; i < _rows; i++)
    {
        for(int j = 0; j < _cols; j++)
        {
            index = (i * _cols) + j;

            if(_depthValues[index])
            {
                ++count;
                sum += _depthValues[index];
            }
        }
    }

    if(count)
        return sum / (float)count;
    else
        return 0;
}

int DepthFrame::numberOfPointsWithSkeletonID(uint8_t id) const
{
    int count = 0;

    int index = 0;

    for(int i = 0; i < _rows; i++)
    {
        for(int j = 0; j < _cols; j++)
        {
            index = (i * _cols) + j;
            if(_skeletonIDValues[index] == id)
            {
                ++count;
            }
        }
    }

    return count;
}
