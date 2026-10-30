// 题目：653. 两数之和 IV - 输入二叉搜索树（Two Sum IV - Input is a BST）
// 思路：DFS 遍历整棵树并用哈希集合记录已见过的节点值，对每个节点检查 k - 当前值是否已在集合中，命中即说明存在一对和为 k。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，哈希集合最多存 n 个节点值（递归栈另计 O(h)）。

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
    bool findTarget(TreeNode* root, int k) {  // root 是树根，k 是目标和，判断是否存在两个节点值之和为 k
        unordered_set<int> vis;  // 记录 DFS 过程中已经访问过的节点值

        function<bool(TreeNode*)> dfs = [&](TreeNode* root) {  // 递归 lambda：判断能否在剩余节点中找到配对
            if (!root) {  // 空节点没有值可以配对
                return false;  // 该分支失败
            }
            if (vis.count(k - root->val)) {  // 之前访问过补数 k - 当前值，说明这一对已经凑齐
                return true;  // 已找到答案，立即返回
            }
            vis.insert(root->val);  // 把当前值加入集合，供后续节点查询
            return dfs(root->left) || dfs(root->right);  // 左右子树任一侧找到即算成功
        };
        return dfs(root);  // 从整棵树的根开始搜索
    }
};