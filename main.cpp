#include <iostream>
#include <ctime>

using namespace std;

#include "depthframefilereader.h"

int main(void)
{
    DepthFrameFileReader depthFileReader;

    string fileName = "/Users/emreozanalkan/Desktop/MSRDailyAct3D_pack1/a01_s01_e01_depth.bin";

    depthFileReader.setFilePath(fileName);

    clock_t timeStart, timeEnd;

    timeStart = clock();
    bool isReadFile = depthFileReader.readFile();
    timeEnd = clock();

    cout << "Reading depth file took "<< difftime(timeEnd, timeStart) / CLOCKS_PER_SEC <<" second(s)."<< endl;

    if(!isReadFile)
    {
        cerr << "Error on read file :(" << endl;
        return 0;
    }

    cout << "Duration: " << depthFileReader.getFrameCount() << endl;
    cout << "Cols: " << depthFileReader.getColsCount() << endl;
    cout << "Rows: " << depthFileReader.getRowsCount() << endl;

    return 0;
}
