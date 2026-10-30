// 题目：549. 二叉树最长连续序列 II（Binary Tree Longest Consecutive Sequence II）🔒
// 思路：后序遍历，dfs 返回「以当前节点结尾的最长递增连续长度」和「最长递减连续长度」；以当前节点为拐点的最长路径 = 递增段 + 递减段 - 1，用成员变量 ans 记录全局最大值。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高。
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
public:  // 成员对外可见
    int ans;  // 全局最优长度（用成员变量代替 Python 的 nonlocal）

    int longestConsecutive(TreeNode* root) {  // 返回树中最长的连续（相邻节点值相差 1）路径长度
        ans = 0;  // 重置全局答案，避免多组用例互相影响
        dfs(root);  // 后序遍历整棵树，顺便更新 ans
        return ans;  // 返回全局最优值
    }  // 结束 longestConsecutive

    vector<int> dfs(TreeNode* root) {  // 返回 {以 root 结尾的最长递增连续长度, 以 root 结尾的最长递减连续长度}
        if (!root) return {0, 0};  // 空节点两种长度都是 0，作为递归出口
        int incr = 1, decr = 1;  // 只考虑 root 自己时，递增/递减长度都是 1
        auto left = dfs(root->left);  // 先递归左子树，拿到它的两种长度
        auto right = dfs(root->right);  // 再递归右子树，拿到它的两种长度
        if (root->left) {  // 左孩子存在才可能接续
            if (root->left->val + 1 == root->val) incr = left[0] + 1;  // 左孩子的值比根小 1，递增序列可以接在左子树后面
            if (root->left->val - 1 == root->val) decr = left[1] + 1;  // 左孩子的值比根大 1，递减序列可以接在左子树后面
        }  // 结束左孩子处理
        if (root->right) {  // 右孩子同理
            if (root->right->val + 1 == root->val) incr = max(incr, right[0] + 1);  // 右孩子比根小 1，取左右两条递增链中更长的一条
            if (root->right->val - 1 == root->val) decr = max(decr, right[1] + 1);  // 右孩子比根大 1，取左右两条递减链中更长的一条
        }  // 结束右孩子处理
        ans = max(ans, incr + decr - 1);  // 以 root 为拐点的路径 = 递增段 + 递减段 - 重复计算的 root 本身
        return {incr, decr};  // 把以 root 结尾的两种长度返回给父节点使用
    }  // 结束 dfs
};  // 类定义结束