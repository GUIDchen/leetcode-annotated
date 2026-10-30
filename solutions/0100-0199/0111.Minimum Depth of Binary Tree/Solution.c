// 题目：111. 二叉树的最小深度（Minimum Depth of Binary Tree）
// 思路：递归。空结点深度为 0；只有一个孩子时必须沿那个孩子继续走（叶子才终止）；两个孩子都在才取较小值加一。
// 时间复杂度：O(n)，最坏访问每个结点一次；空间复杂度：O(h)，h 为树高，即递归栈深度。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define min(a, b) (((a) < (b)) ? (a) : (b))  // 宏定义取两个值中的较小者，省去额外头文件依赖

int minDepth(struct TreeNode* root) {  // 返回以 root 为根的子树最小深度（根到最近叶子经过的结点数）
    if (!root) {  // 空结点没有深度
        return 0;  // 空子树深度为 0
    }  // 空结点处理完毕
    if (!root->left) {  // 没有左孩子，最小深度只能沿右子树往下走
        return 1 + minDepth(root->right);  // 只有右子树时，深度是右子树深度加一
    }  // 左孩子判断结束
    if (!root->right) {  // 没有右孩子，最小深度只能沿左子树往下走
        return 1 + minDepth(root->left);  // 只有左子树时，深度是左子树深度加一
    }  // 右孩子判断结束
    int left = minDepth(root->left);  // 左右孩子都存在：分别求两侧最小深度
    int right = minDepth(root->right);  // 右侧最小深度
    return 1 + min(left, right);  // 取较小者再加一（加的是当前这一层）
}  // 函数结束