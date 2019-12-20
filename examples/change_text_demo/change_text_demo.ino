#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include"Histogram.h"

TFT_Histogram histogram=TFT_Histogram();
TFT_eSPI tft = TFT_eSPI(); 
    
void setup() {

  tft.init();                  
  histogram.histogramInit(&tft);                                             //Initialize histogram 
  histogram.histogramForm("A",1,530.55,40,TFT_RED);                          //Input lable,NO,value(high),width,colour
  histogram.histogramForm("B",2,120,40,TFT_RED);
  histogram.histogramForm("C",3,240,40,TFT_RED);
  histogram.histogramForm("D",4,210,40,TFT_RED);
  histogram.histogramForm("E",5,320,40,TFT_RED);
}

void loop() {
  histogram.histogramShow();
  delay(2000);
  histogram.setTextSizeColourHistogram(1,2,TFT_RED,TFT_RED,TFT_WHITE);            //The function is set size of text of the histogram  and the background of screen
  delay(2000);
  histogram.setTextSizeColourHistogram(2,1,TFT_GREEN,TFT_GREEN,TFT_YELLOW);            //The function is set size of text of the histogram  and the background of screen
  delay(2000); 
  histogram.setTextSizeColourHistogram(1,1,TFT_YELLOW,TFT_YELLOW,TFT_GREEN);            //The function is set size of text of the histogram  and the background of screen
  delay(2000);
  histogram.setTextSizeColourHistogram(2,2,TFT_BLACK,TFT_BLACK,TFT_YELLOW);            //The function is set size of text of the histogram  and the background of screen
  delay(2000);
}
