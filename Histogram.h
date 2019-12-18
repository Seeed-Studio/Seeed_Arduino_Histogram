
#include <TFT_eSPI.h>
#include <SPI.h>

struct Histogram_param{ 
  String lable;         //标签
  int NO;               //序号
  int wide;             //柱形宽度
  int    value;         //值（高度）
  int    colour;        //柱状体颜色
  struct Histogram_param *next;     //用链表来记录每个柱状体的参数
  };

class TFT_Histogram 
{

  public:
        struct Histogram_param *head,*rear;   //用链表来记录每个柱状体的参数
        int number=1;      //记录圆柱个数
        int Histogram_max,Histogram_min,Histogram_sum_wide;               //Histogram_max,Histogram_min记录柱状体最大值与最小值（高度）;Histogram_sum_wide:总宽度
        int Histogram_width=30;                        //记录柱状体的总体长度
        TFT_Histogram();                                                                                        //析构函数
        void Histogram_init(TFT_eSPI* tft);                                                                                  //柱状体的一些初始化
        void Histogram_form(String lable,int NO,int Histogram_value,int Histogram_WIDTH,uint32_t  colour);      //柱状体的参数输入记录
        void Histogram_show();                                                                                  //显示柱状体的整体形状
        void compare();                                                                                         //
  private:
       TFT_eSPI* tft_Histogram; 
};
