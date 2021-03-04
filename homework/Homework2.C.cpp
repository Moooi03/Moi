#include<stdio.h>                        ///Raúl Chavez explain me how to do the homework//
#include<math.h>
#define K 13                             ///https://www.youtube.com/watch?v=RFVJHeDL9LA&t=611s (BASED ON THIS VIDEO TO GET THE IDEA OF K PRIME NUMBERS DECIMALS)///

void prime(int n);                        
void binary(int d);                      ///TRANSFORM ALL THE FIRST K NUMBERS INTO BINARY///
int main() {

  prime(K); 
  return 0;
}
void binary(int t)
{
    int i=0; 
    int base[10]={0};
    while(t>0)
    {
    base[i]= t%2;
	t/=2; 
	++i; 
    }
   
    for(int x=9;x>=0;--x)   
    {
       printf("%01d",base[x]);
    }
     printf("\n");
}
void prime(int k)
{
  int count, i, flag, sr;
  int n=1;
  count = 1;
  while(count <= k){
    sr = sqrt(n);
    flag = 0; 
    for(i=2; i<= sr; i++){
      if(n%i==0){
        flag = 1; 
        break;
      }
    }
    if(flag==0){ 
      binary(n); 
      count++; 
    }
    n++; 
  }
}
