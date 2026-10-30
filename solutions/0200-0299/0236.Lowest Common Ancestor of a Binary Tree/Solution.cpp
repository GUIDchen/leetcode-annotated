// 题目：236. 二叉树的最近公共祖先（Lowest Common Ancestor of a Binary Tree）
// 思路：后序递归，返回「子树中找到的 p 或 q」；左右子树各返回一个非空时，当前结点就是最近公共祖先，否则把非空的一侧往上传递。
// 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(H)，H 为树高，即递归栈深度。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {  // root 是树根，p、q 是待求祖先的两个结点
        if (root == nullptr || root == p || root == q) {  // 空树返回空；当前结点就是 p 或 q 时直接返回它自己（它可能就是答案）
            return root;  // 返回 nullptr，或 p / q 本身
        }  // 递归终止条件判断结束
        auto left = lowestCommonAncestor(root->left, p, q);  // 在左子树中查找，看能否找到 p 或 q
        auto right = lowestCommonAncestor(root->right, p, q);  // 在右子树中查找，看能否找到 p 或 q
        if (left && right) {  // 左右都找到了，说明 p、q 分居两侧，当前结点就是最近公共祖先
            return root;  // 返回当前结点作为答案
        }  // 分居两侧的判断结束
        return left ? left : right;  // 只有一侧找到就把它继续往上传递；都没找到则返回空
    }  // 方法结束
};  // 题解类结束