#include"Histogram.h"

TFT_Histogram::TFT_Histogram()
{
}
//初始化
void TFT_Histogram::Histogram_init(TFT_eSPI* tft)
{
  tft_Histogram = tft;
  tft_Histogram->setRotation(2);                    //原点在正对usb口的左下角
  tft_Histogram->drawFastHLine(20,20,200,TFT_BLACK);//正对usb口的竖线（x）
  tft_Histogram->drawFastVLine(20,20,280,TFT_BLACK);//正对usb横线（y）

  //x、y轴尾的箭头
  tft_Histogram->drawLine(10,290,20,300,TFT_BLACK);
  tft_Histogram->drawLine(30,290,20,300,TFT_BLACK);
  tft_Histogram->drawLine(210,10,220,20,TFT_BLACK);
  tft_Histogram->drawLine(210,30,220,20,TFT_BLACK);
  
  head=(struct Histogram_param *)malloc(sizeof(struct Histogram_param ));//设置链表头节点（不存数据）
  rear=head;
  rear->next=NULL;
}

//记录柱状体参数函数
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
}

//寻找最大值与最小值、计算总宽度
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
    number++;
  }
}

//显示柱状图
void TFT_Histogram::Histogram_show()
{
  struct Histogram_param *h=head->next;
  int high,width_P;
  this->compare();
  tft_Histogram->setTextSize(2);//设置文本字体大小
  tft_Histogram->setTextColor(TFT_BLACK, TFT_YELLOW);
  
  while(h!=NULL)
  {
    high=h->value*180/Histogram_max;    //计算高度值比例
    //计算宽度比例
    if(number>=4)
      {
        width_P=h->wide*(280-number*10-10)/Histogram_sum_wide;
      }
      else
      {
        width_P=h->wide*(280-150)/Histogram_sum_wide;
      }
      
    if(high<2) high=2;
    if(width_P<8) width_P=8;
    
    tft_Histogram->drawRect(20,Histogram_width,high,width_P, h->colour);//打印柱形
    tft_Histogram->fillRect(20,Histogram_width,high,width_P, h->colour);//填充颜色

    tft_Histogram->setRotation(3);                                       //设置文字或数字打印参考原点
    tft_Histogram->drawNumber(h->value,Histogram_width, 240-high-37);    //显示值（高度）
    tft_Histogram->drawString(h->lable,Histogram_width,222);             //文本字符串
    tft_Histogram->setRotation(2);                                       //还原参考原点

    
    Histogram_width=Histogram_width+width_P+10;                  //记录总宽度
    h=h->next;
  }
}
