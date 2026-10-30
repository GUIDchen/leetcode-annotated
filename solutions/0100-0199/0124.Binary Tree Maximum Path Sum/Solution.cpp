// 题目：124. 二叉树中的最大路径和（Binary Tree Maximum Path Sum）
// 思路：后序 DFS 返回「从当前节点向下延伸的最大单边贡献」，同时用左右贡献之和更新全局答案（路径可以在任意节点拐弯）。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高。
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
 */  // 上面的 TreeNode 结构体由判题器预先提供，这里不需要重复定义
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxPathSum(TreeNode* root) {  // root：二叉树根节点，返回最大路径和
        int ans = -1001;  // 全局答案，节点值最小为 -1000，所以用 -1001 作为更小的初值
        function<int(TreeNode*)> dfs = [&](TreeNode* root) {  // 递归 lambda：返回以 root 为起点向下走的最大单边和
            if (!root) {  // 空节点
                return 0;  // 空子树对路径和没有贡献
            }  // if 结束
            int left = max(0, dfs(root->left));  // 左子树的贡献，负数会拉低总和，所以与 0 取大
            int right = max(0, dfs(root->right));  // 右子树的贡献，同样丢弃负数部分
            ans = max(ans, left + right + root->val);  // 路径在 root 处拐弯：左 + root + 右，用它更新全局答案
            return root->val + max(left, right);  // 往父节点返回时只能选一条边，故取较大的那一侧贡献
        };  // lambda 定义结束
        dfs(root);  // 从根节点开始遍历整棵树
        return ans;  // 返回全局最大路径和
    }  // maxPathSum 结束
};