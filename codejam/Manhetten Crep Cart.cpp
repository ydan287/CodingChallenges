#include <iostream>

using namespace std;

std::pair<int,int> maxSumPair(int arr1[], int n1, int arr2[], int n2)
{
    int max1 = 0;
    int max2 = 0;
    int bestI=0,bestJ=0;
    int i =0;
    while(i < n1){
        if (arr1[i] > max1) {
            max1 = arr1[i];
            bestI = i;
        }
        ++i;
    }
    int j =0;
    while(j<n2){
        if (arr2[j] > max2){
            max2 = arr2[j];
            bestJ = j;
        }
        ++j;
        
    }
    
    return std::make_pair(bestI,bestJ);
}


int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int P,Q;
        int X,Y;
        char D;
        cin>>P;
        cin>>Q;
        Q=Q+1;
        int arrayX[Q];
        int arrayY[Q];
        for(int k=0;k<Q;k++){
            arrayX[k]=0;
            arrayY[k]=0;
        }
        for(int i = 0; i< P; i++){
            cin>>X;
            cin>>Y;
            cin>>D;
            if(D == 'N'){
                for(int j=Y+1;j<Q;j++){
                    arrayY[j]++;
                }
            }
            if(D == 'S'){
                for(int j=0;j<Y;j++){
                    arrayY[j]++;
                }
            }
            if(D == 'E'){
                for(int j=X+1;j<Q;j++){
                    arrayX[j]++;
                }

            }
            if(D == 'W'){
                for(int j=0;j<X;j++){
                    arrayX[j]++;
                }
            }
        }
