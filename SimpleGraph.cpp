#include "SimpleGraph.h"

SimpleGraph::SimpleGraph(U8G2 &display) : u8g2(display), regionX(0), regionY(0), regionWidth(128), regionHeight(64), rows(1), cols(1), currentIndex(0) {}

void SimpleGraph::setSubplot(int rows, int cols, int index) {
    this->rows = rows;
    this->cols = cols;
    this->currentIndex = index;

    int subplotWidth = 128 / cols;
    int subplotHeight = 64 / rows;

    int colIndex = index % cols;
    int rowIndex = index / cols;

    regionX = colIndex * subplotWidth;
    regionY = rowIndex * subplotHeight;
    regionWidth = subplotWidth;
    regionHeight = subplotHeight;
}

void SimpleGraph::resetRegion() {
    regionX = 0;
    regionY = 0;
    regionWidth = 128;
    regionHeight = 64;
}

void SimpleGraph::drawAxes() {
    u8g2.drawLine(regionX + 10, regionY + 10, regionX + 10, regionY + regionHeight - 10);  // Eje Y
    u8g2.drawLine(regionX + 10, regionY + regionHeight - 10, regionX + regionWidth - 10, regionY + regionHeight - 10); // Eje X
}

void SimpleGraph::drawPoint(int x, int y) {
    u8g2.drawPixel(mapX(x), mapY(y));
}

void SimpleGraph::drawLine(int x1, int y1, int x2, int y2) {
    u8g2.drawLine(mapX(x1), mapY(y1), mapX(x2), mapY(y2));
}

void SimpleGraph::drawScatterPlot(int dataX[], int dataY[], int dataSize) {
    for (int i = 0; i < dataSize; i++) {
        drawPoint(dataX[i], dataY[i]);
    }
}

void SimpleGraph::drawLineGraph(int dataX[], int dataY[], int dataSize) {
    for (int i = 0; i < dataSize - 1; i++) {
        drawLine(dataX[i], dataY[i], dataX[i+1], dataY[i+1]);
    }
}

void SimpleGraph::drawMultipleLineGraphs(int* dataX[], int* dataY[], int dataSize[], int numLines) {
    for (int i = 0; i < numLines; i++) {
        drawLineGraph(dataX[i], dataY[i], dataSize[i]);
    }
}

void SimpleGraph::drawBarGraph(int data[], int dataSize, int barWidth) {
    for (int i = 0; i < dataSize; i++) {
        u8g2.drawBox(mapX(i * (barWidth + 2)), mapY(data[i]), barWidth, data[i]);
    }
}

void SimpleGraph::drawPieChart(int data[], int dataSize) {
    int total = 0;
    for (int i = 0; i < dataSize; i++) {
        total += data[i];
    }
    
    int startAngle = 0;
    for (int i = 0; i < dataSize; i++) {
        int endAngle = startAngle + (data[i] * 360 / total);
        u8g2.drawPieSlice(regionX + regionWidth / 2, regionY + regionHeight / 2, min(regionWidth, regionHeight) / 2 - 10, startAngle, endAngle);
        startAngle = endAngle;
    }
}

int SimpleGraph::mapX(int x) {
    return regionX + 10 + x * (regionWidth - 20) / 100;
}

int SimpleGraph::mapY(int y) {
    return regionY + regionHeight - 10 - y * (regionHeight - 20) / 100;
}
