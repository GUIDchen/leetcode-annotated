// 题目：2236. 判断根结点是否等于子结点之和（Root Equals Sum of Children）
// 思路：题目保证只有三个结点，直接比较根结点值与左右孩子值之和。
// 时间复杂度：O(1)；空间复杂度：O(1)。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool checkTree(struct TreeNode* root) {  // root 为根结点，返回根值是否等于左右孩子值之和
    return root->val == root->left->val + root->right->val;  // 比较根结点值与两个子结点值之和
}  // 结束 checkTree 函数