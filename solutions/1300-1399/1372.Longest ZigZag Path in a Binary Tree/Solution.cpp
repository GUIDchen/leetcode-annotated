// 题目：1372. 二叉树中的最长交错路径（Longest ZigZag Path in a Binary Tree）
// 思路：DFS 同时携带「上一步向左」和「上一步向右」两种当前长度，向左走时用右长度加一，向右走时用左长度加一，边走边更新答案。
// 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
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
    int ans = 0;  // 全局答案：记录遍历过程中见到的最长交错路径长度

    int longestZigZag(TreeNode* root) {  // root 为树根，返回最长交错路径经过的边数
        dfs(root, 0, 0);  // 从根出发，左右两个方向的当前长度都是 0
        return ans;  // 返回遍历中累计得到的最优答案
    }  // 方法结束

    void dfs(TreeNode* root, int l, int r) {  // 辅助 DFS：l 表示上一步向左走时的当前长度，r 表示上一步向右走时的当前长度
        if (!root) return;  // 空结点没有可延伸的路径，直接回溯
        ans = max(ans, max(l, r));  // 到达非空结点，先用两个方向的长度更新全局答案
        dfs(root->left, r + 1, 0);  // 向左走：上一步必须是向右的才交错，所以长度取 r+1，左方向累计清零
        dfs(root->right, 0, l + 1);  // 向右走：上一步必须是向左的才交错，所以长度取 l+1，右方向累计清零
    }  // 辅助函数结束
};  // 类定义结束