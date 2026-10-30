// 题目：1379. 找出克隆二叉树中的相同节点（Find a Corresponding Node of a Binary Tree in a Clone of That Tree）
// 思路：两棵结构相同的树同步 DFS 遍历，原树走到 target 时，克隆树上同一位置的结点就是要返回的答案。
// 时间复杂度：O(n)，最坏要访问全部结点；空间复杂度：O(h)，递归栈深度等于树高 h。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {  // original 为原树根，cloned 为克隆树根，target 是原树中要找的结点
        function<TreeNode*(TreeNode*, TreeNode*)> dfs = [&](TreeNode* root1, TreeNode* root2) -> TreeNode* {  // 递归 lambda：在两棵结构相同的树上同步下探，返回克隆树中与 target 对应的结点
            if (root1 == nullptr) {  // 原树为空说明这一支已经走到底
                return nullptr;  // 返回空表示该分支没有找到
            }  // 空结点分支结束
            if (root1 == target) {  // 原树中遇到了目标结点
                return root2;  // 克隆树上位置相同的结点就是答案
            }  // 目标结点判断结束
            TreeNode* left = dfs(root1->left, root2->left);  // 先在左子树同步查找
            return left == nullptr ? dfs(root1->right, root2->right) : left;  // 左子树没找到再去右子树找（三目运算符保证只返回一个结果）
        };  // lambda 定义结束
        return dfs(original, cloned);  // 从两棵树的根开始同步遍历
    }  // 方法结束
};  // 类定义结束