#include <iostream>
#include <utility>
#include <vector>
#include <math.h>
typedef std::pair<int,int> intpair;
typedef std::vector<int> Vector;
#define EPSILON 0.0000001
/*
PROBLEM ID: 11881 "Internal Rate of Return"
Solved by Claudio Rain
*/
double function(double IRR, Vector Fvalues){
  int power = 0;
  double answer = 0;
  for (size_t i = 0; i < Fvalues.size(); i++) {
    answer += (Fvalues[i] / (pow(IRR + 1,power)));
    power++;
  }
  return answer;
}
double solve(Vector Fvalues, double a, double b){
  double c;
  while( (b-a) > EPSILON){
    c = (a+b)/2;
    if(function(c,Fvalues) == 0.0){
      break;
    }
    else if(function(c,Fvalues) < 0)
      b = c;
    else
      a = c;
  }
  return c;
}
int main(int argc, char const *argv[]) {
  int T;
  while(std::cin >> T, T!=0){
    Vector Fvalues(T + 1);
    for (size_t i = 0; i < T + 1; i++) {
        int var;
        std::cin >> var;
        Fvalues.push_back(var);
    }
    double answer = solve(Fvalues,-1,10000);
    printf("%.2f\n",answer);
    Fvalues.clear();
  }
  return 0;
}
