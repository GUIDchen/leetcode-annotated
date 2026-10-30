// 题目：1430. 判断给定的序列是否是二叉树从根到叶的路径（Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree）
// 思路：从根开始按 arr 逐步向下匹配，值不等即剪枝；匹配完 arr 的最后一个元素时必须是叶子节点。
// 时间复杂度：O(n)，最坏访问每个节点一次；空间复杂度：O(h)，递归栈深度为树高。
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
    bool isValidSequence(TreeNode* root, vector<int>& arr) {  // 判断是否存在一条根到叶路径，其节点值序列恰好等于 arr
        function<bool(TreeNode*, int)> dfs = [&](TreeNode* root, int u) -> bool {  // 递归函数：root 是当前节点，u 是 arr 中待匹配的下标；用 std::function 便于在 lambda 内调用自身
            if (!root || root->val != arr[u]) return false;  // 节点为空或值不匹配，这条路径立刻失败
            if (u == arr.size() - 1) return !root->left && !root->right;  // 已经匹配到 arr 的最后一个元素：必须同时是叶子（左右子树都空）才算完整路径
            return dfs(root->left, u + 1) || dfs(root->right, u + 1);  // 还没匹配完：左右子节点各自尝试匹配下一个下标，任一成功即可
        };  // lambda 定义结束
        return dfs(root, 0);  // 从根节点、arr 下标 0 开始匹配
    }  // 方法结束
};  // 类定义结束