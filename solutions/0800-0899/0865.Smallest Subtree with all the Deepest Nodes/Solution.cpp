// 题目：865. 具有所有最深节点的最小子树（Smallest Subtree with all the Deepest Nodes）
// 思路：后序 DFS 返回「包含子树中所有最深结点的最小子树根, 该子树高度」。左右高度不同则答案在更深一侧，相同则答案就是当前结点。
// 时间复杂度：O(n)，每个结点只访问一次；空间复杂度：O(n)，递归栈最坏为链状树的深度。
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
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {  // root：二叉树根；返回包含所有最深结点的最小子树的根
        using pti = pair<TreeNode*, int>;  // 别名 pti：子树答案根 + 该子树的高度
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> pti {  // 后序 DFS：返回 (包含最深结点的子树根, 该子树高度)
            if (!root) {  // 空结点没有最深结点
                return {nullptr, 0};  // 空子树高度记为 0
            }  // if 分支结束
            auto [l, ld] = dfs(root->left);  // 递归左子树，得到左边的候选根与高度
            auto [r, rd] = dfs(root->right);  // 递归右子树，得到右边的候选根与高度
            if (ld > rd) {  // 左子树更深
                return {l, ld + 1};  // 最深结点全在左边，答案继承左边，高度再加一
            }  // if 分支结束
            if (ld < rd) {  // 右子树更深
                return {r, rd + 1};  // 最深结点全在右边，答案继承右边，高度再加一
            }  // if 分支结束
            return {root, ld + 1};  // 两边一样深，最深结点分布在两侧，当前结点才是最小公共根
        };  // dfs 闭包定义结束
        return dfs(root).first;  // 取 pair 的第一个元素，即最小子树的根
    }  // subtreeWithAllDeepest 方法结束
};  // Solution 类定义结束
