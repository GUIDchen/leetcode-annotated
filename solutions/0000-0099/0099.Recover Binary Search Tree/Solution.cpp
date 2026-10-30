// 题目：99. 恢复二叉搜索树（Recover Binary Search Tree）
// 思路：中序遍历 BST 得到递增序列，被交换的两个节点会让序列出现一到两处逆序；记录逆序对中的节点再交换值。
// 时间复杂度：O(n)，每个节点遍历一次；空间复杂度：O(h)，h 为树高，即递归栈深度。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x, left), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void recoverTree(TreeNode* root) {  // root：被错误交换了两个节点值的 BST 根，原地修复
        TreeNode* prev = nullptr;  // 中序遍历的前驱节点，用于发现逆序
        TreeNode* first = nullptr;  // 记录第一个需要交换的节点
        TreeNode* second = nullptr;  // 记录第二个需要交换的节点
        function<void(TreeNode * root)> dfs = [&](TreeNode* root) {  // 递归 lambda：中序遍历整棵树
            if (!root) return;  // 空节点直接返回
            dfs(root->left);  // 先完整遍历左子树
            if (prev && prev->val > root->val) {  // 严格递增序列中出现了逆序，说明涉及被交换的节点
                if (!first) first = prev;  // 第一处逆序的较大者就是第一个错误节点，只记录一次
                second = root;  // 较小者记为第二个错误节点；持续覆盖可兼容两节点相邻和不相邻两种情况
            }
            prev = root;  // 把当前节点更新为前驱，继续向右遍历
            dfs(root->right);  // 再完整遍历右子树
        };
        dfs(root);  // 一次中序遍历找出两个被交换的节点
        swap(first->val, second->val);  // 交换两个节点的值即完成恢复，不改变树结构
    }
};