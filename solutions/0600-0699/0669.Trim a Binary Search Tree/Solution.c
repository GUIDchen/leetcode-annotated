// 题目：669. 修剪二叉搜索树（Trim a Binary Search Tree）
// 思路：利用 BST 有序性递归：节点值小于 low 时它和左子树整体偏小、可整棵丢弃，只修剪右子树；大于 high 时反之。
// 时间复杂度：O(n)，每个节点最多访问一次；空间复杂度：O(h)，递归深度为树高 h。
// 下面这段是 LeetCode 题面给出的 TreeNode 定义，判题器会自动注入，无需自己补。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* trimBST(struct TreeNode* root, int low, int high) {  // 返回只保留 [low, high] 闭区间内节点后的 BST 根节点
    if (!root) {  // 空树直接返回
        return root;  // 返回空指针
    }
    if (root->val < low) {  // 当前节点小于下界：它和它的左子树都不合法
        return trimBST(root->right, low, high);  // 合法节点只可能在右子树，用右子树的修剪结果顶替自己
    }
    if (root->val > high) {  // 当前节点大于上界：它和它的右子树都不合法
        return trimBST(root->left, low, high);  // 合法节点只可能在左子树，用左子树的修剪结果顶替自己
    }
    root->left = trimBST(root->left, low, high);  // 当前节点合法，保留它，只需继续修剪左子树
    root->right = trimBST(root->right, low, high);  // 继续修剪右子树
    return root;  // 返回修剪后的当前节点
}