// 题目：617. 合并二叉树（Merge Two Binary Trees）
// 思路：两棵树同步递归合并；任一侧为空就直接返回另一侧，否则把两节点值相加后递归合并左右子树。
// 时间复杂度：O(min(m, n))，只处理两棵树重叠的节点；空间复杂度：O(min(m, n))，递归栈深度不超过较矮的树。
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
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {  // root1、root2 是两棵待合并树的根节点
        if (!root1) return root2;  // root1 为空：另一棵子树整体搬过来即可，无需再合并
        if (!root2) return root1;  // root2 为空：同理直接复用 root1 的子树
        TreeNode* node = new TreeNode(root1->val + root2->val);  // 两棵树都不空：新建节点存放两值之和，保证不修改原树结构
        node->left = mergeTrees(root1->left, root2->left);  // 左孩子由两棵树的左子树递归合并得到
        node->right = mergeTrees(root1->right, root2->right);  // 右孩子由两棵树的右子树递归合并得到
        return node;  // 返回合并后的子树根，供上层挂接
    }
};