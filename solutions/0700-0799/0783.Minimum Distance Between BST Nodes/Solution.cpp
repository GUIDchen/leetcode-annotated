// 题目：783. 二叉搜索树节点最小距离（Minimum Distance Between BST Nodes）
// 思路：二叉搜索树的中序遍历得到严格递增的序列，任意两节点差的最小值一定出现在中序序列的相邻两项之间；递归时用 pre 记住前驱节点的值，边走边更新答案。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高，最坏 O(n)。
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
class Solution {  // LeetCode 约定的题解类（上方注释是题目给出的 TreeNode 定义）
public:  // 题解方法对外可见
    int minDiffInBST(TreeNode* root) {  // root：BST 根节点；返回任意两个不同节点值的最小差值
        const int inf = 1 << 30;  // inf：充当无穷大，1<<30 足够大又不会溢出 int
        int ans = inf, pre = -inf;  // ans 记录最小差值；pre 记录中序前一个节点的值，初值 -inf 让第一次做差得到极大值
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> void {  // 递归 lambda：中序遍历，用 C++23 的 this auto&& 让 lambda 能调用自身
            if (!root) {  // 空节点直接返回，作为递归出口
                return;  // 结束本层递归
            }
            dfs(root->left);  // 先递归左子树：中序保证按值从小到大访问
            ans = min(ans, root->val - pre);  // 当前值与中序前驱值相邻，用它们的差更新最小距离
            pre = root->val;  // 当前节点成为下一轮的前驱
            dfs(root->right);  // 再递归右子树
        };
        dfs(root);  // 从根节点开始中序遍历
        return ans;  // 返回最小差值
    }  // minDiffInBST 方法结束
};  // Solution 类定义结束
