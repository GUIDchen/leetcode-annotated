// 题目：700. 二叉搜索树中的搜索（Search in a Binary Search Tree）
// 思路：利用二叉搜索树的有序性，比较目标值与当前结点：相等则命中，目标更小走左子树，更大走右子树，一路向下最多走树高。
// 时间复杂度：O(h)，h 为树高，平均 O(log n)、最坏 O(n)；空间复杂度：O(h)，递归调用栈的深度。
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
    TreeNode* searchBST(TreeNode* root, int val) {  // root 是二叉搜索树根，返回值为 val 的结点（不存在则返回空）
        if (!root || root->val == val) {  // 空树说明没找到；结点值等于目标说明命中
            return root;  // 两种情况都直接返回当前指针（空或目标结点）
        }
        return root->val > val ? searchBST(root->left, val) : searchBST(root->right, val);  // 当前值更大说明目标在左子树，否则在右子树，继续递归
    }
};
