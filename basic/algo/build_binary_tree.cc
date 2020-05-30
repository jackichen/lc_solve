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
    TreeNode* buildTreeInPre(vector<int>& preorder, vector<int>& inorder) {
        // invalid input
        if (preorder.size() != inorder.size()) return nullptr;

        unordered_map<int, int> inorder_hash;
        int count = inorder.size();
        for (int i=0; i<count; ++i)
            inorder_hash[inorder[i]] = i;

        return buildTreeInPreHelper(preorder, inorder, 0, 0, count, inorder_hash);
    }
    TreeNode* buildTreeInPreHelper(vector<int>& preorder, vector<int>& inorder,
                                   int pre_offset, int in_offset, int count,
                                   const unordered_map<int, int>& inorder_hash) {
        if (count <= 0) return nullptr;

        int root_val = preorder[pre_offset];
        TreeNode *root = new TreeNode(root_val);
        int left_count = inorder_hash[root_val] - in_offset;
        int delta = left_count + 1;
        root->left = buildTreeInPreHelper(preorder, inorder, pre_offset + 1, in_offset, left_count, inorder_hash);
        root->right = buildTreeInPreHelper(preorder, inorder, pre_offset + delta, in_offset + delta,
                                           count - delta, inorder_hash);
        return root;
    }
    
    TreeNode* buildTreeInPost(vector<int>& inorder, vector<int>& postorder) {
        // invalid input
        if (postorder.size() != inorder.size()) return nullptr;

        unordered_map<int, int> inorder_hash;
        int count = inorder.size();
        for (int i=0; i<count; ++i)
            inorder_hash[inorder[i]] = i;

        return buildTreeInPostHelper(inorder, postorder, 0, 0, count, inorder_hash);
    }
    TreeNode* buildTreeInPostHelper(vector<int>& inorder, vector<int>& postorder,
                                    int in_offset, int post_offset, int count,
                                    const unordered_map<int, int>& inorder_hash) {
        if (count <= 0) return nullptr;

        int root_val = postorder[post_offset+count-1];
        TreeNode *root = new TreeNode(root_val);
        int left_count = inorder_hash[root_val] - in_offset;
        int delta = left_count + 1;
        root->left = buildTreeInPostHelper(inorder, postorder, in_offset, post_offset, left_count, inorder_hash);
        root->right = buildTreeInPostHelper(inorder, postorder, in_offset + delta, post_offset + left_count,
                                            count - delta, inorder_hash);
        return root;
    }
};
