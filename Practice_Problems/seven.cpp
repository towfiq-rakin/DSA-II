/*
Problem 7: Cybersecurity Encryption System
You're working as a systems engineer at a cybersecurity firm. The firm has a multi-layer 
encryption pipeline used to process highly confidential government data. The data passes 
through a series of n encryption modules. Each module transforms the data and can be 
represented as a matrix operation (due to underlying linear transformations in the 
encryption algorithms).
The matrices must be multiplied in a specific order to maintain data integrity and 
compliance, but the computational cost of these operations varies significantly depending 
on the multiplication sequence.
The goal is to securely optimize the system by determining the best order of operations 
that:
- Preserves the output (i.e., doesn't change the final matrix product),
- Minimizes the number of scalar multiplications (reducing computational load and 
  encryption latency).
If the wrong multiplication order is chosen, not only does the system slow down, but the 
encryption hardware could overheat and shut down, causing a security breach.
Input Format:
- Integer n — number of matrices (encryption modules)
- Array p[0..n] — where matrix Ai has dimensions p[i-1] x p[i]
(Hint: Use MCM to solve it)
Output Format:
- A single integer: minimum number of scalar multiplications
- A string showing the parenthesization of multiplication order
Example Input:
4
1 2 3 4 5
Example Output:
Minimum number of scalar multiplications: 30
Optimal parenthesization: ((M1 * M2) * (M3 * M4))
*/

#include <bits/stdc++.h>
using namespace std;

string getParentheses(vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        return "M" + to_string(i);
    } else {
        return "(" + getParentheses(s, i, s[i][j]) + " * " + getParentheses(s, s[i][j] + 1, j) + ")";
    }
}

int matrixChainMultiplication(vector<int>& p, string& parentheses) {
    int n = p.size() - 1;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));
    
    for (int length = 2; length <= n; length++) {
        for (int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;
            
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    
    parentheses = getParentheses(s, 1, n);
    return dp[1][n];
}

int main() {
    int n;
    cout << "Enter number of matrices: ";
    cin >> n;
    
    vector<int> p(n + 1);
    cout << "Enter dimensions array: ";
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }
    
    string parentheses;
    int minMultiplications = matrixChainMultiplication(p, parentheses);
    
    cout << "Minimum number of scalar multiplications: " << minMultiplications << endl;
    cout << "Optimal parenthesization: " << parentheses << endl;
    
    return 0;
}