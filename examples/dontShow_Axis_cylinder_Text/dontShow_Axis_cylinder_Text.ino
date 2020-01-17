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
  histogram.initHistogram(&tft);                                             //Initialize histogram 
  histogram.formHistogram("A",1,530.55,40,TFT_RED);                          //Input lable,NO,value(high),width,colour
  histogram.formHistogram("B",2,120,40,TFT_RED);
  histogram.formHistogram("C",3,240,40,TFT_RED);
  histogram.formHistogram("D",4,210,40,TFT_RED);
  histogram.formHistogram("E",5,320,40,TFT_RED);

}

void loop() {
  histogram.showHistogram();
  delay(1000);
  
  histogram.notShowCylinder(1);                                             //The function is not show a cylindricity of the histogram  on screen
  histogram.showHistogram();
  delay(1000);
  histogram.notShowCylinder(2);                                             //The function is not show a cylindricity of the histogram  on screen
  histogram.showHistogram();
  delay(1000);
  histogram.notShowCylinder(3);                                             //The function is not show a cylindricity of the histogram  on screen
  histogram.showHistogram();
  delay(1000);
  histogram.notShowCylinder(4);                                             //The function is not show a cylindricity of the histogram  on screen
  histogram.showHistogram();
  delay(1000);
  histogram.notShowCylinder(5);                                             //The function is not show a cylindricity of the histogram  on screen
  histogram.showHistogram();
  delay(1000);
  
  histogram.notShowAxis();                                              //The function is not show axes on screen
  delay(3000);
  
  histogram.notShowtext(1);                                         //The function is not show text of a cylinder on screen
  delay(1000);
  histogram.notShowtext(2);                                         //The function is not show text of a cylinder on screen
  delay(1000);
  histogram.notShowtext(3);                                         //The function is not show text of a cylinder on screen
  delay(1000);
  histogram.notShowtext(4);                                         //The function is not show text of a cylinder on screen
  delay(1000);
  histogram.notShowtext(5);                                         //The function is not show text of a cylinder on screen
  delay(1000);
  showSeeed(TFT_MAGENTA);
  delay(2000);
}

void showSeeed(int colour)
{
  tft.setRotation(3);                                       
  tft.setTextSize(3);
  tft.fillScreen(colour);  
  tft.drawString("Welcome",50, 50);
  tft.setTextSize(5);
  tft.drawString("To Seeed!",50, 120);
  tft.setRotation(2);                                       
}
