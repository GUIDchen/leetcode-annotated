// 题目：100. 相同的树（Same Tree）
// 思路：同步递归两棵树，比较根值是否相等，再同时递归比较左左、右右两对子树。
// 时间复杂度：O(min(m, n))，最坏遍历全部节点；空间复杂度：O(min(h1, h2))，递归栈深度取决于较浅的树。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x, left), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isSameTree(TreeNode* p, TreeNode* q) {  // p、q：两棵树的根，返回它们结构和值是否完全一致
        if (p == q) return true;  // 指针相同（含同时为 nullptr）说明两边完全相同，直接判真
        if (!p || !q || p->val != q->val) return false;  // 只有一边为空，或根值不同，结构与值必然不一致
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);  // 左子树与右子树分别都必须相同
    }
};