// 题目：1973. 值等于子节点值之和的节点数量（Count Nodes Equal to Sum of Descendants）
// 思路：后序 DFS，函数返回整棵子树的节点值之和；回传前顺便判断左右子树之和是否等于当前节点值，相等就给计数器加一。
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
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int equalToDescendants(TreeNode* root) {  // root：二叉树根节点；返回满足条件的节点个数
        int ans = 0;  // 计数器：值恰好等于所有后代值之和的节点个数
        function<long long(TreeNode*)> dfs = [&](TreeNode* root) -> long long {  // 返回以 root 为根的子树中所有节点值之和
            if (!root) {  // 空节点没有值
                return 0;  // 空子树的节点值之和约定为 0
            }
            auto l = dfs(root->left);  // 递归求左子树的节点值之和（用 long long 防止累加溢出）
            auto r = dfs(root->right);  // 递归求右子树的节点值之和
            ans += l + r == root->val;  // 左右子树之和就是全部后代之和，等于当前节点值时比较结果 1 累加到计数
            return root->val + l + r;  // 向上回传整棵子树的节点值之和
        };
        dfs(root);  // 从根开始遍历，计数在遍历过程中完成
        return ans;  // 返回满足条件的节点个数
    }
};
