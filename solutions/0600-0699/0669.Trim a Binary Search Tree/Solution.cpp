// 题目：669. 修剪二叉搜索树（Trim a Binary Search Tree）
// 思路：利用 BST 有序性递归：节点值大于 high 时整棵右子树都不合法，直接换成左子树的修剪结果；小于 low 时反之。
// 时间复杂度：O(n)，每个节点最多访问一次；空间复杂度：O(h)，递归深度为树高 h。
// 下面这段是 LeetCode 题面给出的 TreeNode 定义，判题器会自动注入，无需自己补。
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
public:  // 公有接口
    TreeNode* trimBST(TreeNode* root, int low, int high) {  // 返回只保留 [low, high] 区间内节点后的 BST 根
        if (!root) return root;  // 空树直接返回
        if (root->val > high) return trimBST(root->left, low, high);  // 节点值超过上界：它和右子树都要丢弃，只需修剪左子树
        if (root->val < low) return trimBST(root->right, low, high);  // 节点值小于下界：它和左子树都要丢弃，只需修剪右子树
        root->left = trimBST(root->left, low, high);  // 当前节点保留，继续修剪左子树并挂回去
        root->right = trimBST(root->right, low, high);  // 继续修剪右子树并挂回去
        return root;  // 返回修剪后的当前节点
    }  // 结束 trimBST
};