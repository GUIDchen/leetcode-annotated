// 题目：538. 把二叉搜索树转换为累加树（Convert BST to Greater Tree）
// 思路：反向中序遍历（右-根-左）恰好按节点值从大到小访问，用累加和 s 边遍历边把节点值改为「大于等于它的所有值之和」。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
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
    int s = 0;  // 成员变量 s 保存「当前已访问过的更大值的累加和」

    TreeNode* convertBST(TreeNode* root) {  // 入口：原地修改整棵树并返回根节点
        dfs(root);  // 反向中序遍历，边遍历边改写节点值
        return root;  // 返回同一个根节点（树结构已被原地修改）
    }

    void dfs(TreeNode* root) {  // 递归函数：按 右子树 → 根 → 左子树 的顺序访问
        if (!root) return;  // 空节点直接返回，作为递归边界
        dfs(root->right);  // 先处理右子树：右子树的值都大于当前节点，必须先累加
        s += root->val;  // 把当前节点值加入累加和，得到「大于等于当前值的所有节点值之和」
        root->val = s;  // 用累加和覆盖原值，完成本题要求的转换
        dfs(root->left);  // 再处理左子树：左子树的值都小于当前节点，此时 s 已包含所有更大值
    }
};