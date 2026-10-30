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
// 题目：530. 二叉搜索树的最小绝对差（Minimum Absolute Difference in BST）
// 思路：二叉搜索树的中序遍历是严格递增序列，最小绝对差一定出现在中序里相邻的两个节点之间，边遍历边比较。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高，最坏 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    int getMinimumDifference(TreeNode* root) {  // root 是二叉搜索树的根节点
        const int inf = 1 << 30;  // 取一个足够大的数当无穷大，1<<30 约 10.7 亿
        int ans = inf, pre = -inf;  // ans 存最小差；pre 存中序前驱的值，初值取负无穷让第一次做差不产生有效答案
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> void {  // C++23 显式对象参数：让 lambda 能递归调用自己
            if (!root) {  // 空节点是递归出口
                return;  // 直接返回
            }
            dfs(root->left);  // 先中序遍历左子树，保证按升序访问节点
            ans = min(ans, root->val - pre);  // 当前值减前驱值即中序相邻差，取最小值
            pre = root->val;  // 当前值成为下一个节点的前驱
            dfs(root->right);  // 最后中序遍历右子树
        };
        dfs(root);  // 从根开始中序遍历整棵树
        return ans;  // 返回最小绝对差
    }
};
