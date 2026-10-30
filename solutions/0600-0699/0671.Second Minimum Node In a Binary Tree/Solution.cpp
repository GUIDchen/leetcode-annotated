// 题目：671. 二叉树中第二小的节点（Second Minimum Node In a Binary Tree）
// 思路：根节点即全树最小值，DFS 收集所有严格大于根值的节点值，其中最小的那个就是第二小；不存在则返回 -1。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高（最坏 O(n)）。
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
    int ans = -1;  // 记录第二小的值，-1 表示还没有找到

    int findSecondMinimumValue(TreeNode* root) {  // root：二叉树根节点
        dfs(root, root->val);  // 以根值（全树最小值）为基准遍历整棵树
        return ans;  // 返回第二小的值，找不到时仍是 -1
    }

    void dfs(TreeNode* root, int val) {  // val：传入的最小值基准
        if (!root) return;  // 空节点直接返回，作为递归出口
        dfs(root->left, val);  // 递归处理左子树
        dfs(root->right, val);  // 递归处理右子树
        if (root->val > val) ans = ans == -1 ? root->val : min(ans, root->val);  // 比基准大的值中取最小者
    }
};