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
  histogram.histogramShrinkShow(70,60,3);                                         //The function is show histogram more little
  delay(2000);
  histogram.histogramShrinkShow(130,180,2);                                     //The function is show histogram more little
  delay(2000);
    histogram.histogramShrinkShow(50,80,3);                                         //The function is show histogram more little
  delay(2000);
  histogram.histogramShrinkShow(20,20,2);                                     //The function is show histogram more little
  delay(2000);
}
