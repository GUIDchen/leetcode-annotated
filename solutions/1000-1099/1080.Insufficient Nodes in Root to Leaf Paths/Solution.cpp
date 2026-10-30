// 题目：1080. 根到叶路径上的不足节点（Insufficient Nodes in Root to Leaf Paths）
// 思路：自顶向下把 limit 递减为「从根走到当前结点后还需要的剩余目标」；遇到叶子时判断剩余目标是否仍大于 0，大于 0 说明这条路径和不足，删掉该叶子；回溯时若某结点的左右孩子都被删光，它自己也不再通向任何合格叶子，同样删除。
// 时间复杂度：O(n)，每个结点只访问一次；空间复杂度：O(h)，h 为树高，递归栈开销。
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
    TreeNode* sufficientSubset(TreeNode* root, int limit) {  // root 是子树根，limit 是当前路径还需要的剩余值
        if (!root) {  // 空结点直接返回，作为递归的边界
            return nullptr;  // 空树没有可删的结点
        }
        limit -= root->val;  // 把当前结点值从剩余目标中扣掉，得到子结点还需达到的剩余值
        if (!root->left && !root->right) {  // 当前结点是叶子，路径和已经确定
            return limit > 0 ? nullptr : root;  // 剩余目标仍大于 0 说明路径和不足，删除该叶子；否则保留
        }
        root->left = sufficientSubset(root->left, limit);  // 递归处理左子树，并把可能被删除的空结果写回左孩子
        root->right = sufficientSubset(root->right, limit);  // 递归处理右子树，并把可能被删除的空结果写回右孩子
        return !root->left && !root->right ? nullptr : root;  // 两个孩子都没了，本结点也就不通向合格叶子，删除；否则保留
    }
};