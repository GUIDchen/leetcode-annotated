// 题目：1325. 删除给定值的叶子节点（Delete Leaves With a Given Value）
// 思路：后序遍历。先递归删除左右子树中值为 target 的叶子，回溯到当前节点时若它变成叶子且值等于 target，就把自己删掉（返回 nullptr）。
// 时间复杂度：O(N)，每个节点只访问一次；空间复杂度：O(H)，递归栈深度为树高。
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
class Solution {  // 题解类
public:  // 对外暴露题解接口
    TreeNode* removeLeafNodes(TreeNode* root, int target) {  // root：树根；target：要被删除的叶子值
        if (!root) {  // 递归边界：空节点直接返回
            return nullptr;  // 空树（或越过叶子）没有节点可删
        }  // 边界判断结束
        root->left = removeLeafNodes(root->left, target);  // 先处理左子树：子树返回的新根重新挂到 left 上
        root->right = removeLeafNodes(root->right, target);  // 再处理右子树：子树返回的新根重新挂到 right 上
        if (!root->left && !root->right && root->val == target) {  // 左右子树都空了且自己的值等于 target，说明当前节点变成了要删的叶子
            return nullptr;  // 删除当前节点，向父节点返回空
        }  // 判断分支结束
        return root;  // 否则保留当前节点
    }  // 方法结束
};  // 类定义结束