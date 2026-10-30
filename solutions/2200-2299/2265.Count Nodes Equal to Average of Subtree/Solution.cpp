// 题目：2265. 统计值等于子树平均值的节点数（Count Nodes Equal to Average of Subtree）
// 思路：后序遍历（DFS），每层返回该子树的 (节点值之和, 节点个数)，用整数除法求出平均值并与根节点值比较，相等则答案加一。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度为树高 h（最坏情况 O(n)）。
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
    int averageOfSubtree(TreeNode* root) {  // root：二叉树根节点
        int ans = 0;  // 统计「节点值恰好等于其子树平均值」的节点个数
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> pair<int, int> {  // 递归 lambda：C++23 显式对象参数实现自引用；返回 (子树节点值之和, 子树节点数)
            if (!root) {  // 空节点：递归出口
                return {0, 0};  // 空子树对和的贡献为 0，节点个数也为 0
            }
            auto [ls, ln] = dfs(root->left);  // 递归求左子树的 (和, 节点数)，再用结构化绑定解包
            auto [rs, rn] = dfs(root->right);  // 递归求右子树的 (和, 节点数)
            int s = ls + rs + root->val;  // 以当前节点为根的子树全部节点值之和
            int n = ln + rn + 1;  // 该子树的节点总数（左右子树节点数 + 当前节点）
            if (s / n == root->val) {  // 整数除法向下取整得到平均值，恰好等于当前节点值
                ++ans;  // 满足题目条件，答案加一
            }
            return {s, n};  // 把本子树的 (和, 节点数) 返回给父节点复用
        };
        dfs(root);  // 从根节点开始后序遍历整棵树
        return ans;  // 返回满足条件的节点总数
    }
};
