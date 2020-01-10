#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include"Histogram.h"

TFT_Histogram histogram=TFT_Histogram();
TFT_eSPI tft = TFT_eSPI();
void setup() {

  tft.init();                  
  histogram.initHistogram(&tft);                                             //Initialize histogram 
  histogram.formHistogram("A",1,530.55,40,TFT_RED);                          //Input lable,NO,value(high),width,colour
  histogram.formHistogram("B",2,120,40,TFT_RED);
  histogram.formHistogram("C",3,240,40,TFT_RED);
  histogram.formHistogram("D",4,210,40,TFT_RED);
  histogram.formHistogram("E",5,320,40,TFT_RED);

}

void loop() {
  histogram.showHistogram();
  delay(2000);
  histogram.shrinkShowHistogram(70,60,3);                                         //The function is show histogram more little
  delay(2000);
  histogram.shrinkShowHistogram(130,180,2);                                     //The function is show histogram more little
  delay(2000);
    histogram.shrinkShowHistogram(50,80,3);                                         //The function is show histogram more little
  delay(2000);
  histogram.shrinkShowHistogram(20,20,2);                                     //The function is show histogram more little
  delay(2000);
}
