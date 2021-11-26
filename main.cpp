#include<bits/stdc++.h>

using namespace std;

int n;
vector<int> permutation;
vector<bool> chosen;
vector<int> sol;
vector<vector<int>> solutions;
int res = 0;


bool isCollinear(int n, int a, int b, int c){
    if(a/n == b/n) return a/n == c/n;
    else if(a%n == b%n) return a%n == c%n;
    else return (a/n - b/n)*(c%n - b%n) == (c/n - b/n)*(a%n - b%n);
}

bool isParallel(int n, int a1, int a2, int b1, int b2){
    if(a1/n == a2/n && b1/n == b2/n) return true;
    else if (a1%n == a2%n && b1%n == b2%n) return true;
    else return (a2/n - a1/n)*(b2%n - b1%n) == (b2/n - b1/n)*(a2%n - a1%n);
}

bool isIntersect(int n, int a1, int a2, int b1, int b2){
    if(isParallel(n,a1,a2,b1,b2)) return isCollinear(n,a1,b1,b2);
    else{
        int a1x = a1%n;
        int a2x = a2%n;
        int b1x = b1%n;
        int b2x = b2%n;
        int a1y = a1/n;
        int a2y = a2/n;
        int b1y = b1/n;
        int b2y = b2/n;
        bool bSide = ((a1y-b1y)*(b2x-b1x) - (a1x-b1x)*(b2y-b1y))*((a2y-b1y)*(b2x-b1x) - (a2x-b1x)*(b2y-b1y))<=0;
        bool aSide = ((b1y-a1y)*(a2x-a1x) - (b1x-a1x)*(a2y-a1y))*((b2y-a1y)*(a2x-a1x) - (b2x-a1x)*(a2y-a1y))<=0;
        return aSide && bSide;
    }
}

void permuteGenerator(){
    if (permutation.size() == n*n){
        for(int i=0; i<n*n; i++){
            cout << permutation.at(i) << " ";
        }
        cout << "=====>";
        
        int intersection = 0;
        for(unsigned int i=0; i<permutation.size()-1; i++){
            for(unsigned int j=0; j<permutation.size()-1; j++){
                if(isIntersect(n,permutation.at(i),permutation.at(i+1),permutation.at(j),permutation.at(j+1))) intersection++;
            }
        }
        cout << intersection << "\n";
        if(intersection > res){
            solutions.clear();
        }
        if(intersection >= res){
            
            for(int i=0; i<n*n; i++){
                sol[i] = permutation.at(i);
            }
            solutions.push_back(sol);
            res = intersection;
        }
    }else{
        for(int i=0; i<n*n; i++){
            if(chosen[i]) continue;
            else if (permutation.size()>0){
                bool isThereCollinear = false;
                for(int j=0; j < n*n; j++){
                    if(!chosen[j]){
                        if(isCollinear(n,j,i,permutation.at(permutation.size()-1))){
                            isThereCollinear = true;
                            break;
                        }
                    }
                }
                if(isThereCollinear) continue;
            }
            chosen[i] = true;
            permutation.push_back(i);
            permuteGenerator();
            chosen[i] = false;
            permutation.pop_back();
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=0; i<n*n; i++){
        chosen.push_back(false);
        sol.push_back(0);
    }

    permuteGenerator();
    cout << "jawabnya " << res;
    cout << "\npermutasinya gini ngab \n";
    for(unsigned int i=0; i<solutions.size(); i++){
        for(int j=0; j<n*n; j++){
            cout << solutions.at(i).at(j) << " ";
        }
        cout << "\n";
    }
    return 0;
}