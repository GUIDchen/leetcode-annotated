// 题目：450. 删除二叉搜索树中的节点（Delete Node in a BST）
// 思路：按 BST 的有序性递归定位 key；命中后用「右子树最小值（中序后继）」顶替，并把原左子树挂到后继的左指针上。
// 时间复杂度：O(h)，h 为树高，最坏退化成链表为 O(n)；空间复杂度：O(h)，递归调用栈。
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
    TreeNode* deleteNode(TreeNode* root, int key) {  // root：BST 根结点；key：要删除的值；返回删除后的（可能换过根的）子树根
        if (!root) return root;  // 空树或没找到该值：原样返回空指针
        if (root->val > key) {  // key 比当前值小，它只可能出现在左子树里
            root->left = deleteNode(root->left, key);  // 递归删除左子树中的 key，并把新的左子树根接回来
            return root;  // 当前根的值不受影响，直接返回
        }  // 结束「去左子树删除」的分支
        if (root->val < key) {  // key 比当前值大，它只可能出现在右子树里
            root->right = deleteNode(root->right, key);  // 递归删除右子树中的 key，并把新的右子树根接回来
            return root;  // 当前根的值不受影响，直接返回
        }  // 结束「去右子树删除」的分支
        if (!root->left) return root->right;  // 命中结点且没有左孩子：直接让右孩子顶替（右孩子可以为空）
        if (!root->right) return root->left;  // 只有左孩子：直接让左孩子顶替
        TreeNode* node = root->right;  // 两个孩子都存在：先去右子树找最小的结点（中序后继）
        while (node->left) node = node->left;  // 沿左链一路向下，停下时 node 就是右子树的最小值
        node->left = root->left;  // 把原左子树挂到后继的左指针上，这样整棵树仍然满足 BST 有序性
        root = root->right;  // 后继所在的右子树顶替被删结点，成为新的子树根
        return root;  // 返回新的子树根
    }  // 结束 deleteNode
};  // 结束 Solution 类