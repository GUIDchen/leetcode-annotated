// 题目：226. 翻转二叉树（Invert Binary Tree）
// 思路：递归先翻转左右子树，再把根节点的左右孩子指针互换，相当于后序遍历整棵树。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高，最坏 O(n)。
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
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    TreeNode* invertTree(TreeNode* root) {  // root 是子树根节点；返回翻转后的同一棵树根
        if (!root) {  // 空节点没有孩子可交换，直接返回作为递归出口
            return root;  // 返回空指针，父节点的孩子位置保持不变
        }
        TreeNode* l = invertTree(root->left);  // 先把左子树整体翻转好，l 是翻转后的新左子根
        TreeNode* r = invertTree(root->right);  // 再把右子树整体翻转好，r 是翻转后的新右子根
        root->left = r;  // 交换：原来的右子树接到根节点左边
        root->right = l;  // 交换：原来的左子树接到根节点右边
        return root;  // 返回翻转完成的根节点给上一层使用
    }
};