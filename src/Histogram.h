
#include <TFT_eSPI.h>
#include <SPI.h>

struct Histogram_param{ 
  char lable[24];                           //lable
  uint8_t    NO;                         //NO
  uint16_t    wide;                     //width
  //int    value;                      //value(high)
  float value;
  uint32_t    colour;                //the colour of cylindricity
  struct Histogram_param *next;     //Use linked lists to record these datas of cylindricity
  };

class TFT_Histogram 
{

  public:
        TFT_Histogram();                                                                                                  //destructor     
        void initHistogram(TFT_eSPI* tft);                                                                               //initialization
        void formHistogram(char *lable,uint8_t NO,float Histogram_value,uint16_t Histogram_WIDTH,uint32_t  colour);    //Input parameters about a cylinder  
        void showHistogram();                                                                                          //The function is show  the histogram  on screen
        void setTextSizeColourHistogram(uint8_t lableSize,float valueSize,uint32_t textColour,uint32_t textBackgroundColour,uint32_t background);            //The function is set size of text of the histogram  and the background of screen 
        void shrinkShowHistogram(uint16_t x,uint16_t y,uint8_t shrinkMultiple);                                     //The function is show histogram more little
        void notShowCylinder(uint8_t NO);                                                                          //The function is not show a cylindricity of the histogram  on screen
        void changeParam(uint8_t NO,char *lable,float Histogram_value,uint32_t  colour);//The function is change these parameter of the histogram
        void notShowAxis();                                                                                      //The function is not show axes on screen
        void notShowtext(uint8_t NO);                                                                           //The function is not show text of a cylinder on screen
        void deleteCylinder(uint8_t NO);                                                                       //The function is delete a cylinder 
        void groupCylinder(uint8_t Cylinder_Number);                                                          //The function is to group these cylinders.
        void lineChart(uint32_t colour);                                                                     // The function is to show a line chart. 
        void lineChart(uint8_t Cylinder_Number,uint32_t colour);                                            // The function is to show a line chart. 
        void drawArrow();                                                                                  //Draw arrow of x/y axis
        void initParams();                                                                                //initialze some params
        void showOne();                                                                                  //Show a cylinder
        void showText();                                                                                //Display text
        void compare();                                                                                //to abtain the maximum value and  and minimum value
        void ShowAxis();                                                                              //The function is not show axes on screen
        void changeWidth(uint8_t NO,uint16_t Histogram_WIDTH);                                       //The function is to change width of cylinder
  private:
       TFT_eSPI* tft_Histogram; 
       uint8_t notShow=0;                                                                           //this value is let a cylinder not showing on screen 
       uint32_t number=1;                                                                          //record amount of cylindricity(sum=number-1)
       float histogramMax,histogramMin;                                                           //It is a value of high that histogramMax is to record the maximum value and histogramMin is to record the minimum value
       uint16_t Histogram_sum_wide;                                                              //Histogram_sum_wide is record the width of the sum of all cylindricitys
       uint16_t Histogram_width=30;                                                             //Histogram_width is record the length of the sum of all cylindricitys                                 
       float high=0;
       float width_P=0;
       struct Histogram_param *head,*rear;                                                   //this's a linked list of pointer of head and rear
       struct Histogram_param *h=NULL;
       uint8_t limitWidth=0;                                                               //A flag of width
//       uint16_t changeNOFlag=9999;
};
