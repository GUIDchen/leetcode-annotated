// 题目：298. 二叉树最长连续序列（Binary Tree Longest Consecutive Sequence）🔒
// 思路：后序 DFS，返回以当前结点为起点的向下连续递增长度；孩子值不等于父值 +1 时该侧链断开、重置为 1。
// 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(h)，递归栈深度为树高。
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
    int longestConsecutive(TreeNode* root) {  // root：树根；返回整棵树中最长的连续递增路径长度
        int ans = 0;  // 记录全局最大长度
        function<int(TreeNode*)> dfs = [&](TreeNode* root) {  // 递归函数：返回以入参结点为起点的向下连续长度
            if (!root) {  // 空结点
                return 0;  // 空路径长度为 0
            }  // if 块结束
            int l = dfs(root->left) + 1;  // 左子树递归结果再接上自己，所以 +1
            int r = dfs(root->right) + 1;  // 右子树递归结果再接上自己，所以 +1
            if (root->left && root->left->val - root->val != 1) {  // 左孩子存在但值不是父值 +1，说明左链断开
                l = 1;  // 只能从自己重新开始计数
            }  // if 块结束
            if (root->right && root->right->val - root->val != 1) {  // 右孩子存在但值不是父值 +1，说明右链断开
                r = 1;  // 同样从自己重新开始计数
            }  // if 块结束
            int t = max(l, r);  // 当前结点往下左右两条路中较长的那条
            ans = max(ans, t);  // 用它更新全局最大值
            return t;  // 把以当前结点为起点的长度返回给上一层
        };  // lambda 定义结束
        dfs(root);  // 从根开始遍历，答案记录在全局变量 ans 里
        return ans;  // 返回最长连续序列长度
    }  // 方法结束
};  // 类定义结束