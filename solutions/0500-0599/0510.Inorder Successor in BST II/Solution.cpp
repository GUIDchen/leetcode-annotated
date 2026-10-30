// 题目：510. 二叉搜索树中的中序后继 II（Inorder Successor in BST II）
// 思路：有右子树时，后继是右子树中最左（最小）的节点；否则沿 parent 上爬，直到当前节点是父节点的左孩子，该父节点即后继。
// 时间复杂度：O(h)，h 为树高；空间复杂度：O(1)，只用常数个指针。
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    Node* inorderSuccessor(Node* node) {  // node：BST 中的某个节点；返回它的中序后继，不存在则返回 nullptr
        if (node->right) {  // 情况一：有右子树，后继是右子树中最小的节点
            node = node->right;  // 先走到右子树的根
            while (node->left) {  // 一路向左，找右子树中的最小值
                node = node->left;  // 继续向左
            }  // 左孩子为空，此时 node 就是右子树中的最小节点
            return node;  // 它就是中序后继
        }  // 情况一处理结束
        while (node->parent && node->parent->right == node) {  // 情况二：无右子树，向上找第一个“自己是父节点左孩子”的位置
            node = node->parent;  // 当前节点是父节点的右孩子，说明父节点比它先被访问，继续上爬
        }  // 循环结束：要么到了根（parent 为空），要么当前节点是父节点的左孩子
        return node->parent;  // 该父节点就是后继；若已到根则为 nullptr，表示没有后继
    }  // 方法结束
};  // 类定义结束