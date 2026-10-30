// 题目：1022. 从根到叶的二进制数之和（Sum of Root To Leaf Binary Numbers）
// 思路：DFS 时用参数 x 累积「从根走到当前节点」的二进制值（左移一位再或上当前位），走到叶子就把 x 返回并逐层相加。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，h 为树高，来自递归调用栈。
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
// 上面的 TreeNode 定义由 LeetCode 判题器注入，代码中直接使用
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumRootToLeaf(TreeNode* root) {  // root 是 01 二叉树的根；返回所有根到叶路径所表示二进制数之和
        auto dfs = [&](this auto&& dfs, TreeNode* root, int x) -> int {  // C++23 推导 this 的递归 lambda：root 为当前节点，x 为从根到父节点已累积的数值
            if (!root) {  // 空节点不构成路径，直接剪枝
                return 0;  // 返回 0，使父节点的加法不受影响
            }
            x = x << 1 | root->val;  // 左移一位腾出最低位，再按位或填入当前节点的二进制位
            if (root->left == root->right) {  // 左右指针相等说明二者同为 nullptr，即当前节点是叶子
                return x;  // 一条完整路径结束，它代表的二进制数就是 x
            }
            return dfs(root->left, x) + dfs(root->right, x);  // 非叶子节点：左右子树的路径和相加
        };
        // 从根节点出发，累积值初始为 0
        return dfs(root, 0);  // 启动 DFS
    }
};
