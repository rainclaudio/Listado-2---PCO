#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
/*
PROBLEM ID: 11935 "Trough the Desert"
Made by Claudio Rain
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
int limitFuel = 0;
int limitLeak = 0;

int process(std::string input){
  int FuelConsID = -1;
  std::stringstream ss;
  std::string number;
  if(input == "0 Fuel consumption 0") return -1;
  else {
    int pos = 0;
    while(input[pos] != ' '){
      number.push_back(input[pos]);
      pos++;
    }
    int kmID = -1;
    ss<<number;
    ss>>kmID;
    pos++;
    number.clear();
    if(input[pos] == 'F'){
      while(input[pos] != ' '){
        pos++;
      }
      pos++;
      while(pos<input.size()){
        number.push(input[pos]);
        pos++;
      }
      ss<<number;
      ss>>FuelConsID;
      FuelConsvector.push_back(std::make_pair(kmID,FuelConsID));
      incidenceQueue.push({kmID,FuelConsID},'f');

    } else if(input[pos] == 'L'){

      Leakvector.push_back(kmID);
      incidenceQueue.push({kmID,0},'l');

    } else if(input[pos] == 'G'){
      // Goal or Gas
      if(input[pos+1] == 'o'){
        Goal_ID = kmID;
        //gotGoal: true;
        return 0;
      } else {

        GasStationvector.push_back(kmID);
        incidenceQueue.push({kmID,0},'g');

      }
    } else if(input[pos] == 'M'){

      MechanicVector.push_back(kmID);
      incidenceQueue.push({kmID,0},'m');

    }
  }

  return 1;
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
  // setear aquí la fórmula para calcular el límite superior de answer 
}
bool Pprop(double x){
  double currentFuel = x;
  // asumimos que no hay más en un principio
  double Fuelconsumption = incidenceQueue.front().first.second / 100; // first fuel cons
  incidenceQueue.pop();
  int leakConsumption = 0;

  while (incidenceQueue.front().first.first != 0) {
    if(incidenceQueue.front().second == 'm')leakConsumption = 0;
    if(incidenceQueue.front().second == 'l')leakConsumption++;
    incidenceQueue.pop();
  }

  for(int i = 1; i <= Goal_ID; ++i){
    currentFuel = currentFuel - (Fuelconsumption + leakConsumption);
    if(incidenceQueue.front().first.first == i){
      while(incidenceQueue.front().first.first != i){
        // options incidenceQueue: fc - g - m - l
        if(incidenceQueue.front().second == 'm'){

          leakConsumption = 0;

        } else if(incidenceQueue.front().second == 'l'){

          leakConsumption++;

        } else if(incidenceQueue.front().second == 'f'){

          Fuelconsumption = incidenceQueue.front().first.second / 100;

        } else if(incidenceQueue.front().second == 'g'){

          currentFuel = x;

        }
        incidenceQueue.pop();
      }
    }
  }
  return currentFuel >= 0;
}
double get_answer(){
  double left = 0, right = Goal_ID;
  while(left < right - 1){
    double mid = (left + right)/2;
    if(Pprop(mid)) right = mid;
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
