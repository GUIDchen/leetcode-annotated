// 题目：814. 二叉树剪枝（Binary Tree Pruning）
// 思路：后序遍历，先递归剪掉左右子树，再判断当前结点是否为 0 且没有子结点，是则整棵删除。
// 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(h)，递归栈深度为树高。
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
    TreeNode* pruneTree(TreeNode* root) {  // root 为子树根结点，返回剪枝后的子树根
        if (!root) {  // 空结点无法再剪，直接返回
            return root;  // 原样返回空指针
        }  // if 结束
        root->left = pruneTree(root->left);  // 先把左子树剪干净，并把新的左子结点接回
        root->right = pruneTree(root->right);  // 再把右子树剪干净，并把新的右子结点接回
        if (root->val == 0 && root->left == root->right) {  // 当前值为 0 且左右子结点都为空，说明整棵子树全是 0
            return nullptr;  // 返回空指针，相当于删除这棵子树
        }  // if 结束
        return root;  // 否则保留当前结点
    }  // 方法结束
};  // 类定义结束
