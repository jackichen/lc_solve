class Solution {
public:
    vector<vector<string>> result;
    vector<bool> col_flag, flag_45, flag_135;
    vector<vector<string>> solveNQueens(int n) {
        col_flag.resize(n, true);
        flag_45.resize(2*n-1, true);
        flag_135.resize(2*n-1, true);
        string init(n, '.');
        vector<string> solution(n, init);
        backtrack(solution, 0);
        return result;
    }
    void backtrack(vector<string>& solution, int r) {
        int n = solution.size();
        if (r == n) {
            result.push_back(solution);
            return;
        }

        for (int c=0; c<n; ++c) {
            if (col_flag[c] && flag_45[r+c] && flag_135[r-c+n-1]) {
                col_flag[c] = false;
                flag_45[r + c] = false;
                flag_135[r-c+n-1] = false;
                solution[r][c] = 'Q';
                backtrack(solution, r+1);
                solution[r][c] = '.';
                col_flag[c] = true;
                flag_45[r + c] = true;
                flag_135[r-c+n-1] = true;
            }
        }
    }
};

class Solution1 {
public:
    vector<vector<string>> result;
    vector<vector<string>> solveNQueens(int n) {
        string init(n, '.');
        vector<string> solution(n, init);
        for (int i=0; i<n; ++i) {
          solution[0][i] = 'Q';
          backtrack(solution, 1);
          solution[0][i] = '.';
        }
        return result;
    }
    void backtrack(vector<string>& solution, int r) {
        int n = solution.size();
        if (r == n) {
            result.push_back(solution);
            return;
        }

        for (int i=0; i<n; ++i) {
            if (check(solution, r, i)) {
                solution[r][i] = 'Q';
                backtrack(solution, r+1);
                solution[r][i] = '.';
            }
        }
    }
    bool check(vector<string>& solution, int r, int index) {
        int n = solution.size();
        for (int x=0; x<r; ++x) {
            int delta = r - x;
            if ((solution[x][index] == 'Q') ||
                (index >= delta && solution[x][index - delta] == 'Q') ||
                (index + delta<n && solution[x][index + delta] == 'Q'))
                return false;
        }
        return true;
    }
};
