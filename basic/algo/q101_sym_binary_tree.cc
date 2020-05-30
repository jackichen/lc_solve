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
    // 0ms 12.5MB
    bool isSymmetric_rec(TreeNode* root) {
        if (!root) return true;

        return isSymmetric_rec(root, root);
    }
    bool isSymmetric_rec(TreeNode* left, TreeNode* right) {
        if (left == nullptr)
            return (right == nullptr);
        else if (right == nullptr)
            return false;

        return (left->val == right->val) &&
               isSymmetric(left->left, right->right) &&
               isSymmetric(left->right, right->left);
    }
    
    // 4ms 12.9MB
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        deque<TreeNode*> left_queue, right_queue;
        left_queue.push_back(root);
        right_queue.push_back(root);
        while (!left_queue.empty()) {
            if (right_queue.empty()) return false;
            TreeNode* left = left_queue.front(); left_queue.pop_front();
            TreeNode* right = right_queue.front(); right_queue.pop_front();
            if (left->val != right->val) return false;

            if (left->left) {
                if (!right->right) return false;
                left_queue.push_back(left->left);
                right_queue.push_back(right->right);
            } else if (right->right)
                return false;
            
            if (left->right) {
                if (!right->left) return false;
                left_queue.push_back(left->right);
                right_queue.push_back(right->left);
            } else if (right->left)
                return false;
        }
        return true;
    }
};
