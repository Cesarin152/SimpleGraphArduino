#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H

#include <U8g2lib.h>

class SimpleGraph {
public:
    SimpleGraph(U8G2 &display);
    void setSubplot(int rows, int cols, int index);
    void resetRegion();
    void drawAxes();
    void drawPoint(int x, int y);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawScatterPlot(int dataX[], int dataY[], int dataSize);
    void drawLineGraph(int dataX[], int dataY[], int dataSize);
    void drawMultipleLineGraphs(int* dataX[], int* dataY[], int dataSize[], int numLines);
    void drawBarGraph(int data[], int dataSize, int barWidth);
    void drawPieChart(int data[], int dataSize);

private:
    U8G2 &u8g2;
    int regionX, regionY, regionWidth, regionHeight;
    int rows, cols, currentIndex;
    int mapX(int x);
    int mapY(int y);
};

#endif
