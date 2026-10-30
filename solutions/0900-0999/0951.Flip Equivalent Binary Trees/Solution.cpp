// 题目：951. 翻转等价二叉树（Flip Equivalent Binary Trees）
// 思路：递归同时比较两棵树；当前节点值相同后，或用「不交换」的左右子树配对，或用「交换」的配对，任一成立即等价。
// 时间复杂度：O(n)，每个节点至多配对常数次；空间复杂度：O(h)，h 为树高，即递归栈深度。
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
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {  // root1、root2：待比较的两棵树的根
        return dfs(root1, root2);  // 交给递归函数做判定
    }

    bool dfs(TreeNode* root1, TreeNode* root2) {  // 递归比较 root1 与 root2 为根的两棵子树是否翻转等价
        if (root1 == root2 || (!root1 && !root2)) return true;  // 同一指针或同时为空都直接等价，是递归的终止条件
        if (!root1 || !root2 || root1->val != root2->val) return false;  // 只有一个为空，或根值不同，必然不等价
        return (dfs(root1->left, root2->left) && dfs(root1->right, root2->right)) || (dfs(root1->left, root2->right) && dfs(root1->right, root2->left));  // 先试「左右不交换」的配对，再试「左右交换」的配对，任一组成立即返回真
    }
};