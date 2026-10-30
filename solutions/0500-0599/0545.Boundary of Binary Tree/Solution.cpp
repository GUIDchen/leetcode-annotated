// 题目：545. 二叉树的边界（Boundary of Binary Tree）🔒
// 思路：答案由四段拼成——根、左边界（自顶向下、不含叶子）、全部叶子、右边界（逆序，即自底向上），用一次 DFS 分别按 i=0/1/2 三种模式收集。
// 时间复杂度：O(n)，每个节点只被一种模式访问一次；空间复杂度：O(h)，递归栈深度等于树高（不含答案数组）。
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
    vector<int> boundaryOfBinaryTree(TreeNode* root) {  // root 是二叉树根节点，返回逆时针排列的边界节点值
        auto dfs = [&](this auto&& dfs, vector<int>& nums, TreeNode* root, int i) -> void {  // C++23 显式对象参数 this auto&& dfs：让 lambda 内部可以递归调用自己
            if (!root) {  // 空节点直接返回，避免解引用空指针
                return;  // 递归出口
            }  // 结束空节点判断
            if (i == 0) {  // 模式 0：自顶向下收集左边界（不含叶子）
                if (root->left != root->right) {  // 左右指针不同即为真，说明当前节点不是叶子（叶子的两个指针都为空）
                    nums.push_back(root->val);  // 记录这个左边界节点
                    if (root->left) {  // 有左孩子就优先沿左边继续向下
                        dfs(nums, root->left, i);  // 递归处理左子树
                    } else {  // 没有左孩子，只能改走右孩子
                        dfs(nums, root->right, i);  // 沿右孩子继续收集左边界
                    }  // 结束 else 分支
                }  // 结束模式 0 的「非叶子」判断
            } else if (i == 1) {  // 模式 1：收集全部叶子节点（从根开始遍历整棵树）
                if (root->left == root->right) {  // 两个指针都为空，说明是叶子
                    nums.push_back(root->val);  // 记录叶子节点的值
                } else {  // 不是叶子就继续往下找
                    dfs(nums, root->left, i);  // 递归左子树找叶子
                    dfs(nums, root->right, i);  // 递归右子树找叶子
                }  // 结束模式 1 的判断
            } else {  // 模式 2：自顶向下收集右边界（最终整体逆序，得到自底向上）
                if (root->left != root->right) {  // 同样要求不是叶子
                    nums.push_back(root->val);  // 记录这个右边界节点
                    if (root->right) {  // 有右孩子就优先沿右边向下
                        dfs(nums, root->right, i);  // 递归处理右子树
                    } else {  // 没有右孩子则改走左孩子
                        dfs(nums, root->left, i);  // 沿左孩子继续收集右边界
                    }  // 结束 else 分支
                }  // 结束模式 2 的「非叶子」判断
            }  // 结束模式 2
        };  // lambda 定义结束
        vector<int> ans = {root->val};  // 根节点必然在边界上，先放入答案
        if (root->left == root->right) {  // 根同时也是叶子时，边界只有根自己
            return ans;  // 直接返回单元素答案
        }  // 结束「根是叶子」的特判
        vector<int> left, right, leaves;  // 三段边界分别收集：left 左边界、right 右边界、leaves 叶子
        dfs(left, root->left, 0);  // 从根的左孩子开始收集左边界
        dfs(leaves, root, 1);  // 从根开始收集全部叶子
        dfs(right, root->right, 2);  // 从根的右孩子开始收集右边界
        ans.insert(ans.end(), left.begin(), left.end());  // 拼接左边界，保持自顶向下的顺序
        ans.insert(ans.end(), leaves.begin(), leaves.end());  // 拼接叶子序列
        ans.insert(ans.end(), right.rbegin(), right.rend());  // 右边界必须逆序拼接，才符合逆时针方向
        return ans;  // 返回最终边界序列
    }  // 结束 boundaryOfBinaryTree
};  // 类定义结束
