#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
   int a, b, x, y, z, ja, ka, jb, kb;
   for (a = 0; a < 2; a++)
   {
      for (b = 0; b < 2; b++)
      {
         for (x = 0; x < 2; x++)
         {
            for (y = 0; y < 2; y++)
            {
               ja = (b & x) | ((!b) & (!y));
               ka = (!b) & x & (!y);
               jb = (!a) & x;
               kb = a | (x & (!y));
               z = (a & (!x) & (!y)) | (b & (!x) & (!y));
               int qa,qb;
               qa = (ja&(!a)) | ((!ka) & a);
               qb = (jb&(!b)) | ((!kb) & b);
               cout << "A为:"<< qa << " B为:"<< qb << " Z为:" << z <<endl; 
            }
         }
      }
   }
}