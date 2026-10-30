// 3997. 统计二叉树中支配节点的数量 / Count Dominant Nodes in a Binary Tree（中等）
// 核心思路：后序 DFS 让每棵子树返回自身最大值，节点值若等于「左子树最大值、右子树最大值、自身值」三者的最大者，它就是支配节点；空子树用 INT_MIN 表示「没有节点」。
// 复杂度：时间 O(n)，每个节点只访问一次；空间 O(h)，递归栈深度等于树高。
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
class Solution {  // 题解类
public:  // 公有接口
    int countDominantNodes(TreeNode* root) {  // 返回支配节点的数量
        int ans = 0;  // 支配节点计数器
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> int {  // 后序 DFS：返回以 node 为根的子树中所有节点值的最大值
            if (!node) {  // 空节点
                return INT_MIN;  // 空子树没有节点，用极小值充当最大值
            }  // if 结束
            int l = dfs(node->left);  // 左子树的最大值
            int r = dfs(node->right);  // 右子树的最大值
            int mx = max({l, r, node->val});  // 整棵子树的最大值
            if (mx == node->val) {  // 自身值不小于子树内其它节点，说明它是支配节点
                ++ans;  // 计数加一
            }  // if 结束
            return mx;  // 把子树最大值交给父节点
        };  // lambda 定义结束
        dfs(root);  // 从根节点开始遍历
        return ans;  // 返回支配节点数量
    }  // 方法结束
};  // 类定义结束