#include <vector>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
void swap(int &a, int &b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}

void reverse(vector<int>& values, vector<int>& hash, size_t start, size_t end)
{
    while (start < end) {
        hash[values[start]] = end;
        hash[values[end]] = start;
        swap(values[start], values[end]);
        ++start;
        --end;
    }
    cout << "After reverse: ";
    int N = values.size();
    for (int i=0; i<N; ++i)
        cout << '(' << hash[i] << ',' << values[i] << ") ";
    cout << endl;
}

int minOperations(const vector<int>& arr)
{
    int N = arr.size();
    if (N < 2) return 0;
    int count1 = 0;
    {
        vector<int> values(N, 0), hash(N, 0);
        for (int i=0; i <N; ++i) {
            values[i] = arr[i] - 1;
            hash[values[i]] = i;
        }
        cout << "Initial state: ";
        for (int i=0; i<N; ++i)
            cout << '(' << hash[i] << ',' << values[i] << ") ";
        cout << endl;
        for (int val=N-1; val>=0; --val) {
            if (hash[val] != val) {
                reverse(values, hash, hash[val], val);
                ++count1;
            }
        }
        cout << "count1: " << count1 << endl;
    }

    int count2 = 0;
    {
        vector<int> values(N, 0), hash(N, 0);
        for (int i=0; i <N; ++i) {
            values[i] = arr[i] - 1;
            hash[values[i]] = i;
        }
        cout << "Initial state: ";
        for (int i=0; i<N; ++i)
            cout << '(' << hash[i] << ',' << values[i] << ") ";
        cout << endl;
        for (int val=0; val<N; ++val) {
            if (hash[val] != val) {
                reverse(values, hash, val, hash[val]);
                ++count2;
            }
        }
        cout << "count2: " << count2 << endl;
    }
    return count1 < count2 ? count1 : count2;
}

int main()
{
    vector<int> vec1({1, 2, 5, 4, 3}), vec2({3, 1, 2}), vec3({1, 4, 5, 3, 2});
    minOperations(vec1);
    minOperations(vec2);
    minOperations(vec3);
    return 0;
}