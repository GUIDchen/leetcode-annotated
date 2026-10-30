// 题目：998. 最大二叉树 II（Maximum Binary Tree II）
// 思路：val 是追加在构造序列末尾的值，因此它只会落在根或右链上：递归下行右子树，遇到空位或更小的节点就新建节点，并让原树整体作为它的左子树。
// 时间复杂度：O(h)，h 为树高（最坏 O(n)）；空间复杂度：O(h)，递归栈深度。
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
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {  // root：最大二叉树根节点；val：要插入的新值（追加在遍历序列末尾）
        if (!root || root->val < val) return new TreeNode(val, root, nullptr);  // 空树或新值更大：新节点成为根，原树整体作为它的左子树
        root->right = insertIntoMaxTree(root->right, val);  // 否则只能往右子树递归插入，并把结果接回右指针
        return root;  // 根节点不变，直接返回
    }
};