
#include <TFT_eSPI.h>
#include <SPI.h>

struct Histogram_param{ 
  String lable;         //lable
  int NO;               //NO
  int wide;             //width
  int    value;         //value(high)
  int    colour;        //the colour of cylindricity
  struct Histogram_param *next;     //Use linked lists to record these datas of cylindricity
  };

class TFT_Histogram 
{

  public:
        struct Histogram_param *head,*rear;                                 //this's a linked list of pointer of head and rear

        void Histogram_init(TFT_eSPI* tft);                           //initialization
        TFT_Histogram();                                               //destructor     
        void Histogram_form(String lable,int NO,int Histogram_value,int Histogram_WIDTH,uint32_t  colour);      //Parameters input about a histogram  
        void Histogram_show();                                                                                  //The function is show  the histogram  on screen
        void setTextSizeColourHistogram(int lableSize,int valueSize,int textColour,int textBackgroundColour);

  private:
       TFT_eSPI* tft_Histogram; 

       void compare();                                                      //to abtain the maximum value and  and minimum value
       int number=1;                                                      //record these number of cylindricity
       int Histogram_max,Histogram_min,Histogram_sum_wide;               //It is a value of high that Histogram_max is to record the maximum value and Histogram_min is to record the minimum value
                                                                        //Histogram_sum_wide is record the width of the sum of all cylindricitys
       int Histogram_width=30;                                         //Histogram_width is record the length of the sum of all cylindricitys                                 
};
