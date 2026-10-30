// 题目：1339. 分裂二叉树的最大乘积（Maximum Product of Splitted Binary Tree）
// 思路：先求整棵树的总和 s，再后序遍历求每棵子树的和 t；在任意一个「真子树」处切断，两个连通块的乘积就是 t * (s - t)，取最大值后对 1e9+7 取模。
// 时间复杂度：O(n)，两次遍历每个节点一次；空间复杂度：O(h)，递归栈深度（h 为树高）。
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
    int maxProduct(TreeNode* root) {  // root 是二叉树根节点，返回分裂后两部分乘积的最大值（对 1e9+7 取模）
        using ll = long long;  // 乘积会超过 int 范围，统一用 64 位整数
        ll ans = 0;  // 记录最大乘积
        const int mod = 1e9 + 7;  // 题目要求的取模数

        auto sum = [&](this auto&& sum, TreeNode* root) -> ll {  // 递归求子树和；this auto&& 是显式对象参数写法，让 lambda 能自递归调用
            if (!root) {  // 空节点没有贡献
                return 0;  // 空子树和为 0
            }  // 分支结束
            return root->val + sum(root->left) + sum(root->right);  // 子树和 = 根值 + 左子树和 + 右子树和
        };  // 求和 lambda 结束

        ll s = sum(root);  // 整棵二叉树的总和

        auto dfs = [&](this auto&& dfs, TreeNode* root) -> ll {  // 后序遍历：同时求子树和，并尝试以当前节点为切口切断
            if (!root) {  // 空节点没有贡献
                return 0;  // 空子树和为 0
            }
            ll t = root->val + dfs(root->left) + dfs(root->right);  // 当前子树的和（递归过程中顺便求出左右子树和）
            if (t < s) {  // t < s 说明这是真子树（t == s 表示整棵树，切了等于没切，乘积为 0）
                ans = max(ans, t * (s - t));  // 切成 t 与 s - t 两块，用乘积更新答案
            }  // 分支结束
            return t;  // 返回当前子树和，供父节点使用
        };  // 后序遍历 lambda 结束

        dfs(root);  // 从根开始遍历所有子树
        return ans % mod;  // 按题目要求取模后返回
    }  // 方法结束
};  // 类定义结束
