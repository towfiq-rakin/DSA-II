#include <bits/stdc++.h>
using namespace std;

int knapsack(int W, vector<int> &wt, vector<int> &val) {
    int n = wt.size();
    vector<int> f(W + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = W; j >= wt[i]; j--)
            f[j] = max(f[j], f[j - wt[i]] + val[i]);
    
    for(int i: f) cout << i << " "; // Debugging line to print the DP array
    return f.back(); // Return the maximum value
}

int main() {
    int n, W; // Number of items and maximum weight
    cin >> n >> W;
    vector<int> wt(n + 1), val(n + 1);
    for (int i = 1; i <= n; i++) 
        cin >> wt[i] >> val[i]; // Weight & value input
    
    cout << endl << knapsack(W, wt, val) << endl;
    return 0;
}