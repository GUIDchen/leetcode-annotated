// 题目：431. 将 N 叉树编码为二叉树（Encode N-ary Tree to Binary Tree）
// 思路：左孩子右兄弟表示法——N 叉节点的第一个孩子挂到二叉树的 left，其余孩子依次挂在前一个孩子的 right 链上；解码时沿 left + right 链反向还原。
// 时间复杂度：O(n)，每个节点只被访问一次；空间复杂度：O(n)，递归调用栈与新建节点的开销。
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
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

class Codec {  // 编码 / 解码器类：负责 N 叉树与二叉树之间的双向转换
public:  // 方法对外可见
    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root) {  // 编码入口：把 N 叉树根 root 转成对应的二叉树根并返回
        if (root == nullptr) {  // 空节点直接返回空，作为递归终止条件
            return nullptr;  // 空树编码后仍是空树
        }
        TreeNode* node = new TreeNode(root->val);  // 用当前 N 叉节点的值新建一个二叉树节点
        if (root->children.empty()) {  // children 为空说明这个 N 叉节点是叶子，无需挂孩子
            return node;  // 叶子节点即编码结果，直接返回
        }
        TreeNode* left = encode(root->children[0]);  // 递归编码第 0 个孩子，它将作为当前节点在二叉树中的左孩子
        node->left = left;  // 建立「父节点 → 第一个孩子」的 left 指针
        for (int i = 1; i < root->children.size(); i++) {  // 第 2 个孩子起，依次串成左孩子的右兄弟链
            left->right = encode(root->children[i]);  // 让当前兄弟的 right 指向下一个孩子的编码结果
            left = left->right;  // 指针后移一位，准备挂再下一个兄弟
        }
        return node;  // 返回当前子树对应的二叉树根
    }

    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* data) {  // 解码入口：把二叉树 data 还原成 N 叉树并返回根
        if (data == nullptr) {  // 空指针表示这里没有对应的 N 叉节点
            return nullptr;  // 递归终止，返回空
        }
        Node* node = new Node(data->val, vector<Node*>());  // 用二叉树节点的值新建 N 叉节点，孩子列表先置为空
        if (data->left == nullptr) {  // left 为空说明原 N 叉节点没有孩子
            return node;  // 叶子节点直接返回，无需遍历右链
        }
        TreeNode* left = data->left;  // 从左孩子出发，沿 right 链遍历，每个节点正好对应原树的一个孩子
        while (left != nullptr) {  // 右兄弟链非空就继续还原
            node->children.push_back(decode(left));  // 递归解码该孩子并追加到孩子列表末尾，保持原树的孩子顺序
            left = left->right;  // 沿 right 链前进到下一个兄弟
        }
        return node;  // 返回还原出的 N 叉节点
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));
