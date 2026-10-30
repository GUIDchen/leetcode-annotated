// 题目：222. 完全二叉树的节点个数（Count Complete Tree Nodes）
// 思路：后序递归统计。空节点贡献 0，其余节点贡献 1 + 左子树节点数 + 右子树节点数。
// 时间复杂度：O(n)，每个节点恰好访问一次；空间复杂度：O(h)，递归栈深度为树高，最坏 O(n)。
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
    int countNodes(TreeNode* root) {  // root：完全二叉树的根节点；返回以 root 为根的子树节点个数
        if (!root) {  // 空节点说明已经走到叶子之外，作为递归出口
            return 0;  // 空子树没有节点，贡献 0
        }
        return 1 + countNodes(root->left) + countNodes(root->right);  // 根节点自身 1 个 + 左子树节点数 + 右子树节点数
    }
};