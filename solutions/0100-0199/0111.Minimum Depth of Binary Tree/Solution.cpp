// 题目：111. 二叉树的最小深度（Minimum Depth of Binary Tree）
// 思路：递归。空结点为 0；只剩一个孩子时必须沿该孩子递归（最小深度终点必须是叶子）；两个孩子都在才取较小值加一。
// 时间复杂度：O(n)，最坏访问每个结点一次；空间复杂度：O(h)，h 为树高，即递归栈深度。
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
    int minDepth(TreeNode* root) {  // root 是树根，返回根到最近叶子的结点数
        if (!root) {  // 空结点没有深度
            return 0;  // 空子树深度为 0
        }  // 空结点处理完毕
        if (!root->left) {  // 没有左孩子时，只能沿右子树继续找叶子
            return 1 + minDepth(root->right);  // 深度等于右子树最小深度加一
        }  // 左孩子判断结束
        if (!root->right) {  // 没有右孩子时，只能沿左子树继续找叶子
            return 1 + minDepth(root->left);  // 深度等于左子树最小深度加一
        }  // 右孩子判断结束
        return 1 + min(minDepth(root->left), minDepth(root->right));  // 两个孩子都在：取左右最小深度的较小者，再加当前这一层
    }  // 方法结束
};  // 题解类结束