// 题目：1123. 最深叶节点的最近公共祖先（Lowest Common Ancestor of Deepest Leaves）
// 思路：后序 DFS 返回「该子树中最深叶子的公共祖先 + 子树高度」；左右高度相同时最深叶子跨两侧，当前节点即为答案。
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
    TreeNode* lcaDeepestLeaves(TreeNode* root) {  // 返回所有最深叶子节点的最近公共祖先
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> pair<TreeNode*, int> {  // 后序递归 lambda：返回 {该子树最深叶子的公共祖先, 该子树高度}；this auto&& 是 C++23 显式对象参数，用于自调用
            if (!root) {  // 空节点
                return {nullptr, 0};  // 递归出口：没有祖先，高度记为 0
            }  // 空节点分支结束
            auto [l, d1] = dfs(root->left);  // 先求左子树：l 是答案，d1 是左子树高度
            auto [r, d2] = dfs(root->right);  // 再求右子树：r 是答案，d2 是右子树高度
            if (d1 > d2) {  // 左子树更高，说明最深叶子全在左边
                return {l, d1 + 1};  // 左子树的答案原样上移一层，高度加 1
            }  // 左高分支结束
            if (d1 < d2) {  // 右子树更高，说明最深叶子全在右边
                return {r, d2 + 1};  // 右子树的答案原样上移一层，高度加 1
            }  // 右高分支结束
            return {root, d1 + 1};  // 左右等高：最深叶子分布在两侧，当前 root 就是它们的公共祖先
        };  // lambda 定义结束
        return dfs(root).first;  // 只取祖先，丢弃高度信息
    }  // 方法结束
};  // 类定义结束