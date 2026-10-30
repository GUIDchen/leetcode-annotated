// 题目：235. 二叉搜索树的最近公共祖先（Lowest Common Ancestor of a Binary Search Tree）
// 思路：利用 BST 的大小关系，从根往下走；若当前值比两个目标都小就去右子树，都比它大就去左子树，介于两者之间时当前结点就是分叉点。
// 时间复杂度：O(H)，H 为树高（最坏 O(n)）；空间复杂度：O(1)，只用了常数个指针。
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {  // root 是 BST 根结点，p、q 是待求祖先的两个结点
        while (1) {  // 一直向下走，直到找到分叉点
            if (root->val < min(p->val, q->val)) {  // 当前值比两个目标都小，说明祖先在右子树（右子树的值更大）
                root = root->right;  // 向右子树走
            } else if (root->val > max(p->val, q->val)) {  // 当前值比两个目标都大，说明祖先在左子树
                root = root->left;  // 向左子树走
            } else {  // 否则当前值介于两者之间（或等于其中之一），它就是分叉点
                return root;  // 当前结点即最近公共祖先
            }  // 分支结束
        }  // 循环结束
    }  // 方法结束
};  // 题解类结束