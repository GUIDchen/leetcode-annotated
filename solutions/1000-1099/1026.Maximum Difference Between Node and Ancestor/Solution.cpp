// 题目：1026. 节点与其祖先之间的最大差值（Maximum Difference Between Node and Ancestor）
// 思路：DFS 一路往下传「从根到父节点路径上的最小值 mi 与最大值 mx」，在当前节点处用 mi、mx 与它自己作差更新答案。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，h 为树高，来自递归栈。
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
// 上面的 TreeNode 定义由 LeetCode 判题器注入，代码中直接使用
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxAncestorDiff(TreeNode* root) {  // root 是二叉树根；返回任意祖先与后代节点值之差绝对值的最大值
        int ans = 0;  // 答案：记录目前见过的最大差值
        function<void(TreeNode*, int, int)> dfs = [&](TreeNode* root, int mi, int mx) {  // 递归 lambda：root 为当前节点，mi/mx 是从根到父节点路径上的最小值和最大值
            if (!root) {  // 空节点直接返回
                return;  // 无节点可比较，结束这一分支
            }
            ans = max({ans, abs(mi - root->val), abs(mx - root->val)});  // 当前节点与祖先中的最小值、最大值分别作差，取三者最大来更新答案
            mi = min(mi, root->val);  // 把当前节点也纳入路径最小值，供子节点使用
            mx = max(mx, root->val);  // 把当前节点也纳入路径最大值，供子节点使用
            dfs(root->left, mi, mx);  // 左子树继续带着更新后的 mi、mx 往下走
            dfs(root->right, mi, mx);  // 右子树同理
        };
        // 根节点没有祖先，mi 与 mx 都初始化为根的值（根与自身差为 0）
        dfs(root, root->val, root->val);  // 从根开始 DFS
        return ans;  // 返回最大差值
    }
};