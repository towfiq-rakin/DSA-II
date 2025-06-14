#include <bits/stdc++.h>
using namespace std;

void knapsack(int W, vector<int> &wt, vector<int> &val){
    int n = wt.size()-1;
    vector<int> dp(W + 1, 0);
    vector<int> keep[W+1];
    for (int i = 1; i <= n; i++) {
        for (int j = W; j >= wt[i]; j--) {
            if (dp[j - wt[i]] + val[i] > dp[j]) {
                dp[j] = dp[j - wt[i]] + val[i];
                keep[j] = keep[j - wt[i]];
                keep[j].push_back(i);      
            }
        }
    }
    cout << endl << "Maximum value: " << dp.back() << endl;
    cout << "Items included: ";
    for (int i : keep[W]) cout << i << " ";
}

int main() {
    int n, W; 
    cin >> n >> W; // Number of items and maximum weight
    vector<int> wt(n + 1), val(n + 1);
    for (int i = 1; i <= n; i++) 
        cin >> wt[i] >> val[i];
    
    knapsack(W, wt, val);
    return 0;
}

/*
4 5
2 10
1 12
3 20
2 15
*/

/*
4 12
3 4
4 6
8 3
7 9
*/