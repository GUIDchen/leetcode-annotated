// 题目：1145. 二叉树着色游戏（Binary Tree Coloring Game）
// 思路：先找到玩家 1 选中的节点 x，分别统计 x 左子树、右子树和其余部分三个连通块的大小，玩家 2 选最大的一块，能占据超过 n/2 个节点即获胜。
// 时间复杂度：O(n)，每个节点只被访问常数次；空间复杂度：O(h)，h 为树高（最坏 O(n) 递归栈）。
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
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {  // root 为整棵树；n 为节点总数；x 为玩家 1 选中的节点值
        auto node = dfs(root, x);  // 找到玩家 1 所选节点所在的位置
        int l = count(node->left), r = count(node->right);  // 分别统计 x 左子树与右子树的节点个数
        return max({l, r, n - l - r - 1}) > n / 2;  // 玩家 2 在左子树 / 右子树 / 其余部分中选最大的一块，超过一半就能赢
    }  // 方法结束

    TreeNode* dfs(TreeNode* root, int x) {  // 深度优先搜索：找到值为 x 的节点
        if (!root || root->val == x) {  // 空节点或命中目标值就停止
            return root;  // 返回命中的节点（可能是空）
        }  // 否则继续向下找
        auto node = dfs(root->left, x);  // 先去左子树找
        return node ? node : dfs(root->right, x);  // 左子树没找到再找右子树
    }  // dfs 结束

    int count(TreeNode* root) {  // 统计以 root 为根的子树节点个数
        if (!root) {  // 空树大小为 0
            return 0;  // 返回 0
        }  // 非空则继续递归
        return 1 + count(root->left) + count(root->right);  // 自己 1 个 加上 左子树 与 右子树的节点数
    }  // count 结束
};  // 类定义结束