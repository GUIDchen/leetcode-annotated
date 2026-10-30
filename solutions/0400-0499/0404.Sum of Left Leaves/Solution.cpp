// 题目：404. 左叶子之和（Sum of Left Leaves）
// 思路：后序递归。右子树的左叶子递归统计；左孩子单独判断，是叶子就取它的值，不是就继续递归下去。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度为树高 h。
// TreeNode 的定义由判题器提供，这里注释形式列出了构造函数，类中无需再定义
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
public:  // 方法对外可见
    int sumOfLeftLeaves(TreeNode* root) {  // 求二叉树中所有「左叶子」节点值之和
        if (!root) {  // 空节点没有贡献
            return 0;  // 返回 0
        }
        int ans = sumOfLeftLeaves(root->right);  // 先统计右子树中的左叶子（右孩子自身不是左叶子）
        if (root->left) {  // 有左孩子时才需要判断它是不是叶子
            if (!root->left->left && !root->left->right) {  // 左孩子没有左右子树，说明它是叶子
                ans += root->left->val;  // 是左叶子，把它的值累加进答案
            } else {  // 否则左孩子不是叶子
                ans += sumOfLeftLeaves(root->left);  // 继续递归到左子树里找左叶子
            }
        }
        return ans;  // 返回总和
    }
};  // 题解类结束
