#include "histogramApplication.h"

void HistogramApplication::setup() 
{
    ofSetBackgroundColor(0);
    histogram.assign(256, 0);
}

void HistogramApplication::draw()
{
    if (histogram.empty()) return;

    float padding = 20;
    float barWidth = (ofGetWidth() - 2 * padding) / (float)histogram.size();
    int maxCount = *std::max_element(histogram.begin(), histogram.end());

    for (size_t i = 0; i < histogram.size(); i++) {
        float height = ofMap(histogram[i], 0, maxCount, 0, ofGetHeight() - 2 * padding);
        ofSetColor(255);
        ofDrawRectangle(padding + i * barWidth, ofGetHeight() - padding - height, barWidth, height);
    }
}

void HistogramApplication::setHistogram(const ofImage& img)
{
    histogram.assign(256, 0);
    for (int y = 0; y < img.getHeight(); y++)
    {
        for (int x = 0; x < img.getWidth(); x++)
        {
            int brightness = img.getColor(x, y).getBrightness(); //TODO: Fix
            histogram[brightness]++;
        }
    }
}

void HistogramApplication::exit()
{
    isClosed = true;    
}

void HistogramApplication::close()
{
}
