// 题目：1740. 找到二叉树中的距离（Find Distance in a Binary Tree）
// 思路：先用递归求出 p、q 的最近公共祖先 g，再从 g 出发分别 DFS 求到 p、q 的边数，两者相加就是两点间的距离。
// 时间复杂度：O(n)，求 LCA 和两次 DFS 各自最多遍历一遍节点；空间复杂度：O(h)，递归栈深度为树高 h。
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
    int findDistance(TreeNode* root, int p, int q) {  // root：二叉树根；p、q：要求距离的两个节点值
        TreeNode* g = lca(root, p, q);  // 先求出 p、q 的最近公共祖先，两点之间的路径一定经过它
        return dfs(g, p) + dfs(g, q);  // 距离 = g 到 p 的边数 + g 到 q 的边数
    }

    TreeNode* lca(TreeNode* root, int p, int q) {  // 求最近公共祖先：返回 p、q 的 LCA 节点
        if (!root || root->val == p || root->val == q) return root;  // 走到空节点，或当前节点就是 p/q，直接返回它
        TreeNode* left = lca(root->left, p, q);  // 在左子树里递归寻找
        TreeNode* right = lca(root->right, p, q);  // 在右子树里递归寻找
        if (!left) return right;  // 左子树里一个都没找到，答案落在右子树
        if (!right) return left;  // 右子树里一个都没找到，答案落在左子树
        return root;  // 左右各找到一个，说明当前节点就是它们的最近公共祖先
    }

    int dfs(TreeNode* root, int v) {  // 从 root 出发走到值为 v 的节点，返回经过的边数
        if (!root) return -1;  // 走到空节点说明这条路上没有 v，用 -1 表示失败
        if (root->val == v) return 0;  // 正好是目标节点，距离为 0
        int left = dfs(root->left, v);  // 到左子树里继续找
        int right = dfs(root->right, v);  // 到右子树里继续找
        if (left == -1 && right == -1) return -1;  // 两边都没找到，向上返回失败
        return 1 + max(left, right);  // 找到的那一侧距离再加一，就是当前节点到 v 的边数
    }
};