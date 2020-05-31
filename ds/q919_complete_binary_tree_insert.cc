/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class CBTInserter {
    TreeNode* root;
    deque<TreeNode*> incomplete_nodes;
public:
    CBTInserter(TreeNode* root) {
        this->root = root;
        if (root) {
            incomplete_nodes.push_back(root);
            while (true) {
                auto node = incomplete_nodes.front();
                if (node->left && node->right) {
                    incomplete_nodes.push_back(node->left);
                    incomplete_nodes.push_back(node->right);
                    incomplete_nodes.pop_front();
                } else
                    break;
            }
        }
    }
    
    int insert(int v) {
        auto new_node = new TreeNode(v);
        if (root) {
            auto node = incomplete_nodes.front();
            int res = node->val;
            if (!node->left) {
                node->left = new_node;
            } else {
                node->right = new_node;
                incomplete_nodes.push_back(node->left);
                incomplete_nodes.push_back(node->right);
                incomplete_nodes.pop_front();
            }
            return res;
        } else {
            root = new_node;
            incomplete_nodes.push_back(root);
            return 0;
        }
    }
    
    TreeNode* get_root() {
        return root;
    }
};

class CBTInserter1 {
    TreeNode* root;
    list<TreeNode*> incomplete_nodes;
public:
    CBTInserter(TreeNode* root) {
        this->root = root;
        if (root) {
            incomplete_nodes.push_back(root);
            while (!incomplete_nodes.empty()) {
                TreeNode* node = incomplete_nodes.front();
                if (node->left && node->right) {
                    incomplete_nodes.push_back(node->left);
                    incomplete_nodes.push_back(node->right);
                    incomplete_nodes.pop_front();
                } else
                    break;
            }
        }
    }
    
    int insert(int v) {
        auto new_node = new TreeNode(v);
        if (root) {
            assert(!incomplete_nodes.empty());
            TreeNode* node = incomplete_nodes.front();
            if (!node->left) {
                node->left = new_node;
            } else {
                node->right = new_node;
                incomplete_nodes.push_back(node->left);
                incomplete_nodes.push_back(node->right);
                incomplete_nodes.pop_front();
            }
            return node->val;
        } else {
            assert(incomplete_nodes.empty());
            root = new_node;
            incomplete_nodes.push_back(root);
            return 0;
        }
    }
    
    TreeNode* get_root() {
        return root;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */
