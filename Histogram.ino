/*
  柱状图案例
*/

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include"Histogram.h"

TFT_Histogram histogram=TFT_Histogram();
TFT_eSPI tft = TFT_eSPI();     
void setup(void) {
  int i=0;
  tft.init();                 
  tft.fillScreen(TFT_WHITE);  //填充背景颜色为白色

  
  histogram.Histogram_init(&tft);       //柱状图设计初始化
  
  histogram.Histogram_form("one",5,2000,40,TFT_RED);      //输入柱状图参数：标签、序号、值（高度）、宽度、颜色
  histogram.Histogram_form("two",5,5000,40,TFT_RED);
  histogram.Histogram_form("three",1,8541,50,TFT_RED);
  histogram.Histogram_form("four",5,1550,50,TFT_RED);
  histogram.Histogram_form("five",5,5000,30,TFT_RED);
  
  histogram.Histogram_show();                             //显示柱状图
}

void loop() {
}
