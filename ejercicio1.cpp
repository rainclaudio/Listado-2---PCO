#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#define EPSILON 0.0000001
/*
Problem ID: 10341 Solve It
Made by Claudio Rain
*/
int p,q,r,s,t,u;
std::ifstream lector;
std::ofstream escritor;
double func(double x){
  return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
  //return value;
}
double bisection(double a , double b){
  double c;
  while( (b-a) > EPSILON){
    c = (a+b)/2;
    if(func(c) == 0.0){
      break;
    }
    else if(func(c) < 0)
      b = c;
    else
      a = c;
  }
  return c;
}
int main(int argc, char const *argv[]){
  double a = 0;
  double b = 1;
//  escritor.open(argv[1]);
  while (scanf("%d %d %d %d %d %d",&p,&q,&r,&s,&t,&u) != EOF) {
  //  std::cin >> p>>q>>r>>s>>t>>u;
    if (func(0)*func(1) > 0){
      std::cout << "No solution" << '\n';
    } else{
      double answer = bisection(a,b);
      printf("%.4f\n",answer);
      //escritor<< ("%.4f,answer") <<std::endl;
    //  escritor << "No solution"<<std::endl;
    }
  }
  escritor.close();
  return 0;
}
