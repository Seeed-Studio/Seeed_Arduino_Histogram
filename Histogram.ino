/*
  柱状图案例
*/

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include"Histogram.h"

TFT_Histogram histogram=TFT_Histogram();
TFT_eSPI tft = TFT_eSPI(); 
    
void setup(void) {
  tft.init();                 
   
  histogram.Histogram_init(&tft);                                 //Initialize histogram 
  histogram.Histogram_form("a",1,50,40,TFT_RED);             //Input lable,NO,value(high),width,colour
  histogram.Histogram_form("b",2,60,40,TFT_RED);
  histogram.Histogram_form("c",3,10,50,TFT_RED);
  histogram.Histogram_form("d",4,53,50,TFT_RED);
  histogram.Histogram_form("e",5,33,30,TFT_RED);
  
  histogram.Histogram_show(); 
  delay(5000);
  histogram.notShowCylindricity(1);
  histogram.Histogram_show(); 
  delay(5000);
}

void loop() {
    histogram.Histogram_show(); 
  delay(3000);

  histogram.HistogramShrinkShow(130,180,2);
  delay(3000);
  showSeeeder();
  delay(3000);
  histogram.setTextSizeColourHistogram(1,2,TFT_BLACK,TFT_GREEN);
  delay(3000);
  histogram.HistogramShrinkShow(50,60,3);
  delay(3000);
}

void showSeeeder()
{
  tft.setRotation(3);                                       
  tft.setTextSize(5);
  tft.fillScreen(TFT_BLUE);  
  tft.drawString("Seeeder:",50, 50);
  tft.setTextSize(3);
  tft.drawString("Hello world!",50, 120);
  tft.setRotation(2);                                       
}
