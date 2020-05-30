class Solution {
public:
    // dp(i) means count of trees which use i as root with [1, i-1] in left subtree and [i+1, n] in right subtree
    // f(n) = sum(dp[1], dp[2], ..., dp[n])
    // dp(i) = dp(i-1) * dp(n-i)
    int numTrees(int n) {
        if (n <= 1) return 1;
        if (n == 2) return 2;
        vector<int> dp(n+1);
        dp[0] = dp[1] = 1;
        dp[2] = 2;
        for (int i=3; i<=n; ++i) {
            //for (int p=1; p<=i; ++p)
            //    dp[i] += dp[p-1] * dp[i-p];
            int h_i = (i-1)>>1;
            for (int left=0; left<=h_i; ++left) {
                int right = i-1-left;
                int delta = dp[left]*dp[right];
                dp[i] += delta;
                if (left != right)
                    dp[i] += delta;
            }
        }
        return dp[n];
    }
};
