#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <queue>
#define EPSILON 0.0000001

/*
PROBLEM ID: 11935 "Trough the Desert"
Made by Claudio Rain
Se podría haber resuelto de manera mucho más fácil, pero me di cuenta de eso
cuando ya había terminado la manera difícil.
*/
typedef std::pair<int,int> intPair;
typedef std::vector<intPair> intPairVector;
typedef std::vector<int> Vector;
typedef std::queue<std::pair<intPair,char>> UtilQueue;
intPairVector FuelConsvector;
Vector Leakvector;
int Goal_ID;
Vector GasStationvector;
Vector MechanicVector;
UtilQueue incidenceQueue;
double limitFuel = 0;
double limitLeak = 0;

int process(std::string input){
  int FuelConsID = -1;
  std::stringstream ss1;
  std::stringstream ss2;
  std::string number;
  if(input == "0 Fuel consumption 0") return -1;
  else {
    int pos = 0;
    while(input[pos] != ' '){
      number.push_back(input[pos]);
      pos++;
    }
    int kmID = -1;
    ss1<<number;
    ss1>>kmID;
    pos++;
    number.clear();
    if(input[pos] == 'F'){
      // para "Fuel"
      while(input[pos] != ' '){
        pos++;
      }
      pos++;
      // para "consumption"
      while(input[pos] != ' '){
        pos++;
      }
      pos++;

      while(pos<input.size()){
        number.push_back(input[pos]);
        pos++;
      }
      //std::cout << "NUMBER PROCESS: "<<number << '\n';
      ss2<<number;
      ss2>>FuelConsID;
      //std::cout << "FUEL CONSID: "<<FuelConsID << '\n';
      FuelConsvector.push_back(std::make_pair(kmID,FuelConsID));
      incidenceQueue.push({{kmID,FuelConsID},'f'});

    } else if(input[pos] == 'L'){

      Leakvector.push_back(kmID);
      incidenceQueue.push({{kmID,0},'l'});

    } else if(input[pos] == 'G'){
      // Goal or Gas
      if(input[pos+1] == 'o'){
        Goal_ID = kmID;
        //gotGoal: true;
        return 0;
      } else {

        GasStationvector.push_back(kmID);
        incidenceQueue.push({{kmID,0},'g'});

      }
    } else if(input[pos] == 'M'){

      MechanicVector.push_back(kmID);
      incidenceQueue.push({{kmID,0},'m'});

    }
  }

  return 1;
}
void printIncidenceQueue(UtilQueue q){
  std::cout << "\tkm: " << '\t'<< "fuel"<<'\t' << "Even" << '\n';
  while(!q.empty()){
    std::cout<<'\t' << q.front().first.first<<'\t' << q.front().first.second<<'\t' << q.front().second<<'\n';
    q.pop();
  }
}
void setup(bool& endFunction){
  bool gotGoal = false;
  std::string input;
    while(!gotGoal){
      getline(std::cin,input);
      switch (process(input)){
        case -1:
          endFunction = true;
          break;
        case 0:
          gotGoal = true;
          break;
        default:
          break;
      }
    if(gotGoal)break;
    if(endFunction)break;
  }
  limitFuel = (30 * (double)Goal_ID);
  for(auto it: Leakvector){
    limitLeak = limitLeak + (Goal_ID - it);
  }

}
bool Pprop(double x,UtilQueue q){
  double currentFuel = x;

  double Fuelconsumption = (double)q.front().first.second / 100; // first fuel cons
  q.pop();
  int leakConsumption = 0;
  if(!q.empty()){
    while (q.front().first.first == 0) {
      if(q.front().second == 'm')leakConsumption = 0;
      if(q.front().second == 'l')leakConsumption++;
      if(q.front().second == 'f')Fuelconsumption = (double)q.front().first.second / 100;

      q.pop();
    }
  }

  for(int i = 1; i <= Goal_ID; ++i){
    currentFuel = currentFuel - (Fuelconsumption + (double)leakConsumption);
    if(currentFuel < 0)break;
    if(!q.empty()){
        if(q.front().first.first == i){
          while(q.front().first.first == i){
            if(q.front().second == 'm'){

              leakConsumption = 0;

            } else if(q.front().second == 'l'){

              leakConsumption++;

            } else if(q.front().second == 'f'){

              Fuelconsumption = (double)q.front().first.second / 100;
            } else if(q.front().second == 'g'){

              currentFuel = x;

            }
            q.pop();
          }
      }
    }
  }
  return currentFuel >= 0;
}
double get_answer(){
  double left = 0, right = limitFuel + limitLeak;
  while(left < right - EPSILON){
    double mid = (left + right)/2;
    if(Pprop(mid,incidenceQueue)) right = mid;
    else left = mid;
  }
  return right;
}

int main(int argc, char const *argv[]) {

  bool endFunction = false;
  while(true){
    setup(endFunction);
    if(endFunction)break;
    double answer = get_answer();
    printf("%.3f\n",answer);

    while(!incidenceQueue.empty())incidenceQueue.pop();
    limitLeak = 0;
    limitFuel = 0;


    FuelConsvector.clear();
    Leakvector.clear();
    GasStationvector.clear();
    MechanicVector.clear();
    Goal_ID = 0;

  }

  return 0;
}
