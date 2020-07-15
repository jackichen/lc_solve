#include <vector>
using std::vector;

class Solution {
public:
    int compare(const vector<int>& lhs, const vector<int>& rhs) {
        if (lhs.empty() && rhs.empty()) return 0;
        if (lhs.empty()) return -1;
        if (rhs.empty()) return 1;

        // [a, b] vs. [c, d]
        // a == c
        if (lhs[0] == rhs[0]) {
            // b == d
            if (lhs[1] == rhs[1]) return 0; // lhs == rhs
            // b < d
            else if (lhs[1] < rhs[1]) return 2; // rhs contains lhs [c, d]
            // b > d
            else return -2; // lhs contains rhs [a, b]
        // a < c
        } else if (lhs[0] < rhs[0]) {
            // a < =b < c <= d
            if (lhs[1] < rhs[0]) return -1; // lhs < rhs
            // a <= b == c <= d
            else if (lhs[1] == rhs[0]) return -3; // lhs + rhs, [a, d]
            // a < c < b <= d
            else if (lhs[1] <= rhs[1]) return -3; // lhs + rhs, [a, d]
            // a < c <= d < b
            else return -2; // lhs contains rhs
        // a > c
        } else {
            // c <= d < a <= b
            if (rhs[1] < lhs[0]) return 1; // lhs > rhs
            // c <= d == a <= b || c < a < d <= b
            else if (rhs[1] <= lhs[1] || rhs[1] == lhs[0]) return 3; // rhs + lhs, [c, b]
            // c < a <= b < d
            else /*if (rhs[1] > lhs[1])*/ return 2; // rhs contains lhs [c, d]
        }
    }
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        if (intervals.empty()) {
            result.push_back(newInterval);
        } else {
            size_t count = intervals.size(), i = 0;
            while (i < count) {
                switch(compare(intervals[i], newInterval)) {
                case -3:
                    newInterval[0] = intervals[i++][0];
                    break;
                case 3:
                    newInterval[1] = intervals[i++][1];
                    break;
                case -2:
                case 0:
                    return intervals;
                case -1:
                    result.push_back(intervals[i++]);
                    break;
                case 1:
                    result.push_back(newInterval);
                    while (i < count) {
                        result.push_back(intervals[i++]);
                    }
                    return result;
                case 2:
                    ++i;
                    break;
                }
            }
            result.push_back(newInterval);
        }
        return result;
    }

    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        if (intervals.empty()) {
            result.push_back(newInterval);
        } else {
            size_t i=0, count = intervals.size();
            // [a, b] vs. [c, d]

            // b < c
            while (i<count && intervals[i][1] < newInterval[0]) {
                // smaller interval
                result.push_back(intervals[i]);
                ++i;
            }

            // b <= d
            while (i < count && intervals[i][1] <= newInterval[1]) {
                // new = left + right
                // newInterval[1] = intervals[i][0];
                // a < c
                if (intervals[i][0] < newInterval[0])
                    newInterval[0] = intervals[i][0];
                // c <= a, just skip current interval
                ++i;
            }

            // a <= d < b
            while (i < count && intervals[i][0] <= newInterval[1]) {
                newInterval[1] = intervals[i][1];
                // a < c
                if (intervals[i][0] < newInterval[0])
                    newInterval[0] = intervals[i][0];
                // c <= a, just skip current interval
                ++i;
            }
            result.push_back(newInterval);
            // c <= d < a <= b
            while (i<count) {
                result.push_back(intervals[i]);
                ++i;
            }
        }
        return result;
    }
};
