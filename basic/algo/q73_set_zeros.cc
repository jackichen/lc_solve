// O(mn) for time compexity
// While this solution cost take more time and consume more memory than solution1 when commited to leetcode
// O(1) for space complexity
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (!matrix.empty() && !matrix[0].empty()) {
            size_t rows = matrix.size(), cols=matrix[0].size();
            bool flag_row0 = false;
            for (size_t c=0; c<cols; ++c)
                if (!matrix[0][c]) {
                    flag_row0 = true;
                    break;
                }

            for (size_t r=1; r<rows; ++r)
                for (size_t c=0; c<cols; ++c)
                    if (!matrix[r][c])
                        // column c and row r should be set as zero
                        matrix[0][c] = matrix[r][0] = 0;

            for (size_t r=1; r<rows; ++r)
                for (size_t c=1; c<cols; ++c)
                    if (!matrix[r][0] || !matrix[0][c])
                        matrix[r][c] = 0;

            if (!matrix[0][0])
                // first column should be set as zero
                for (size_t r=1; r<rows; ++r)
                    matrix[r][0] = 0;

            if (flag_row0)
                // first row should be set as zero
                for (size_t c=0; c<cols; ++c)
                    matrix[0][c] = 0;
        }
    }
};

// O(m+n) for space complexity
class Solution1 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (!matrix.empty() && !matrix[0].empty()) {
            size_t rows = matrix.size(), cols=matrix[0].size();
            std::unordered_set<size_t> zero_rows, zero_cols;
            for (size_t r=0; r<rows; ++r)
                for (size_t c=0; c<cols; ++c)
                    if (!matrix[r][c]) {
                        zero_rows.insert(r);
                        zero_cols.insert(c);
                    }

            for (auto& r : zero_rows)
                for (size_t c=0; c<cols; ++c)
                    matrix[r][c] = 0;
            for (auto& c : zero_cols)
                for (size_t r=0; r<rows; ++r)
                    matrix[r][c] = 0;
        }
    }
};
