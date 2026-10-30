// 题目：872. 叶子相似的树（Leaf-Similar Trees）
// 思路：分别对两棵树做 DFS，按「左子树 → 右子树」的顺序收集叶子值，再比较两个序列是否完全相同。
// 时间复杂度：O(n + m)，各遍历一棵树一次；空间复杂度：O(n + m)，存放两个叶子序列（递归栈另计 O(树高)）。
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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {  // root1、root2 是两棵二叉树的根，判断它们的叶子值序列是否相同
        vector<int> l1, l2;  // l1、l2 分别收集两棵树的叶子值序列
        dfs(root1, l1);  // 深度优先遍历第一棵树，从左到右记录叶子值
        dfs(root2, l2);  // 深度优先遍历第二棵树，同样从左到右记录叶子值
        return l1 == l2;  // 两个序列完全相同即为叶子相似
    }  // 方法结束

    void dfs(TreeNode* root, vector<int>& nums) {  // 辅助函数：按从左到右的顺序把叶子节点的值追加到 nums
        if (root->left == root->right) {  // 左右孩子都为空（两个 nullptr 相等）说明当前节点是叶子
            nums.push_back(root->val);  // 记录这个叶子节点的值
            return;  // 叶子处理完立即返回，不再往下递归
        }
        if (root->left) {  // 左孩子存在就继续递归左子树
            dfs(root->left, nums);  // 先递归左子树，保证左子树的叶子排在右子树之前
        }
        if (root->right) {  // 右孩子存在就继续递归右子树
            dfs(root->right, nums);  // 再递归右子树，使序列顺序为从左到右
        }
    }  // 辅助函数结束
};  // 题解类定义结束
