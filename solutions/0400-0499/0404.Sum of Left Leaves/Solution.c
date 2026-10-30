// 题目：404. 左叶子之和（Sum of Left Leaves）
// 思路：后序递归。右子树里的左叶子照常递归统计；左孩子只单独判断，若它是叶子就直接取值，否则继续往下递归。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
// 结构体定义由判题器提供，这里只是注释形式给出 TreeNode 的字段：val、left、right
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int sumOfLeftLeaves(struct TreeNode* root) {  // 求二叉树中所有「左叶子」节点值之和
    if (!root) {  // 空节点没有任何贡献
        return 0;  // 返回 0
    }
    int ans = sumOfLeftLeaves(root->right);  // 右子树里的左叶子递归统计（右孩子本身不属于左叶子）
    if (root->left) {  // 存在左孩子时，单独判断它是不是叶子
        if (!root->left->left && !root->left->right) {  // 左孩子既无左子树也无右子树，说明它是一个叶子
            ans += root->left->val;  // 是左叶子，直接把它的值累加进答案
        } else {  // 否则左孩子不是叶子
            ans += sumOfLeftLeaves(root->left);  // 继续往左子树里递归，找更深处的左叶子
        }
    }
    return ans;  // 返回累加好的总和
}