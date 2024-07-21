#include "SimpleGraph.h"

SimpleGraph::SimpleGraph(U8G2 &display) : u8g2(display) {}

void SimpleGraph::drawAxes() {
    u8g2.drawLine(10, 10, 10, 54);  // Eje Y
    u8g2.drawLine(10, 54, 118, 54); // Eje X
}

void SimpleGraph::drawPoint(int x, int y) {
    u8g2.drawPixel(10 + x, 54 - y);
}

void SimpleGraph::drawLine(int x1, int y1, int x2, int y2) {
    u8g2.drawLine(10 + x1, 54 - y1, 10 + x2, 54 - y2);
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
        u8g2.drawBox(10 + i * (barWidth + 2), 54 - data[i], barWidth, data[i]);
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
        u8g2.drawPieSlice(64, 32, 30, startAngle, endAngle);
        startAngle = endAngle;
    }
}
