#include"Histogram.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TFT_Histogram::TFT_Histogram()
{
  head=(struct Histogram_param *)malloc(sizeof(struct Histogram_param ));//no any data in this linked list of head
  rear=head;
  rear->next=NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Initialize                                                                                                                                           //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::histogramInit(TFT_eSPI* tft)
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
//The function is record some datas of cylindricity                                                                                                    //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::histogramForm(String lable,int NO,double Histogram_value,int Histogram_WIDTH,uint32_t  colour)
{ 
  if(number>8) return;
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
//The function is to find the maximum value and the minimum value                                                                                      //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
//The function is show  the histogram  on screen                                                                                                       //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::histogramShow()
{ 
  this->histogramInit(tft_Histogram);
  struct Histogram_param *h=head->next;
  double high=0,width_P=0;
  Histogram_width=30;
  this->compare();
  tft_Histogram->setTextSize(2);                        //The function is to set size of text 
  tft_Histogram->setTextColor(TFT_BLACK, TFT_YELLOW);

  while(h!=NULL)
  {
    if(NotShow==h->NO){NotShow=0;h=h->next; continue;}
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
//  tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-30);    //显示值（高度）
    tft_Histogram->drawFloat(h->value,1 ,Histogram_width, 240-high-30);
    tft_Histogram->drawString(h->lable,Histogram_width,222);             //文本字符串
    tft_Histogram->setRotation(2);                                       //还原参考原点

    
    Histogram_width=Histogram_width+width_P+10;                  //记录总宽度
    h=h->next;
  }


}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is show  many cylinders on screen                                                                                                       //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void TFT_Histogram::histogramShowMany()
{ 
  this->histogramInit(tft_Histogram);
  struct Histogram_param *h=head->next;
  int high=0,width_P=1;
  Histogram_width=22;
  this->compare();

  while(h!=NULL)
  {
    high=h->value*180/Histogram_max;                                 //Calculate the ratio of height value

    if(Histogram_width>300-width_P) break;
    if(high<2) high=2;
    if(width_P<1) width_P=1;
    
    tft_Histogram->drawRect(20,Histogram_width,high,width_P, h->colour);//打印柱形
    tft_Histogram->fillRect(20,Histogram_width,high,width_P, h->colour);//填充颜色
    
    Histogram_width=Histogram_width+width_P+1;                  //记录总宽度
    h=h->next;
  }


}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is set size of text of the histogram  and the background of screen                                                                    ///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::setTextSizeColourHistogram(int lableSize,int valueSize,int textColour,int textBackgroundColour,int background)
{
  struct Histogram_param *h=head->next;
  int high=0,width_P=0;
  Histogram_width=30; 
  this->compare();
  tft_Histogram->fillScreen(background);
  tft_Histogram->setRotation(2);                         //The origin is in the lower left corner facing the usb port
  tft_Histogram->drawFastHLine(20,20,200,TFT_BLACK);    //It is x axis facing usb port
  tft_Histogram->drawFastVLine(20,20,280,TFT_BLACK);   //It is y axis facing usb port

  //Draw arrow of x,y axis
  tft_Histogram->drawLine(10,290,20,300,TFT_BLACK);
  tft_Histogram->drawLine(30,290,20,300,TFT_BLACK);
  tft_Histogram->drawLine(210,10,220,20,TFT_BLACK);
  tft_Histogram->drawLine(210,30,220,20,TFT_BLACK);
  
  while(h!=NULL)
  {
    if(NotShow==h->NO){NotShow=0;h=h->next; continue;}
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
//  tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-40);    //显示值（高度）
    tft_Histogram->drawFloat(h->value,1 ,Histogram_width, 240-high-40);

    tft_Histogram->setTextSize(lableSize);
    tft_Histogram->drawString(h->lable,Histogram_width,222);             //文本字符串
    tft_Histogram->setRotation(2);                                       //还原参考原点

    
    Histogram_width=Histogram_width+width_P+10;                  //记录总宽度
    h=h->next;
  }
  width_P=0;

  Histogram_width=30;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is show histogram more little                                                                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::histogramShrinkShow(int x,int y,int shrinkMultiple)
{ 
  Histogram_width=y+2;
  tft_Histogram->fillScreen(TFT_WHITE);                   //Fill the screen with white
  tft_Histogram->setRotation(2);                         //The origin is in the lower left corner facing the usb port
  tft_Histogram->drawFastHLine(x,y,200/shrinkMultiple,TFT_BLACK);    //It is x axis facing usb port
  tft_Histogram->drawFastVLine(x,y,280/shrinkMultiple,TFT_BLACK);   //It is y axis facing usb port

//  Draw arrow of x,y axis
  tft_Histogram->drawLine(x+200/shrinkMultiple,y,x+200/shrinkMultiple-5,y-5,TFT_BLACK);
  tft_Histogram->drawLine(x+200/shrinkMultiple,y,x+200/shrinkMultiple-5,y+5,TFT_BLACK);
  tft_Histogram->drawLine(x,y+280/shrinkMultiple,x+5,y+280/shrinkMultiple-5,TFT_BLACK);
  tft_Histogram->drawLine(x,y+280/shrinkMultiple,x-5,y+280/shrinkMultiple-5,TFT_BLACK); 
  struct Histogram_param *h=head->next;
  int high=0,width_P=0;
  this->compare();
  tft_Histogram->setTextSize(0);                        //The function is to set size of text 
  tft_Histogram->setTextColor(TFT_BLACK, TFT_YELLOW);

  while(h!=NULL)
  {
    if(NotShow==h->NO){NotShow=0;h=h->next; continue;}
    high=h->value*180/Histogram_max/shrinkMultiple;                                 //Calculate the ratio of height value

    if(number>=4)
      {
        width_P=h->wide*(280-number*10-10)/Histogram_sum_wide/shrinkMultiple;      //Calculate the ratio of width value
      }
      else
      {
        width_P=h->wide*(280-150)/Histogram_sum_wide/shrinkMultiple;           
      }
    if(Histogram_width>y+280/shrinkMultiple-width_P) break;
    if(high<2) high=2;
    if(width_P<1) width_P=1;
    
    tft_Histogram->drawRect(x,Histogram_width,high,width_P, h->colour);//打印柱形
    tft_Histogram->fillRect(x,Histogram_width,high,width_P, h->colour);//填充颜色

    tft_Histogram->setRotation(3);                                       //设置文字或数字打印参考原点
    tft_Histogram->setTextSize(0);
//  tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-x-8);    //显示值（高度）
    tft_Histogram->drawFloat(h->value,1 ,Histogram_width, 240-high-x-8);
    tft_Histogram->drawString(h->lable,Histogram_width,240-x);             //文本字符串
    tft_Histogram->setRotation(2);                                       //还原参考原点
    
    Histogram_width=Histogram_width+width_P+2;                  //记录总宽度
    h=h->next;
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is not show a cylindricity of the histogram  on screen                                                                                  //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::notShowCylinder(int NO)
{
  NotShow=NO;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is delete a cylinder                                                                                  //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::deleteCylinder(int NO)
{
  struct Histogram_param *p=head,*q;
  while(p->next->NO!=NO && p->next!=NULL){
    p=p->next;
  }
  if(p->next==NULL) return;
  q=p->next;
  p->next=q->next;
  free(q);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is not show axes on screen                                                                                                              //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::notShowAxis()
{
  tft_Histogram->fillScreen(TFT_WHITE); 
  struct Histogram_param *h=head->next;
  int high=0,width_P=0;
  Histogram_width=30;
  this->compare();
  tft_Histogram->setTextSize(2);                        //The function is to set size of text 
  tft_Histogram->setTextColor(TFT_BLACK, TFT_YELLOW);

  while(h!=NULL)
  {
    if(NotShow==h->NO){NotShow=0;h=h->next; continue;}
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
//  tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-30);    //显示值（高度）
    tft_Histogram->drawFloat(h->value,1 ,Histogram_width, 240-high-30);
    tft_Histogram->drawString(h->lable,Histogram_width,222);             //文本字符串
    tft_Histogram->setRotation(2);                                       //还原参考原点

    
    Histogram_width=Histogram_width+width_P+10;                  //记录总宽度
    h=h->next;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is not show text of a cylinder on screen                                                                                                              //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::notShowtext(int NO)
{ 
  this->histogramInit(tft_Histogram);
  struct Histogram_param *h=head->next;
  int high=0,width_P=0;
  Histogram_width=30;
  this->compare();
  tft_Histogram->setTextSize(2);                        //The function is to set size of text 
  tft_Histogram->setTextColor(TFT_BLACK, TFT_YELLOW);

  while(h!=NULL)
  {
    if(NotShow==h->NO){NotShow=0;h=h->next; continue;}
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
    if(h->NO==NO){ Histogram_width=Histogram_width+width_P+10; h=h->next;continue; }
    tft_Histogram->setRotation(3);                                       //设置文字或数字打印参考原点
    tft_Histogram->setTextSize(1);
//    tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-30);    //显示值（高度）
    tft_Histogram->drawFloat(h->value,1 ,Histogram_width, 240-high-30);
    tft_Histogram->drawString(h->lable,Histogram_width,222);             //文本字符串
    tft_Histogram->setRotation(2);                                       //还原参考原点

    
    Histogram_width=Histogram_width+width_P+10;                  //记录总宽度
    h=h->next;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is change these parameter of the histogram                                                                                              //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::changeParam(int NO,String lable,double Histogram_value,int Histogram_WIDTH,uint32_t  colour)
{
  struct Histogram_param * h=head->next;
  while(h!=NULL&&h->NO!=NO){
    h=h->next;
  }

  h->lable=lable;
  h->value=Histogram_value;
  h->wide=Histogram_WIDTH;
  h->colour=colour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is to group these cylinders.                                                                                                            //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::groupCylinder(int Cylinder_Number)
{
  this->histogramInit(tft_Histogram);
  struct Histogram_param *h=head->next;
  double high=0,width_P=0;
  Histogram_width=30;
  this->compare();
  tft_Histogram->setTextSize(2);                        //The function is to set size of text 
  tft_Histogram->setTextColor(TFT_BLACK, TFT_YELLOW);

  while(h!=NULL)
  {
    if(NotShow==h->NO){NotShow=0;h=h->next; continue;}
    for(int i=1;i<=Cylinder_Number;i++)
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
  //  tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-30);    //显示值（高度）
      tft_Histogram->drawFloat(h->value,1 ,Histogram_width, 240-high-30);
      tft_Histogram->drawString(h->lable,Histogram_width,222);             //文本字符串
      tft_Histogram->setRotation(2);  
      
      Histogram_width=Histogram_width+width_P;//还原参考原点
      h=h->next;
    }
    if(Histogram_width>300-width_P) break;
    Histogram_width=Histogram_width+10;                  //记录总宽度
  }

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is to show a line chart.                                                                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::lineChat(int colour)
{
  this->histogramInit(tft_Histogram);
  struct Histogram_param *h=head->next;
  double high=0,width_P=0;
  Histogram_width=30;
  this->compare();
  tft_Histogram->setTextSize(2);                        //The function is to set size of text 
  tft_Histogram->setTextColor(TFT_BLACK, TFT_YELLOW);
  int x=20,y=20;
  while(h!=NULL)
  {
    if(NotShow==h->NO){NotShow=0;h=h->next; continue;}
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
//  tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-30);    //显示值（高度）
    tft_Histogram->drawFloat(h->value,1 ,Histogram_width, 240-high-30);
    tft_Histogram->drawString(h->lable,Histogram_width,222);             //文本字符串
    tft_Histogram->setRotation(2);                                       //还原参考原点
    tft_Histogram->drawLine(x,y,21+high,Histogram_width,colour);        //to draw line chat
    x=21+high;
    y=Histogram_width;
    Histogram_width=Histogram_width+width_P+10;                  //记录总宽度
    h=h->next;
  }

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The function is to show a line chart.                                                                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TFT_Histogram::lineChat(int Cylinder_Number,int colour)
{
  this->histogramInit(tft_Histogram);
  struct Histogram_param *h=head->next;
  double high=0,width_P=0;
  Histogram_width=30;
  int x=20,y=20;
  this->compare();
  tft_Histogram->setTextSize(2);                        //The function is to set size of text 
  tft_Histogram->setTextColor(TFT_BLACK, TFT_YELLOW);

  while(h!=NULL)
  {
    if(NotShow==h->NO){NotShow=0;h=h->next; continue;}
    for(int i=1;i<=Cylinder_Number;i++)
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
  //  tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-30);    //显示值（高度）
      tft_Histogram->drawFloat(h->value,1 ,Histogram_width, 240-high-30);
      tft_Histogram->drawString(h->lable,Histogram_width,222);             //文本字符串
      tft_Histogram->setRotation(2);  
      tft_Histogram->drawLine(x,y,21+high,Histogram_width,colour);        //to draw line chat
      x=21+high;
      y=Histogram_width;
      
      Histogram_width=Histogram_width+width_P;//还原参考原点
      h=h->next;
    }
    if(Histogram_width>300-width_P) break;
    Histogram_width=Histogram_width+10;                  //记录总宽度
  }

}
