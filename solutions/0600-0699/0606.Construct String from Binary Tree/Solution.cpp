// 题目：606. 根据二叉树创建字符串（Construct String from Binary Tree）
// 思路：递归前序遍历，根节点写成 val(...)；左子树为空而右子树非空时必须保留一对空括号，右子树为空则整体省略。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，递归栈深度与拼接出的字符串。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类（上面是题目自带的 TreeNode 定义注释）
public:  // 题解方法对外可见
    string tree2str(TreeNode* root) {  // 把以 root 为根的子树转成题目要求的括号字符串
        if (!root) return "";  // 空节点不产生任何字符，直接返回空串
        if (!root->left && !root->right) return to_string(root->val);  // 叶子节点不需要括号，只输出节点值
        if (!root->right) return to_string(root->val) + "(" + tree2str(root->left) + ")";  // 只有左孩子时输出「值(左子树)」，右子树的括号整体省略
        return to_string(root->val) + "(" + tree2str(root->left) + ")(" + tree2str(root->right) + ")";  // 左右孩子都存在（或仅右孩子存在）时，左右子树都要用括号包起来
    }  // 方法结束
};  // 类定义结束