/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* copyTree(TreeNode* root, int delta)
    {
        if (!root) return nullptr;

        TreeNode* new_root = new TreeNode(root->val + delta);
        new_root->left = copyTree(root->left, delta);
        new_root->right = copyTree(root->right, delta);
        return new_root;
    }

    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> result;
        if (n == 0)
            return result;

        vector<vector<TreeNode*>> trees;
        trees.push_back({nullptr});
        trees.push_back({new TreeNode(1)});

        for (int i=2; i<=n; ++i) {
            vector<TreeNode*> roots;
            for (int root_val=1; root_val<=i; ++root_val) {
                int left_count = root_val - 1, right_count = i - root_val;
                for (auto left : trees[left_count]) {
                    for (auto right : trees[right_count]) {
                        TreeNode* root = new TreeNode(root_val);
                        root->left = left; // copyTree(left, 0); we can share the left subtree in memory
                        root->right = copyTree(right, root_val);
                        roots.push_back(root);
                    }
                }
            }
            trees.push_back(roots);
        }
        return trees[n];
    }
};

class Solution1 {
public:
    void generateTreesHelper(int min, int max, vector<TreeNode*> &output)
    {
        if (min > max) {
            output.push_back(nullptr);
        } else if (min == max) {
            output.push_back(new TreeNode(min));
        } else if (min < max) {
            for (int root_val=min; root_val<=max; ++root_val) {
                vector<TreeNode*> left_subtrees, right_subtrees;
                generateTreesHelper(min, root_val-1, left_subtrees);
                generateTreesHelper(root_val+1, max, right_subtrees);
                for (auto left : left_subtrees) {
                    for (auto right : right_subtrees) {
                        TreeNode* root = new TreeNode(root_val);
                        root->left = left;
                        root->right = right;
                        output.push_back(root);
                    }
                }
            }
        }
    }
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> result;
        generateTreesHelper(1, n, result);
        return result;
    }
};
