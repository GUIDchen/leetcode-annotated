// 题目：687. 最长同值路径（Longest Univalue Path）
// 思路：后序 DFS，返回「以当前节点为端点向下延伸的同值路径长度」，再用左右两臂之和更新全局最大边数。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归 lambda 的调用栈深度等于树高 h。
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
    int longestUnivaluePath(TreeNode* root) {  // root 为树根，返回最长同值路径经过的边数
        int ans = 0;  // 全局答案：最长同值路径的边数，初值为 0
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> int {  // C++23 显式对象参数（this auto&& dfs）让 lambda 能递归调用自身，并按引用捕获 ans
            if (!root) {  // 空节点：没有可延伸的路径
                return 0;  // 空子树贡献长度为 0
            }
            int l = dfs(root->left);  // 先求左子树向下延伸的同值长度
            int r = dfs(root->right);  // 再求右子树向下延伸的同值长度
            l = root->left && root->left->val == root->val ? l + 1 : 0;  // 左孩子与当前值相同才能接上这条边（长度 +1），否则同值路径在此断开，记 0
            r = root->right && root->right->val == root->val ? r + 1 : 0;  // 右孩子同理：值相同才 +1，否则断开记 0
            ans = max(ans, l + r);  // 以当前节点为拐点，左右两臂拼成一条路径，边数为 l + r，更新全局最大值
            return max(l, r);  // 向上返回时只能选一条臂，取较长者
        };  // 递归 lambda 定义结束
        dfs(root);  // 从根节点开始后序遍历
        return ans;  // 返回统计到的最大边数
    }
};
