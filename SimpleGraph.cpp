#include "SimpleGraph.h"

SimpleGraph::SimpleGraph(U8G2 &display) : u8g2(display), regionX(0), regionY(0), regionWidth(128), regionHeight(64), rows(1), cols(1), currentIndex(0), minX(0), maxX(100), minY(0), maxY(100) {}

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

void SimpleGraph::autoResizeAxes(int dataX[], int dataY[], int dataSize) {
    if (dataX != nullptr && dataY != nullptr) {
        minX = dataX[0];
        maxX = dataX[0];
        minY = dataY[0];
        maxY = dataY[0];

        for (int i = 1; i < dataSize; i++) {
            if (dataX[i] < minX) minX = dataX[i];
            if (dataX[i] > maxX) maxX = dataX[i];
            if (dataY[i] < minY) minY = dataY[i];
            if (dataY[i] > maxY) maxY = dataY[i];
        }
    } else {
        minY = dataY[0];
        maxY = dataY[0];

        for (int i = 1; i < dataSize; i++) {
            if (dataY[i] < minY) minY = dataY[i];
            if (dataY[i] > maxY) maxY = dataY[i];
        }
    }

    // Asegurar que el rango no sea cero
    if (maxX == minX) {
        maxX += 1;
        minX -= 1;
    }
    if (maxY == minY) {
        maxY += 1;
        minY -= 1;
    }
}

void SimpleGraph::drawAxes() {
    // Dibuja el eje Y
    u8g2.drawLine(regionX + 10, regionY + 5, regionX + 10, regionY + regionHeight - 5);
    // Añadir escalas en el eje Y
    for (int i = 0; i <= 5; i++) {
        int y = regionY + regionHeight - 5 - i * (regionHeight - 10) / 5;
        u8g2.drawLine(regionX + 8, y, regionX + 12, y);
        u8g2.setCursor(regionX - 2, y + 4);
        u8g2.print(minY + i * (maxY - minY) / 5);
    }

    // Dibuja el eje X
    u8g2.drawLine(regionX + 10, regionY + regionHeight - 10, regionX + regionWidth - 5, regionY + regionHeight - 10);
    // Añadir escalas en el eje X
    for (int i = 0; i <= 5; i++) {
        int x = regionX + 10 + i * (regionWidth - 15) / 5;
        u8g2.drawLine(x, regionY + regionHeight - 12, x, regionY + regionHeight - 8);
        u8g2.setCursor(x - 5, regionY + regionHeight);
        u8g2.print(minX + i * (maxX - minX) / 5);
    }
}

void SimpleGraph::drawPoint(int x, int y) {
    u8g2.drawPixel(mapX(x), mapY(y));
}

void SimpleGraph::drawLine(int x1, int y1, int x2, int y2) {
    u8g2.drawLine(mapX(x1), mapY(y1), mapX(x2), mapY(y2));
}

void SimpleGraph::drawScatterPlot(int dataX[], int dataY[], int dataSize) {
    autoResizeAxes(dataX, dataY, dataSize);
    drawAxes();
    for (int i = 0; i < dataSize; i++) {
        drawPoint(dataX[i], dataY[i]);
    }
}

void SimpleGraph::drawLineGraph(int dataX[], int dataY[], int dataSize) {
    autoResizeAxes(dataX, dataY, dataSize);
    drawAxes();
    for (int i = 0; i < dataSize - 1; i++) {
        drawLine(dataX[i], dataY[i], dataX[i+1], dataY[i+1]);
    }
}

void SimpleGraph::drawMultipleLineGraphs(int* dataX[], int* dataY[], int dataSize[], int numLines) {
    int allDataX[100], allDataY[100];
    int index = 0;

    for (int i = 0; i < numLines; i++) {
        for (int j = 0; j < dataSize[i]; j++) {
            allDataX[index] = dataX[i][j];
            allDataY[index] = dataY[i][j];
            index++;
        }
    }

    autoResizeAxes(allDataX, allDataY, index);
    drawAxes();

    for (int i = 0; i < numLines; i++) {
        for (int j = 0; j < dataSize[i] - 1; j++) {
            drawLine(dataX[i][j], dataY[i][j], dataX[i][j + 1], dataY[i][j + 1]);
        }
    }
}

void SimpleGraph::drawBarGraph(int data[], int dataSize, int barWidth) {
    autoResizeAxes(nullptr, data, dataSize);
    drawAxes();
    int spacing = (regionWidth - 20) / dataSize;  // Espacio disponible para cada barra incluyendo el espacio entre barras
    for (int i = 0; i < dataSize; i++) {
        int x = regionX + 10 + i * spacing + spacing / 2;  // Ajusta la posición para centrar las barras en su espacio
        int y = mapY(data[i]);
        u8g2.drawBox(x - barWidth / 2, y, barWidth, regionY + regionHeight - 10 - y);
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
        int x = regionX + regionWidth / 2;
        int y = regionY + regionHeight / 2;
        int r = min(regionWidth, regionHeight) / 2 - 10;

        for (int angle = startAngle; angle < endAngle; angle += 10) {
            int x0 = x + r * cos(angle * M_PI / 180);
            int y0 = y + r * sin(angle * M_PI / 180);
            int x1 = x + r * cos((angle + 10) * M_PI / 180);
            int y1 = y + r * sin((angle + 10) * M_PI / 180);

            u8g2.drawTriangle(x, y, x0, y0, x1, y1);
        }

        startAngle = endAngle;
    }
}

int SimpleGraph::mapX(int x) {
    return regionX + 10 + (x - minX) * (regionWidth - 20) / (maxX - minX);
}

int SimpleGraph::mapY(int y) {
    return regionY + regionHeight - 10 - (y - minY) * (regionHeight - 15) / (maxY - minY);
}
