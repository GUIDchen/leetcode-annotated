// 题目：2331. 计算布尔二叉树的值（Evaluate Boolean Binary Tree）
// 思路：后序递归——叶子节点直接返回其 0/1 值，内部节点 val 为 2 时对左右子树取「或」、为 3 时取「与」。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高 h（最坏 O(n)）。
/**
 * Definition for a binary tree node.
 * struct TreeNode {  // 题目给出的二叉树节点结构体
 *     int val;  // 节点值：叶子为 0/1，内部节点为 2（或）/3（与）
 *     TreeNode *left;  // 左子树指针
 *     TreeNode *right;  // 右子树指针
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}  // 默认构造：值为 0，左右子树为空
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}  // 单参数构造：给定值，左右子树为空
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}  // 三参数构造：同时指定值与左右子树
 * };  // 结构体定义结束
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool evaluateTree(TreeNode* root) {  // 主函数：返回整棵布尔表达式树的真假值
        if (!root->left) {  // 左孩子为空即叶子节点（布尔树是满二叉树），不必再递归
            return root->val;  // 叶子只存 0/1，返回时隐式转换成 bool
        }  // 叶子分支结束
        if (root->val == 2) {  // 内部节点值 2 代表逻辑或（OR）
            return evaluateTree(root->left) || evaluateTree(root->right);  // 递归求左右子树后取或，任一为真结果就为真
        }  // 或分支结束
        return evaluateTree(root->left) && evaluateTree(root->right);  // 剩下的只可能是 3，代表逻辑与（AND），两侧都为真才为真
    }  // 方法结束
};  // 类结束