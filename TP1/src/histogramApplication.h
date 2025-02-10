#pragma once
#include "ofMain.h"

class HistogramApplication : public ofBaseApp {
public:
    std::vector<int> histogram;
    bool isClosed;

    void setup();
    void draw();
    void setHistogram(const ofImage& img);
    void exit();
    void close();
};
