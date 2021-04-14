#include <iostream>
#include <vector>
/*
Problem ID: 11858 "Frosh week"
Solved by Claudio Rain
Merge sort sacado de geeksforgeeks :D y tuneado para vector
*/
typedef std::vector<int> Vector;
Vector v;
long long counterSwaps = 0;

void merge(Vector& v,  int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;

    // int L[n1], R[n2];
    Vector L,R;
    for (int i = 0; i < n1; i++)
        L.push_back(v[l + i]);
    for (int j = 0; j < n2; j++)
        R.push_back(v[m + 1 + j]);

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
      }
        else {
            v[k] = R[j];
             counterSwaps+= n1 - i;
            j++;
        }
        k++;
    }
    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(Vector&v, int l,int r){
    if(l>=r){
        return;
    }
    int m = (l+r-1)/2;
    mergeSort(v,l,m);
    mergeSort(v,m+1,r);
    merge(v,l,m,r);
}
void printVector(Vector vec){
  for(auto it: vec){
    std::cout << it << ' ';
  }
  std::cout  << '\n';
}
int main(int argc, char const *argv[]) {
  int n;
  int var;
  while(scanf("%d",&n) != EOF){
    for(int i=0;i<n;i++){
         scanf("%d",&var);
         v.push_back(var);
    }
    mergeSort(v, 0, n-1);
    printf("%lld\n",counterSwaps);
    counterSwaps = 0;
    v.clear();
  }

  return 0;
}
