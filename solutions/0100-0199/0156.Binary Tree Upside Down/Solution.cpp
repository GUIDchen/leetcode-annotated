// 题目：156. 上下翻转二叉树（Binary Tree Upside Down）
// 思路：递归到最左节点作为新根，回溯时把左孩子升为父节点：原左孩子的 right 指向父、left 指向父的原右孩子，再断开父的左右指针。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高（最坏 O(n)）。
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
    TreeNode* upsideDownBinaryTree(TreeNode* root) {  // root：原树根节点；返回翻转后新树的根（即原树最左下的节点）
        if (!root || !root->left) return root;  // 递归出口：空节点直接返回；没有左孩子说明已是最左节点，它就是新根
        TreeNode* newRoot = upsideDownBinaryTree(root->left);  // 先递归处理左子树，拿到整棵新树的根
        root->left->right = root;  // 把原左孩子的右指针指向当前节点，实现「父变子」
        root->left->left = root->right;  // 把原左孩子的左指针指向当前节点的原右孩子
        root->left = nullptr;  // 断开当前节点原有的左指针，避免形成环
        root->right = nullptr;  // 断开当前节点原有的右指针，它已交给上一层接管
        return newRoot;  // 返回递归过程中保留下来的新根
    }  // 题解方法结束
};  // 题解类定义结束