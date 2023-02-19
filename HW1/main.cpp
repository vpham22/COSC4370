#include <iostream>
#include "BMP.h"
#include <cmath>

void MidpointEllipse(BMP& bmpNew, float xradius, float yradius){
  float x = 0, y = yradius;
  float x_central = 500, y_central = 1;

    float d1 = pow(yradius,2) - (pow(xradius,2) * yradius) + (0.25 * pow(xradius,2));
    float xregion1 = 2 * pow(yradius,2) * x;
    float yregion1 = 2 * pow(xradius,2) * y;

     while(xregion1 < yregion1){
        bmpNew.set_pixel(x+x_central, y+y_central, 255, 100, 255, 0);
        bmpNew.set_pixel(-x+x_central, y+y_central, 255, 100, 255, 0);
        if (d1 < 0){
            xregion1 += (2 * pow(yradius,2));
            d1 += xregion1 + pow(yradius,2);
        }
        else{
            --y;
            xregion1 += (2 * pow(yradius,2));
            yregion1 -= (2 * pow(xradius,2));
            d1 += xregion1 - yregion1 + pow(yradius,2);
        }
       x++;
    }
    float d2 = (pow(yradius,2) * ((x + 0.5) * (x + 0.5))) +
          (pow(xradius,2) * ((y - 1) * (y - 1))) -(pow(xradius,2) * pow(yradius,2));
  
    while(y > 0){
        bmpNew.set_pixel(x+x_central, y+y_central, 255, 255, 255, 0);
        bmpNew.set_pixel(-x+x_central, y+y_central, 255, 255, 255, 0);
        if (d2 > 0){
            yregion1 -= (2 * pow(xradius,2));
            d2 += pow(xradius,2) - yregion1;
        }
        else {
            ++x;
            xregion1 +=  (2 * pow(yradius,2));
            yregion1 -= (2 * pow(xradius,2));
            d2 += xregion1 - yregion1 + pow(xradius,2);
        }
      y--;
    }
}

int main(){
  BMP bmpNew(1000, 1000, false);
  for(int i=0;i<1000;i++)
    {
        bmpNew.set_pixel(i, 1, 255, 255, 255, 0);
    }
  float xradius = 384, yradius = 768;
  
  MidpointEllipse(bmpNew, xradius, yradius);

  bmpNew.write("output.bmp");
  
  return 0;
}
