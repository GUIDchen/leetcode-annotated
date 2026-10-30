// 题目：104. 二叉树的最大深度（Maximum Depth of Binary Tree）
// 思路：后序递归，先取左右子树的最大深度，再取两者较大值加一，即当前节点的高。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，h 为树高，即递归栈的最大深度。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x, left), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDepth(TreeNode* root) {  // root：树根，返回整棵二叉树的最大深度
        if (!root) return 0;  // 空节点深度为 0，递归边界
        int l = maxDepth(root->left), r = maxDepth(root->right);  // 分别递归求左右子树的最大深度
        return 1 + max(l, r);  // 当前层贡献 1，取左右较深的一支继续累加
    }
};