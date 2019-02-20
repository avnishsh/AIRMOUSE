#include "mbed.h"
#include "USBMouse.h"
#include  "TSISensor.h"
#include "MMA8451Q.h"
USBMouse Airmouse;
TSISensor tsi;
Serial pc(USBTX,USBRX);
MMA8451Q acc(PTE25,PTE24,0x1D<<1);
 
 int main()
 {
     char sense;
     float slide=0;
     float x=0,y=0;
     while(1)
     {
      
      slide=tsi.readPercentage();
     if(slide<0.33 && slide>0)
        {Airmouse.press(MOUSE_RIGHT);}
    else if(slide>0.66 && slide<1)
     {Airmouse.press(MOUSE_LEFT);}
     
      if(pc.readable() )
      {sense=pc.getc();}
      switch(sense)
      {
          case 's':
          x=acc.getAccX()*2;
           y=acc.getAccY()*2;
           
           break;
           
           case 'm':
           x=acc.getAccX()*6;
           y=acc.getAccY()*6;
           
           break;
           
           case 'f':
           x=acc.getAccX()*11;
           y=acc.getAccY()*11;
          break;
     }
      Airmouse.move(-y,x);
     }
     }
     