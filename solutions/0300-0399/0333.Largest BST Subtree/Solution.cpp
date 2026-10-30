// 题目：333. 最大二叉搜索子树（Largest BST Subtree）
// 思路：后序 DFS，返回 {子树最小值, 子树最大值, 节点数}；若左子树最大值 < 根 < 右子树最小值，则整棵子树是 BST，用它的节点数更新答案。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度（h 为树高）。
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
// 上面是 LeetCode 题面给出的二叉树节点定义，判题器已提供，此处仅作说明
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int ans;  // 全局答案：最大 BST 子树的节点数（每次调用入口处重置）

    int largestBSTSubtree(TreeNode* root) {  // root：二叉树根节点，返回其中最大的二叉搜索子树（BST）的节点数
        ans = 0;  // 先把答案清零，避免多次调用同一对象时互相影响
        dfs(root);  // 后序遍历整棵树，过程中不断更新 ans
        return ans;  // 返回统计到的最大 BST 大小
    }  // 方法结束

    vector<int> dfs(TreeNode* root) {  // 后序 DFS：返回 {子树最小值, 子树最大值, 子树节点数}
        if (!root) return {INT_MAX, INT_MIN, 0};  // 空节点返回哨兵：最小值 INT_MAX、最大值 INT_MIN，任何父节点与它比较都能通过；节点数记 0
        auto left = dfs(root->left);  // 递归求左子树的三元组
        auto right = dfs(root->right);  // 递归求右子树的三元组
        if (left[1] < root->val && root->val < right[0]) {  // 左子树最大值 < 根值 < 右子树最小值，说明以 root 为根的整棵子树是 BST
            ans = max(ans, left[2] + right[2] + 1);  // 用整棵子树的节点数更新全局答案
            return {min(root->val, left[0]), max(root->val, right[1]), left[2] + right[2] + 1};  // 返回合并后的最小值、最大值与节点总数，供父节点判断
        }  // if 分支结束
        return {INT_MIN, INT_MAX, 0};  // 不是 BST：返回 INT_MIN/INT_MAX 哨兵，让父节点判定必然失败，节点数记 0
    }  // 方法结束
};  // 类结束