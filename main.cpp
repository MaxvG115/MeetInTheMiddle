//MVG(^w^)
//Este programa utiliza el algoritmo de meet in the middle para regresar el minimo posible valor de (abs(sum - goal))
/*
paso 1: dividimos el arreglo en 2 partes iguales
paso 2: obtenemos la suma de todos los subconjuntos de los arrelgos divididos en 2 por separado. Esto los almacenamos en 2 sub arreglos
paso 3: ordenamos el subarreglo 2 para realizar una busqueda binaria
paso 4: Asignamos objetivos nuevos por cada elemento del subarreglo 1(target = goal-sub1[i]) Esto hasta eliminar una suma en la primera mitad
paso 5: por cada nuevo objetivo, encontramos la suma más cercana en sub2 usando la búsqueda binaria y la diferencia con ella (sub2[mid]) para obtener min_diff
paso 6: realizamos una busqueda binaria para encontrar el minimo
*/

#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

//funcion para encontrar las sumas
vector<int> findSums(vector<int>& arr){
  int n = arr.size(),c = 0,sum;
  vector<int> res((1<<n),0); 
  
  for(int i = 0 ;i < (1<< n); i++){
    sum = 0;
    
    for(int j = 0; j < n ; j++){
      
      if(i & (1 << j)){
        sum += arr[j]; 
       }
    }
    res[c++] = sum;
  }
  
  return res;
}

// funcion para calcular diferencia
int minAbsDifference(vector<int>& nums, int goal){
  int n = nums.size();
  vector<int> nums1, nums2;
  
  for(int i = 0; i < n/2; i++){
    nums1.push_back(nums[i]);
  }
  for(int i = n/2; i < n ; i++){
    nums2.push_back(nums[i]);
  }
  
  vector<int> sub1 = findSums(nums1), sub2 = findSums(nums2);
  
  sort(sub2.begin(),sub2.end());
  int min_diff = INT_MAX;
  
  for(int i = 0; i < sub1.size() ; i++){
    int target = goal-sub1[i];
    int low = 0, high = sub2.size()-1;
    
    while(low <= high){
      int mid = low + (high-low)/2;
      min_diff = min(min_diff, abs(target-sub2[mid]));
      
      if(sub2[mid] == target){
       break; 
      }
      else if(target < sub2[mid]){
       high = mid-1;
      }
      else{
       low = mid+1; 
      }
    }
  }
  return min_diff;
}

// El programa recibe 3 inputs
//1. el numero de enteros que contendra el arreglo por analizar
//2. los enteros que contiene el arreglo
//3. la meta
int main(){
  int n, goal;
  vector<int> nums;
  cin >> n >>  goal;
  
  for(int i = 0; i < n ; i++){
   int x;
    cin >> x;
    nums.push_back(x);
  }
  
  cout << minAbsDifference(nums,goal) << "\n";
  return 0; 
}

/*
Ejemplo de Input:
Input:
4
7
-9
15
-2 
-5
Output: 
1

Explicación: Elije la subsecuencia [7,-9,-2], con una suma de -4.
La diferencia absoluta es abs(-4 - (-5)) = abs(1) = 1, que es la mínima.
*/