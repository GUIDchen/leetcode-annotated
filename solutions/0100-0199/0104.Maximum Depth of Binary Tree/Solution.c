// 题目：104. 二叉树的最大深度（Maximum Depth of Binary Tree）
// 思路：递归求左右子树的最大深度，取较大者加 1 即为当前节点为根的最大深度；空节点深度为 0。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高，即递归调用栈的深度。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏定义一个求较大值的函数，注意参数要加括号避免运算符优先级问题

int maxDepth(struct TreeNode* root) {  // root：树根，返回以它为根的树的最大深度（节点数）
    if (!root) {  // 空节点
        return 0;  // 空树深度为 0，作为递归的边界
    }
    int left = maxDepth(root->left);  // 递归求左子树的最大深度
    int right = maxDepth(root->right);  // 递归求右子树的最大深度
    return 1 + max(left, right);  // 当前这一层算 1 层，再加上左右两者中较深的一边
}