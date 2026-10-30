// 题目：1373. 二叉搜索子树的最大键值和（Maximum Sum BST in Binary Tree）
// 思路：后序遍历，每个子树返回「是否 BST、最小值、最大值、键值和」，用子树的这四项自底向上判断当前子树是否为 BST 并统计最大和。
// 时间复杂度：O(n)，每个结点只被访问常数次；空间复杂度：O(h)，递归栈深度为树高 h。
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
    int maxSumBST(TreeNode* root) {  // root 为树根，返回所有二叉搜索子树中键值和的最大值
        int ans = 0;  // 答案初值 0：题目允许没有符合要求的非空 BST 时返回 0
        const int inf = 1 << 30;  // 取足够大的数作为「空子树最大值」的哨兵，保证边界比较成立
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> array<int, 4> {  // 泛型 lambda 自己调用自己（C++23 的 this auto&& 写法），返回 {是否BST, 最小值, 最大值, 键值和}
            if (!root) {  // 空结点视为合法的 BST
                return {1, inf, -inf, 0};  // 空子树：是 BST 记 1，最小值 +inf，最大值 -inf，和为 0
            }  // 空结点分支结束
            auto l = dfs(root->left);  // 递归处理左子树，取回左子树的四项信息
            auto r = dfs(root->right);  // 递归处理右子树，取回右子树的四项信息
            int v = root->val;  // 当前结点的值
            if (l[0] && r[0] && l[2] < v && v < r[1]) {  // 左右子树都是 BST，且左子树最大值 < 当前值 < 右子树最小值，当前子树才是 BST
                int s = l[3] + r[3] + v;  // 当前 BST 的键值和 = 左子树和 + 右子树和 + 当前值
                ans = max(ans, s);  // 用当前键值和更新全局最大值
                return {1, min(l[1], v), max(r[2], v), s};  // 返回当前子树的四项信息：最小值取左最小与当前值，最大值取右最大与当前值
            }  // 不满足 BST 条件的分支结束
            return {0};  // 不是 BST 时只把标志位置 0，其余字段父结点不会使用
        };  // lambda 定义结束
        dfs(root);  // 从根开始后序遍历，边遍历边更新答案
        return ans;  // 返回最大键值和
    }  // 方法结束
};  // 类定义结束
