#include <iostream>
// Add any extra import statements you may need here
#include <vector>
#include <set>
using namespace std;

class Node {
public:
  int val;
  vector<Node*> children;

  Node() {
    val = 0;
    children = vector<Node*>();
  }

  Node(int _val) {
    val = _val;
    children = vector<Node*>();
  }

  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

struct Query {
  int v;
  char c;
};

// Add any helper functions you may need here
using IndexPath=vector<int>;
using CharPath=vector<char>;

/*int query(const vector<IndexPath>& ipaths, const string& str, const Query& query)
{
  set<int> nodes_index;
  int path_count = ipaths.size();
  for (int path_index=0; path_index<path_count; ++path_index) {
    cout << "Path " << path_index << ": ";
    int path_len = ipaths[path_index].size(), subtree_index;
    bool check_char = false;
    for (subtree_index=0; subtree_index<path_len; ++subtree_index) {
      cout << '(' << ipaths[path_index][subtree_index] << ", " << str[ipaths[path_index][subtree_index]-1] << ") ";
      if (!check_char && ipaths[path_index][subtree_index] == query.v)
        check_char = true;
      if (check_char && str[ipaths[path_index][subtree_index]-1] == query.c)
        nodes_index.insert(ipaths[path_index][subtree_index]);
    }
    cout << endl;
  }
  cout << query.v << ' ' << query.c;
  for (auto& index : nodes_index)
    cout << ' ' << index;
  cout << endl;
  return nodes_index.size();
}*/

void getPaths(Node* root, vector<IndexPath>& ipaths, IndexPath& ipath, const string& str)
{
  if (root->children.empty()) {
    ipaths.push_back(ipath);
  } else {
    for (auto& node : root->children) {
      ipath.push_back(node->val);
      getPaths(node, ipaths, ipath, str);
      ipath.pop_back();
    }
  }
}

vector<int> countOfNodes(Node* root, vector<Query> queries, string s) {
  // Write your code here
  size_t n_query = queries.size();
  vector<int> result(n_query, 0);
  if (root) {
    vector<IndexPath> ipaths;
    IndexPath ipath;
    ipath.push_back(root->val);
    getPaths(root, ipaths, ipath, s);
    //for (int i=0; i<n_query; ++i)
    //  result[i] = query(ipaths, s, queries[i]);
    int path_count = ipaths.size();
    vector<set<int>> nodes_index(n_query);
    vector<bool> check_char(n_query, false);
    for (int path_index=0; path_index<path_count; ++path_index) {
      int path_len = ipaths[path_index].size(), subtree_index;
      //cout << "Path " << path_index << ": ";
      for (subtree_index=0; subtree_index<path_len; ++subtree_index) {
        //cout << '(' << ipaths[path_index][subtree_index] << ", " << s[ipaths[path_index][subtree_index]-1] << ") ";
        for (size_t i=0; i<n_query; ++i) {
          if (!check_char[i] && ipaths[path_index][subtree_index] == queries[i].v)
            check_char[i] = true;
          if (check_char[i] && s[ipaths[path_index][subtree_index]-1] == queries[i].c)
            nodes_index[i].insert(ipaths[path_index][subtree_index]);
        }
      }
      // cout << endl;
      for (size_t i=0; i<n_query; ++i)
        check_char[i] = false;
    }
    for (size_t i=0; i<n_query; ++i) {
      /*cout << queries[i].v << ' ' << queries[i].c << ':';
      for (auto& index : nodes_index[i])
        cout << ' ' << index;
      cout << endl;*/
      result[i] = nodes_index[i].size();
    }
  }
  return result;
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

  // Testcase 1
  int n_1 = 3, q_1 = 1;
  string s_1 = "aba";
  Node *root_1 = new Node(1);
  root_1->children.push_back(new Node(2));
  root_1->children.push_back(new Node(3));
  vector<Query> queries_1{{1,'a'}};
  vector<int> output_1 = countOfNodes(root_1, queries_1, s_1);
  vector<int> expected_1 = {2};
  check(expected_1, output_1);

  // Testcase 2
  int n_2 = 7, q_2 = 3;
  string s_2 = "abaacab";
  Node *root_2 = new Node(1);
  root_2->children.push_back(new Node(2));
  root_2->children.push_back(new Node(3));
  root_2->children.push_back(new Node(7));
  root_2->children[0]->children.push_back(new Node(4));
  root_2->children[0]->children.push_back(new Node(5));
  root_2->children[1]->children.push_back(new Node(6));
  vector<Query> queries_2{{1,'a'}, {2, 'b'}, {3, 'a'}};
  vector<int> output_2 = countOfNodes(root_2, queries_2, s_2);
  vector<int> expected_2 = {4, 1, 2};
  check(expected_2, output_2);

  // Add your own test cases here

}