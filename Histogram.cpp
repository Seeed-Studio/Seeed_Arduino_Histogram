#include"Histogram.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TFT_Histogram::TFT_Histogram()
{
  head=(struct Histogram_param *)malloc(sizeof(struct Histogram_param ));//no any data in this linked list of head
  rear=head;
  rear->next=NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Initialize
void TFT_Histogram::Histogram_init(TFT_eSPI* tft)
{
  tft_Histogram = tft;
  tft_Histogram->fillScreen(TFT_WHITE);                   //Fill the screen with white
  tft_Histogram->setRotation(2);                         //The origin is in the lower left corner facing the usb port
  tft_Histogram->drawFastHLine(20,20,200,TFT_BLACK);    //It is x axis facing usb port
  tft_Histogram->drawFastVLine(20,20,280,TFT_BLACK);   //It is y axis facing usb port

  //Draw arrow of x,y axis
  tft_Histogram->drawLine(10,290,20,300,TFT_BLACK);
  tft_Histogram->drawLine(30,290,20,300,TFT_BLACK);
  tft_Histogram->drawLine(210,10,220,20,TFT_BLACK);
  tft_Histogram->drawLine(210,30,220,20,TFT_BLACK);


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is record some datas of cylindricity
void TFT_Histogram::Histogram_form(String lable,int NO,int Histogram_value,int Histogram_WIDTH,uint32_t  colour)
{ 
  struct Histogram_param *p;
  p=(struct Histogram_param *)malloc(sizeof(struct Histogram_param ));
  p->NO=NO;
  p->wide=Histogram_WIDTH;
  p->value=Histogram_value;
  p->colour=colour;
  p->lable=lable;
  rear->next=p;
  rear=p;
  rear->next=NULL;
   number++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is to find the maximum value and the minimum value
void TFT_Histogram::compare()
{
  struct Histogram_param *p=head->next;
  
  Histogram_max=Histogram_min=p->value;
  p=p->next;
  while(p!=NULL){
    if((p->value)>Histogram_max) Histogram_max=p->value;
    if((p->value)<Histogram_min) Histogram_min=p->value;
    p=p->next;
  }

  p=head->next;
  Histogram_sum_wide=p->wide;
  p=p->next;
  while(p!=NULL){
    Histogram_sum_wide=Histogram_sum_wide+p->wide;
    p=p->next;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is show  the histogram  on screen
void TFT_Histogram::Histogram_show()
{ 
  this->Histogram_init(tft_Histogram);
  struct Histogram_param *h=head->next;
  int high=0,width_P=0;
  this->compare();
  tft_Histogram->setTextSize(2);                        //The function is to set size of text 
  tft_Histogram->setTextColor(TFT_BLACK, TFT_YELLOW);

  while(h!=NULL)
  {
    high=h->value*180/Histogram_max;                                 //Calculate the ratio of height value

    if(number>=4)
      {
        width_P=h->wide*(280-number*10-10)/Histogram_sum_wide;      //Calculate the ratio of width value
      }
      else
      {
        width_P=h->wide*(280-150)/Histogram_sum_wide;           
      }
    if(Histogram_width>300-width_P) break;
    if(high<2) high=2;
    if(width_P<8) width_P=8;
    
    tft_Histogram->drawRect(20,Histogram_width,high,width_P, h->colour);//打印柱形
    tft_Histogram->fillRect(20,Histogram_width,high,width_P, h->colour);//填充颜色

    tft_Histogram->setRotation(3);                                       //设置文字或数字打印参考原点
    tft_Histogram->setTextSize(1);
    tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-30);    //显示值（高度）
    tft_Histogram->drawString(h->lable,Histogram_width,222);             //文本字符串
    tft_Histogram->setRotation(2);                                       //还原参考原点

    
    Histogram_width=Histogram_width+width_P+10;                  //记录总宽度
    h=h->next;
  }
  Histogram_width=30;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is set size of text of the histogram
void TFT_Histogram::setTextSizeColourHistogram(int lableSize,int valueSize,int textColour,int textBackgroundColour)
{
  struct Histogram_param *h=head->next;
  int high=0,width_P=0;
  Histogram_width=30; 
  this->compare();
  this->Histogram_init(tft_Histogram);
  while(h!=NULL)
  {
    high=h->value*180/Histogram_max;                                 //Calculate the ratio of height value

    if(number>=4)
      {
        width_P=h->wide*(280-number*10-10)/Histogram_sum_wide;      //Calculate the ratio of width value
      }
    else
      {
        width_P=h->wide*(280-150)/Histogram_sum_wide;           
      }      
    if(Histogram_width>300-width_P) break;
    if(high<2) high=2;
    if(width_P<8) width_P=8;
    tft_Histogram->drawRect(20,Histogram_width,high,width_P, h->colour);//打印柱形
    tft_Histogram->fillRect(20,Histogram_width,high,width_P, h->colour);//填充颜色

    if(lableSize>=4||lableSize<0) lableSize=1;
    if(valueSize>=4||valueSize<0) valueSize=1;
    tft_Histogram->setRotation(3);                                       //设置文字或数字打印参考原点   
    tft_Histogram->setTextSize(valueSize);
    tft_Histogram->setTextColor(textColour, textBackgroundColour);
    tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-30);    //显示值（高度）
    tft_Histogram->setTextSize(lableSize);
    tft_Histogram->drawString(h->lable,Histogram_width,222);             //文本字符串
    tft_Histogram->setRotation(2);                                       //还原参考原点

    
    Histogram_width=Histogram_width+width_P+10;                  //记录总宽度
    h=h->next;
  }
  width_P=0;

  Histogram_width=30;
}
