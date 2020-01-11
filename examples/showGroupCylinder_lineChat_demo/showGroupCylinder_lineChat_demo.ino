#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include"Histogram.h"

TFT_Histogram histogram=TFT_Histogram();
TFT_eSPI tft = TFT_eSPI();
void setup() {

  tft.init();                  
  histogram.initHistogram(&tft);                                             //Initialize histogram 
  histogram.formHistogram("A",1,530.55,40,TFT_RED);                          //Input lable,NO,value(high),width,colour
  histogram.formHistogram("B",2,120,40,TFT_BLACK);
  histogram.formHistogram("C",3,240,40,TFT_GREEN);
  histogram.formHistogram("D",4,210,40,TFT_BLUE);
  histogram.formHistogram("E",5,320,40,TFT_YELLOW);
    
}

void loop() {
  histogram.showHistogram();
  delay(2000); 
  histogram.groupCylinder(1);                                     //The function is to group these cylinders.
  delay(2000);
  histogram.lineChart(1,TFT_BLACK);                               // The function is to show a line chart. 
  delay(2000);
  histogram.groupCylinder(2);                                     //The function is to group these cylinders.
  delay(2000);
  histogram.lineChart(2,TFT_BLACK);
  delay(2000);
  histogram.groupCylinder(3);                                     //The function is to group these cylinders.
  delay(2000);
  histogram.lineChart(3,TFT_BLACK);
  delay(2000);
  histogram.groupCylinder(4);                                     //The function is to group these cylinders.
  delay(2000);
  histogram.lineChart(4,TFT_BLACK);
  delay(2000);
  histogram.groupCylinder(5);                                     //The function is to group these cylinders.
  delay(2000);
  histogram.lineChart(5,TFT_BLACK);
  delay(2000);

}
