// 题目：250. 统计同值子树（Count Univalue Subtrees）
// 思路：后序遍历，dfs 返回“以当前节点为根的子树是否同值”，同时用外层引用计数器累加同值子树的个数。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高（递归栈深度）。
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
public:  // 成员函数对外可见
    int countUnivalSubtrees(TreeNode* root) {  // root：二叉树根节点，返回同值子树的数量
        int ans = 0;  // 同值子树计数器，被 dfs 以引用方式捕获并累加
        function<bool(TreeNode*)> dfs = [&](TreeNode* root) -> bool {  // dfs：判断以 root 为根的子树内所有节点值是否相同
            if (!root) {  // 空树按题面约定视为同值
                return true;  // 空节点直接返回真
            }  // 结束空节点判断
            bool l = dfs(root->left);  // 先递归判断左子树是否同值
            bool r = dfs(root->right);  // 再递归判断右子树是否同值
            if (!l || !r) {  // 任一子树不同值，当前子树必然也不同值
                return false;  // 直接返回假
            }  // 结束子树同值判断
            int a = root->left ? root->left->val : root->val;  // 左孩子存在则取其值，否则用当前值占位（表示没有额外约束）
            int b = root->right ? root->right->val : root->val;  // 右孩子同理取占位值
            if (a == b && b == root->val) {  // 左右孩子的值都与当前值相同，说明整棵子树同值
                ++ans;  // 计为一个同值子树
                return true;  // 向父节点汇报本子树同值
            }  // 结束同值判断
            return false;  // 值不相同，不是同值子树
        };  // lambda 定义结束
        dfs(root);  // 触发后序遍历，计数在递归过程中完成
        return ans;  // 返回统计结果
    }  // 结束 countUnivalSubtrees 方法
};  // 结束 Solution 类