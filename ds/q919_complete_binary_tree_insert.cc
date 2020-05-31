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
            //assert(incomplete_nodes.empty());
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
    struct LinkedListNode {
        TreeNode *data;
        LinkedListNode *next;
        LinkedListNode(TreeNode* node): data(node), next(nullptr) {}
    };
    TreeNode* root;
    LinkedListNode *incomplete_nodes_head, *incomplete_nodes_tail;
public:
    CBTInserter(TreeNode* root) {
        this->root = root;
        if (root) {
            incomplete_nodes_head = new LinkedListNode(root);
            incomplete_nodes_tail = incomplete_nodes_head;

            auto list_node = incomplete_nodes_head;
            while (list_node) {
                bool complete = false;
                TreeNode* node = list_node->data;
                if (node->left) {
                    auto new_tail = new LinkedListNode(node->left);
                    incomplete_nodes_tail->next = new_tail;
                    incomplete_nodes_tail = new_tail;
                }
                if (node->right) {
                    auto new_tail = new LinkedListNode(node->right);
                    incomplete_nodes_tail->next = new_tail;
                    incomplete_nodes_tail = new_tail;

                    complete = true;
                }
                list_node = list_node->next;
                if (complete) {
                    auto new_head = incomplete_nodes_head->next;
                    delete incomplete_nodes_head;
                    incomplete_nodes_head = new_head;
                }
            }
        }
    }
    
    int insert(int v) {
        if (root) {
            int res;
            assert(incomplete_nodes_head);
            bool complete = false;
            auto new_node = new TreeNode(v);
            TreeNode* node = incomplete_nodes_head->data;
            res = node->val;
            if (!node->left) {
                node->left = new_node;
            } else {
                //assert(!node->right);
                node->right = new_node;
                complete = true;
            }
            incomplete_nodes_tail->next = new LinkedListNode(new_node);
            incomplete_nodes_tail = incomplete_nodes_tail->next;
            if (complete) {
                auto new_head = incomplete_nodes_head->next;
                delete incomplete_nodes_head;
                incomplete_nodes_head = new_head;
            }
            return res;
        } else {
            assert(!incomplete_nodes_head);
            root = new TreeNode(v);
            incomplete_nodes_head = new LinkedListNode(root);
            incomplete_nodes_tail = incomplete_nodes_head;
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
