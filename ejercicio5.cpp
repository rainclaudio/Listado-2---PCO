#include <iostream>
#include <stdio.h>
#include <algorithm>
/*
Problem ID: 11462 "Age Sort"
Solved by Claudio Rain
*/
using namespace std;
// faster: 0.280, delete i en for
// cambia cout por print
int main(int argc, char const *argv[]) {
  int v[2000000],n,i;
  scanf("%d",&n);
  while(n!= 0){

    for(i=0;i<n;i++)scanf("%d",&v[i]);

    sort(v,v + n);
    // for(i=0;i<n-1;i++)std::cout << v[i] << ' ';
    for(i=0;i<n-1;i++)printf("%d ",v[i]);
    printf("%d\n",v[n-1]);
    // std::cout << v[n-1] << '\n';
    scanf("%d",&n);

  }
  return 0;
}
/* TIEMPO: 0.330
int main(int argc, char const *argv[]) {
  int v[2000000],n;
  while(scanf("%d",&n), n!= 0){

    for(int i = 0 ; i < n ; i++)scanf("%d",&v[i]);

    sort(v,v + n);

    for(int i = 0; i<n - 1;i++)printf("%d ",v[i]);

    printf("%d\n",v[n-1]);

  }
  return 0;
}
*/
