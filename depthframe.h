#ifndef DEPTHFRAME_H
#define DEPTHFRAME_H

#include <cstdint>

class DepthFrame
{
public:
    DepthFrame();
    DepthFrame(int rows, int cols);
    DepthFrame(int rows, int cols, unsigned char* data);
    ~DepthFrame();

    void setSize(int rows, int cols);

    int getRowCount() const;
    int getColCount() const;

    float* getDepthValues() const;

    uint8_t* getSkeletonIDValues() const;
    void setSkeletonIDValues(uint8_t* skeletonValues);

    float getValue(int row, int col) const;
    void setValue(int row, int col, float value);

    float getSkeletonIDValue(int row, int col) const;
    void setSkeletonIDValue(int row, int col, uint8_t value);

    void copyTo(DepthFrame* depthFrame);
    void copyTo(DepthFrame& depthFrame);

    void convertToChar(unsigned char* destination);
    void convertToInt(uint8_t* destination);

    void scaleSize(float scale); // scales cols and rows
    void scaleValues(float scale); // scale depth values

    int numberOfNonZeroPoints() const;
    float avgNonZeroPoints() const;

    int numberOfPointsWithSkeletonID(uint8_t id) const;

private:
    int _cols;
    int _rows;

    float* _depthValues;
    uint8_t* _skeletonIDValues;
};

#endif // DEPTHFRAME_H
