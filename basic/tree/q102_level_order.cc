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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root) {
            deque<TreeNode*> queue;
            queue.push_back(root);
            int level_count = 1;
            while (!queue.empty()) {
                vector<int> values;
                int next_count = 0;
                while (level_count) {
                    TreeNode* node = queue.front(); queue.pop_front();
                    values.push_back(node->val);
                    --level_count;
                    if (node->left) {
                        queue.push_back(node->left);
                        ++next_count;
                    }
                    if (node->right) {
                        queue.push_back(node->right);
                        ++next_count;
                    }
                }
                result.push_back(values);
                level_count = next_count;
            }
        }
        return result;
    }
};
