#include <iostream>
#include <vector>
/* Búsqueda binaria general:
Def: Dado un intervalo [a.b], y una propiedad P sobre el intervalo tal que:
 Ax,y E [a,b] entonces si x < y => P(y) -> P(x)
Ex:
Dado n cajas tq en cada caja entran c[i] elementos. Dados r elementos,
distribuir los r elementos tal que la cnatidad de elementos en la caja que más
tiene se a mínimo
*/
bool Pprop(int x, int r,std::vector<int> v){
  int cnt = 0;
  for (size_t i = 0; i < v.size(); i++) {
    cnt += std::min(x,v[i]);
  }
  return cnt >= r;
}
int get_answer(std::vector<int> vr, int r){
  int left = 0, right = r;
  while(left < right - 1){
    int mid = (left + right) /2;
    if(Pprop(mid,r,vr)) right = mid;
    else left = mid;
  }
  return right;
}
int main(int argc, char const *argv[]) {
  int r,cCages;
  std::vector<int> vr;
  std::cin >> r;
  std::cin >> cCages;
  for(int i = 0; i < cCages; ++i){
    int var;
    std::cin >> var;
    vr.push_back(var);
  }
  int answer = get_answer(vr,r);
  std::cout << answer << '\n';
  return 0;
}
