// 题目：965. 单值二叉树（Univalued Binary Tree）
// 思路：先记下根节点的值作为基准值，再深度优先遍历全树，检查每个节点的值是否都等于基准值。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树的高度。
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
    bool isUnivalTree(TreeNode* root) {  // root 是二叉树根节点，返回整棵树的节点值是否全部相同
        int x = root->val;  // 记下根节点的值，作为全树统一的基准值
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> bool {  // 用 C++23 的显式对象参数（deducing this）让 lambda 可以自递归
            if (!root) {  // 空节点不构成反例，视为符合要求
                return true;  // 返回 true，不影响整体判断
            }  // 空节点判断结束
            return root->val == x && dfs(root->left) && dfs(root->right);  // 当前节点值等于基准值，并且左右子树也都满足（短路求值，一旦为假立即返回）
        };  // 递归 lambda 定义结束
        return dfs(root);  // 从根节点开始 DFS 判断
    }  // 方法结束
};  // 题解类结束
