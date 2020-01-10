
#include <TFT_eSPI.h>
#include <SPI.h>

struct Histogram_param{ 
  String lable;          //lable
  int    NO;            //NO
  int    wide;         //width
//int    value;       //value(high)
  double value;
  int    colour;    //the colour of cylindricity
  struct Histogram_param *next;     //Use linked lists to record these datas of cylindricity
  };

class TFT_Histogram 
{

  public:
        TFT_Histogram();                                                                                              //destructor     
        struct Histogram_param *head,*rear;                                                                          //this's a linked list of pointer of head and rear
        void histogramInit(TFT_eSPI* tft);                                                                          //initialization
        void histogramForm(String lable,int NO,double Histogram_value,int Histogram_WIDTH,uint32_t  colour);       //Parameters input about a histogram  
        void histogramShow();                                                                                     //The function is show  the histogram  on screen
        void setTextSizeColourHistogram(int lableSize,int valueSize,int textColour,int textBackgroundColour,int background);            //The function is set size of text of the histogram  and the background of screen 
        void histogramShrinkShow(int x,int y,int shrinkMultiple);                                               //The function is show histogram more little
        void notShowCylinder(int NO);                                                                          //The function is not show a cylindricity of the histogram  on screen
        void changeParam(int NO,String lable,double Histogram_value,int Histogram_WIDTH,uint32_t  colour);    //The function is change these parameter of the histogram
        void notShowAxis();                                                                                  //The function is not show axes on screen
        void notShowtext(int NO);                                                                           //The function is not show text of a cylinder on screen
        void deleteCylinder(int NO);                                                                       //The function is delete a cylinder 
        void groupCylinder(int Cylinder_Number);                                                          //The function is to group these cylinders.
        void lineChart(int colour);                                                                       // The function is to show a line chart. 
        void lineChart(int Cylinder_Number,int colour);                                                  // The function is to show a line chart. 
//        void histogramShowMany();

  private:
       TFT_eSPI* tft_Histogram; 
       int NotShow=0;                                                       //this value is let a cylinder not showing on screen 
       void compare();                                                     //to abtain the maximum value and  and minimum value
       int number=1;                                                      //record amount of cylindricity
       double Histogram_max,Histogram_min;                               //It is a value of high that Histogram_max is to record the maximum value and Histogram_min is to record the minimum value
       int Histogram_sum_wide;                                          //Histogram_sum_wide is record the width of the sum of all cylindricitys
       double Histogram_width=30;                                      //Histogram_width is record the length of the sum of all cylindricitys                                 
};
