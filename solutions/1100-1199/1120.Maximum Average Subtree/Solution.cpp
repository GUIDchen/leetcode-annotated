// 题目：1120. 子树的最大平均值（Maximum Average Subtree）
// 思路：后序 DFS 让每个节点返回「子树和 + 节点数」，一次遍历中顺便用 sum/count 更新答案，避免每个子树重复统计。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，递归栈最坏深度为 n。
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
    double maximumAverageSubtree(TreeNode* root) {  // root：二叉树根节点；返回所有子树平均值中的最大值
        double ans = 0;  // 记录当前最大平均值；题目保证节点值非负，所以 0 是安全的初值
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> pair<int, int> {  // 后序递归 lambda：返回 {子树和, 节点数}；this auto&& 是 C++23 的显式对象参数，让 lambda 能调用自己
            if (!root) {  // 空节点既没有和也没有节点数
                return {0, 0};  // 递归出口：返回零和与零个节点
            }  // 空节点分支结束
            auto [ls, ln] = dfs(root->left);  // 先递归左子树，拿到左子树的和与节点数
            auto [rs, rn] = dfs(root->right);  // 再递归右子树，拿到右子树的和与节点数
            int s = root->val + ls + rs;  // 以 root 为根的子树元素和
            int n = 1 + ln + rn;  // 以 root 为根的子树节点数（含 root 自己）
            ans = max(ans, s * 1.0 / n);  // 乘 1.0 转成浮点避免整数除法，顺便更新最大值
            return {s, n};  // 把和与节点数返回给父节点复用
        };  // lambda 定义结束
        dfs(root);  // 从根节点开始遍历所有子树
        return ans;  // 返回遍历中记录到的最大平均值
    }  // 方法结束
};  // 类定义结束
