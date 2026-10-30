// 题目：655. 输出二叉树（Print Binary Tree）
// 核心思路：先求树高定矩阵尺寸，再递归按「行 = 深度、列 = 居中偏移」填值。
// 时间复杂度：O(h * 2^h)（要填满矩阵）；空间复杂度：O(h * 2^h) 存放结果。
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
public:
    vector<vector<string>> printTree(TreeNode* root) {  // 把树按满二叉树的网格形状输出成二维字符串数组
        int h = height(root);  // 先求出树高 h（叶子为 0），用来确定矩阵尺寸
        int m = h + 1, n = (1 << (h + 1)) - 1;  // m 是行数 h+1；n 是列数，即满二叉树的总格子数 2^(h+1)-1
        vector<vector<string>> ans(m, vector<string>(n, ""));  // 建 m 行 n 列的矩阵，每个格子初始为空串
        dfs(root, ans, h, 0, (n - 1) / 2);  // 根节点放在第 0 行的正中间列，开始递归填充
        return ans;  // 返回填好的矩阵
    }

    void dfs(TreeNode* root, vector<vector<string>>& ans, int h, int r, int c) {  // 递归填值：r 是行号（深度），c 是列号
        if (!root) return;  // 空节点不占格子，直接返回
        ans[r][c] = to_string(root->val);  // 把节点值转成字符串写入对应格子
        dfs(root->left, ans, h, r + 1, c - pow(2, h - r - 1));  // 左孩子在下一行，列向左偏移 2^(h-r-1)
        dfs(root->right, ans, h, r + 1, c + pow(2, h - r - 1));  // 右孩子在下一行，列向右偏移 2^(h-r-1)
    }

    int height(TreeNode* root) {  // 求树高：空树 -1，叶子 0，便于用 h+1 表示行数
        if (!root) return -1;  // 空节点高度定义为 -1
        return 1 + max(height(root->left), height(root->right));  // 非空节点高度 = 左右子树较大高度 + 1
    }
};  // 题解类定义结束