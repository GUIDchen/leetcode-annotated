// 题目：652. 寻找重复的子树（Find Duplicate Subtrees）
// 思路：后序遍历把每棵子树序列化成「根值,左子树串,右子树串」，用哈希表统计每种形态出现的次数，第二次出现时把该子树的根加入答案。
// 时间复杂度：O(n^2)，最坏情况下字符串拼接与哈希比较达到 O(n)；空间复杂度：O(n^2)，哈希表保存了全部子树的序列化串。

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
    unordered_map<string, int> counter;  // 子树序列化串 → 该形态出现的次数
    vector<TreeNode*> ans;  // 收集重复子树的根节点，每种形态只收一次

    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {  // root 是整棵树根，返回所有重复子树的根节点
        dfs(root);  // 一次后序遍历即可同时填满 counter 与 ans
        return ans;  // 返回收集到的重复子树根节点
    }

    string dfs(TreeNode* root) {  // 返回以 root 为根的子树的序列化串
        if (!root) return "#";  // 空节点用 # 占位，保证不同形态不会序列化成同一字符串
        string v = to_string(root->val) + "," + dfs(root->left) + "," + dfs(root->right);  // 先序拼接「根值,左子树串,右子树串」，形态相同必然串相同
        ++counter[v];  // 该子树形态的出现次数加一
        if (counter[v] == 2) ans.push_back(root);  // 恰好在第二次出现时收录，避免同一形态重复加入答案
        return v;  // 把当前子树串回溯给父节点拼接
    }
};