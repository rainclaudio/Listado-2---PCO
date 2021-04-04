#include <iostream>
#include <vector>
#include <queue>
/*
Problem ID: 11413 "Fill the containers"
Solved by Claudio Rain
*/
typedef std::vector<int> Vector;
bool Pprop(int x, int totalCap,std::queue<int> conveyor,int mContainers){
  bool isPossible = true;
  int cup = 0;
  int counterContainters = 1;
  int totalMilk = 0;
  char tab = '\t';
  while(!conveyor.empty()){
    int var = conveyor.front();
    if(cup + var <= x){
      cup+=var;
      totalMilk+=var;
    } else {
      cup = 0;
      if(var > x){
        isPossible = false;
        break;
      }
      cup+=var;
      totalMilk+=var;
      counterContainters++;
      if(counterContainters > mContainers){
        isPossible = false;
        break;
      }
    }
    conveyor.pop();
  }
  return isPossible;
}

int get_answer(std::queue<int> conveyor, int totalCap, int nVessels, int mContainers){
  int answer = 0;
  int left = 0, right = totalCap;
  while (left < right - 1){
    int mid = (left + right)/2;
    if(Pprop(mid,totalCap,conveyor,mContainers)) right = mid;
    else left = mid;
  }

  return right;
}
int main(int argc, char const *argv[]) {
  int nVessels, mContainers;
  while(scanf("%d %d",&nVessels,&mContainers)!= EOF){
    std::queue<int> conveyor;
    int cap;
    int totalCap = 0;
    for (size_t i = 0; i < nVessels; i++) {
      std::cin >> cap;
      totalCap+= cap;
      conveyor.push(cap);
    }
    int answer = get_answer(conveyor,totalCap,nVessels,mContainers);
    std::cout << answer << '\n';
    while(!conveyor.empty()){
      conveyor.pop();
    }
  }
  return 0;
}
