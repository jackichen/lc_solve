#include <vector>
#include <iostream>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here


vector <int> findSignatureCounts(vector <int> arr) {
  // Write your code here
  size_t n = arr.size();
  vector<int> sign_count(n, 1), signature(n);
  for (size_t i=0; i<n; ++i) signature[i] = arr[i];
  vector<int> *ps = &signature, *pb = &arr, *tmp;
  bool new_sign = true;
  while (new_sign) {
    new_sign = false;
    for (size_t i=0; i<n; ++i) {
      int book = (*ps)[i];
      cout << book << ", ";
      if (book != i+1) {
        ++sign_count[i];
        new_sign = true;

        (*pb)[book] = book;
      }
    }
    cout << endl;
    tmp = ps;
    ps = pb;
    pb = tmp;
  }
  return sign_count;
}

// These are the tests we use to determine if the solution is correct.
// You can add your own at the bottom, but they are otherwise not editable!
void printIntegerVector(vector <int> array) {
  int size = array.size();
  cout << "[";
  for (int i = 0; i < size; i++) {
    if (i != 0) {
      cout << ", ";
    }
   cout << array[i];
  }
  cout << "]";
}

int test_case_number = 1;

void check(vector <int>& expected, vector <int>& output) {
  int expected_size = expected.size();
  int output_size = output.size();
  bool result = true;
  if (expected_size != output_size) {
    result = false;
  }
  for (int i = 0; i < min(expected_size, output_size); i++) {
    result &= (output[i] == expected[i]);
  }
  const char* rightTick = u8"\u2713";
  const char* wrongTick = u8"\u2717";
  if (result) {
    cout << rightTick << "Test #" << test_case_number << "\n";
  }
  else {
    cout << wrongTick << "Test #" << test_case_number << ": Expected ";
    printIntegerVector(expected);
    cout << " Your output: ";
    printIntegerVector(output);
    cout << endl;
  }
  test_case_number++;
}

int main() {
  int n_1 = 2;
  vector <int> arr_1{2, 1};
  vector <int> expected_1{2, 2};
  vector <int> output_1 = findSignatureCounts(arr_1);
  check(expected_1, output_1);

  int n_2 = 2;
  vector <int> arr_2{1, 2};
  vector <int> expected_2{1, 1};
  vector <int> output_2 = findSignatureCounts(arr_2);
  check(expected_2, output_2);

  // Add your own test cases here

}