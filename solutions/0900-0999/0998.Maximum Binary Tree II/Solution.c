// 题目：998. 最大二叉树 II（Maximum Binary Tree II）
// 思路：val 是追加在构造序列末尾的值，所以它只会出现在根或右子树中：沿右链下行，遇到空位或比它小的节点就在此处新建节点，并让原树整体作为左子树。
// 时间复杂度：O(h)，h 为树高（最坏 O(n)）；空间复杂度：O(h)，递归栈深度。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* insertIntoMaxTree(struct TreeNode* root, int val) {  // root：最大二叉树的根；val：要插入的新值（位于遍历序列末尾）
    if (!root || root->val < val) {  // 空树，或者新值比当前根还大：新值成为新的根
        struct TreeNode* res = (struct TreeNode*) malloc(sizeof(struct TreeNode));  // 为新节点申请内存
        res->val = val;  // 写入新节点的值
        res->left = root;  // 原树整体挂到左子树（值比 val 小的元素都在它左边）
        res->right = NULL;  // 右子树为空
        return res;  // 返回新建的根节点
    }
    root->right = insertIntoMaxTree(root->right, val);  // val 更小，只能插到右子树里，递归插入后接回右指针
    return root;  // 根节点不变，直接返回
}