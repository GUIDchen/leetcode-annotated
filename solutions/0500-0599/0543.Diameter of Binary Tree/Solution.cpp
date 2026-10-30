// 题目：543. 二叉树的直径（Diameter of Binary Tree）
// 思路：树形 DP + C++23 递归 lambda。递归求每个节点的左右子树高度，路径经过该节点时的长度为 l+r，用外层变量 ans 记录全局最大值，向上返回 1+max(l,r)。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
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
    int diameterOfBinaryTree(TreeNode* root) {  // 入口：返回二叉树的直径（任意两节点间最长路径的边数）
        int ans = 0;  // ans 记录全局最长路径长度，由下面的 lambda 捕获并就地更新
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> int {  // C++23 的「推导 this」递归 lambda：第一个参数 dfs 就是它自己，便于递归调用
            if (!root) {  // 空节点高度为 0，作为递归边界
                return 0;  // 空树贡献的高度是 0
            }
            int l = dfs(root->left);  // 左子树高度
            int r = dfs(root->right);  // 右子树高度
            ans = max(ans, l + r);  // 经过当前节点的路径长度就是左右子树高度之和，取较大值更新答案
            return 1 + max(l, r);  // 向上返回以当前节点为根的子树高度：较高的一棵子树再加 1（算上自己）
        };  // lambda 定义结束
        dfs(root);  // 从根节点开始一次后序遍历即可算出答案
        return ans;  // 返回最长路径长度
    }
};
