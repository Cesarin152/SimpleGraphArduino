# SimpleGraph Library

La biblioteca `SimpleGraph` permite dibujar gráficos básicos en una pantalla OLED SSD1309 usando Arduino. Esta biblioteca incluye funcionalidades para gráficos de dispersión, gráficos de líneas, gráficos de barras y gráficos circulares.

## Instalación

1. Descarga el archivo `SimpleGraph.zip`.
2. Abre Arduino IDE.
3. Ve a `Sketch` -> `Include Library` -> `Add .ZIP Library...`.
4. Selecciona el archivo `SimpleGraph.zip`.

## Ejemplos de Uso

### Ejemplo 1: Dibujar ejes y un gráfico de dispersión

```cpp
#include <U8g2lib.h>
#include "SimpleGraph.h"

// Configura la pantalla para I2C
U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
SimpleGraph graph(u8g2);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  
  graph.drawAxes();
  
  int dataX[] = {0, 10, 20, 30, 40, 50, 60};
  int dataY[] = {0, 10, 5, 20, 10, 30, 15};
  int dataSize = sizeof(dataX) / sizeof(dataX[0]);
  
  graph.drawScatterPlot(dataX, dataY, dataSize);
  
  u8g2.sendBuffer();
  
  delay(1000);  // Espera un segundo antes de actualizar la pantalla
}
```

### Ejemplo 2: Dibujar un gráfico de líneas

```cpp
#include <U8g2lib.h>
#include "SimpleGraph.h"

// Configura la pantalla para I2C
U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
SimpleGraph graph(u8g2);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  
  graph.drawAxes();
  
  int dataX[] = {0, 10, 20, 30, 40, 50, 60};
  int dataY[] = {0, 10, 5, 20, 10, 30, 15};
  int dataSize = sizeof(dataX) / sizeof(dataX[0]);
  
  graph.drawLineGraph(dataX, dataY, dataSize);
  
  u8g2.sendBuffer();
  
  delay(1000);  // Espera un segundo antes de actualizar la pantalla
}
```

### Ejemplo 3: Dibujar múltiples líneas

```cpp
#include <U8g2lib.h>
#include "SimpleGraph.h"

// Configura la pantalla para I2C
U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
SimpleGraph graph(u8g2);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  
  graph.drawAxes();
  
  int dataX1[] = {0, 10, 20, 30, 40, 50, 60};
  int dataY1[] = {0, 10, 5, 20, 10, 30, 15};
  int dataSize1 = sizeof(dataX1) / sizeof(dataX1[0]);

  int dataX2[] = {0, 10, 20, 30, 40, 50, 60};
  int dataY2[] = {5, 15, 10, 25, 15, 35, 20};
  int dataSize2 = sizeof(dataX2) / sizeof(dataX2[0]);

  int* dataX[] = {dataX1, dataX2};
  int* dataY[] = {dataY1, dataY2};
  int dataSize[] = {dataSize1, dataSize2};
  int numLines = 2;
  
  graph.drawMultipleLineGraphs(dataX, dataY, dataSize, numLines);

  u8g2.sendBuffer();
  
  delay(1000);  // Espera un segundo antes de actualizar la pantalla
}
```

### Ejemplo 4: Dibujar un gráfico de barras

```cpp
#include <U8g2lib.h>
#include "SimpleGraph.h"

// Configura la pantalla para I2C
U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
SimpleGraph graph(u8g2);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  
  graph.drawAxes();
  
  int barData[] = {10, 20, 30, 20, 10, 15};
  int barSize = sizeof(barData) / sizeof(barData[0]);
  graph.drawBarGraph(barData, barSize, 8);

  u8g2.sendBuffer();
  
  delay(1000);  // Espera un segundo antes de actualizar la pantalla
}
```

### Ejemplo 5: Dibujar un gráfico circular

```cpp
#include <U8g2lib.h>
#include "SimpleGraph.h"

// Configura la pantalla para I2C
U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
SimpleGraph graph(u8g2);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  
  int pieData[] = {10, 20, 30, 40};
  int pieSize = sizeof(pieData) / sizeof(pieData[0]);
  graph.drawPieChart(pieData, pieSize);

  u8g2.sendBuffer();
  
  delay(1000);  // Espera un segundo antes de actualizar la pantalla
}
```

### Ejemplo 6: Dibujar gráficos en subplots

```cpp
#include <U8g2lib.h>
#include "SimpleGraph.h"

// Configura la pantalla para I2C
U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
SimpleGraph graph(u8g2);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();

  // Región 1: Gráfico de dispersión
  graph.setSubplot(2, 2, 0);
  graph.drawAxes();
  int dataX1[] = {0, 10, 20, 30, 40, 50, 60};
  int dataY1[] = {0, 10, 5, 20, 10, 30, 15};
  int dataSize1 = sizeof(dataX1) / sizeof(dataX1[0]);
  graph.drawScatterPlot(dataX1, dataY1, dataSize1);

  // Región 2: Gráfico de líneas
  graph.setSubplot(2, 2, 1);
  graph.drawAxes();
  int dataX2[] = {0, 10, 20, 30, 40, 50, 60};
  int dataY2[] = {5, 15, 10, 25, 15, 35, 20};
  int dataSize2 = sizeof(dataX2) / sizeof(dataX2[0]);
  graph.drawLineGraph(dataX2, dataY2, dataSize2);

  // Región 3: Gráfico de barras
  graph.setSubplot(2, 2, 2);
  graph.drawAxes();
  int barData[] = {10, 20, 30, 20, 10, 15};
  int barSize = sizeof(barData) / sizeof(barData[0]);
  graph.drawBarGraph(barData, barSize, 8);

  // Región 4: Gráfico circular
  graph.setSubplot(2, 2, 3);
  int pieData[] = {10, 20, 30, 40};
  int pieSize = sizeof(pieData) / sizeof(pieData[0]);
  graph.drawPieChart(pieData, pieSize);

## Contribuciones

Las contribuciones son bienvenidas. Para contribuir, por favor sigue estos pasos:

1. Haz un fork del repositorio.
2. Crea una nueva rama (`git checkout -b feature/nueva-funcionalidad`).
3. Realiza tus cambios y haz commit (`git commit -am 'Agregar nueva funcionalidad'`).
4. Sube tus cambios a la rama (`git push origin feature/nueva-funcionalidad`).
5. Abre un Pull Request.

## Licencia

Este proyecto está licenciado bajo la licencia MIT. Consulta el archivo LICENSE para más detalles.

  u8g2.sendBuffer();
  
  delay(1000);  // Espera un segundo antes de actualizar la pantalla
}
```
