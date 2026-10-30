// 题目：1457. 二叉树中的伪回文路径（Pseudo-Palindromic Paths in a Binary Tree）
// 思路：从根做一次 DFS，用一个整数的二进制位记录路径上每个数字出现次数的奇偶；到达叶子时，若 mask 中至多只有一位为 1，则这条路径能重排成回文。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高（递归栈深度），mask 本身是常数。
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
    int pseudoPalindromicPaths(TreeNode* root) {  // root：二叉树根节点；返回伪回文路径的条数
        function<int(TreeNode*, int)> dfs = [&](TreeNode* root, int mask) {  // 递归 lambda：root 是当前节点，mask 记录路径上各数字出现次数的奇偶
            if (!root) {  // 空节点没有路径可构成
                return 0;  // 贡献为 0，直接返回
            }  // if 语句块结束
            mask ^= 1 << root->val;  // 异或第 val 位：该数字出现次数的奇偶性翻转（奇变偶、偶变奇）
            if (!root->left && !root->right) {  // 左右子树都为空，说明已经走到叶子，路径完整
                return (mask & (mask - 1)) == 0 ? 1 : 0;  // mask 至多一位为 1 才允许至多一个数字出现奇数次，此时可重排为回文
            }  // if 语句块结束
            return dfs(root->left, mask) + dfs(root->right, mask);  // 分别统计左右子树中的合法路径并相加
        };  // lambda 定义结束
        return dfs(root, 0);  // 从根节点、空 mask 出发开始搜索
    }  // 方法体结束
};  // 类定义结束
