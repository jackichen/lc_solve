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
