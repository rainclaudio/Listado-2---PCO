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

intPairVector FuelConsvector;
Vector Leakvector;
int Goal_ID;
Vector GasStationvector;
Vector MechanicVector;
int process(std::string input){
  int kmID = -1;
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
        number.push_back(input[pos]);
        pos++;
      }
      ss<<number;
      ss>>FuelConsID;
      FuelConsvector.push_back(std::make_pair(kmID,FuelConsID));
    } else if(input[pos] == 'L'){
      Leakvector.push_back(kmID);
    } else if(input[pos] == 'G'){
      // Goal or Gas
      if(input[pos+1] == 'o'){
        Goal_ID = kmID;
        //gotGoal: true;
        return 0;
      } else {
        GasStationvector.push_back(kmID);
      }
    } else if(input[pos] == 'M'){
      MechanicVector.push_back(kmID);
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
}

double counter_Fuel_Leak_Consumption(int limitM, int limit2){//limi2 puede ser Goal_ID o Gasstation
  double answer = 0;
  int counterleak = 1;
  for(int i = 0; i < Leakvector.size(); ++i){
    if(Leakvector[i] < limit2){
      answer+= limit2 - Leakvector[i];
    }
  }
  return answer;
}
double counter_Fuel_Consumption(int limit){
  double answer = 0;
  for(int i = 0; i < FuelConsvector.size(); ++i){
    if(i+1 < FuelConsvector.size()){
      CounterFuel += (FuelConsvector[i].second * (FuelConsvector[i+1].first - FuelConsvector[i].first) )/ 100;
    } else {
      CounterFuel += (FuelConsvector[i].second * (limit - FuelConsvector[i].first) )/ 100;
    }
  }
  return answer;
}
double get_answer(){
  double answer = 0;
  int numGasStations = GasStationvector.size();
  int numMechanicStation = MechanicVector.size();
  double bestOption = 0;
  double currentOption = -1;

  if(numGasStations == 0){
    answer += counter_Fuel_Consumption(Goal_ID);
    answer += counter_Fuel_Leak_Consumption(Goal_ID);
  } else {

  }


  return answer;
}
int main(int argc, char const *argv[]) {

  bool endFunction = false;
  while(true){
    setup(endFunction);
    if(endFunction)break;
    double answer = get_answer();
    printf("%.3f\n",answer);
    FuelConsvector.clear();
    Leakvector.clear();
    GasStationvector.clear();
    MechanicVector.clear();
    Goal_ID = 0;
  }

  return 0;
}
