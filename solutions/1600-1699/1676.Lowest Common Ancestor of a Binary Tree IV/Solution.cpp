// 题目：1676. 二叉树的最近公共祖先 IV（Lowest Common Ancestor of a Binary Tree IV）
// 思路：把目标节点的值放进哈希集合，自底向上 DFS：遇到空或集合中的节点就返回它，左右子树都返回非空则当前节点即最近公共祖先。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，集合与递归栈最深均为 n。
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
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*>& nodes) {  // root：二叉树根；nodes：需要求公共祖先的目标节点列表
        unordered_set<int> s;  // 哈希集合，存放所有目标节点的值，便于 O(1) 判断
        for (auto node : nodes) {  // 遍历目标节点列表
            s.insert(node->val);  // 把目标节点的值加入集合
        }  // 遍历结束
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> TreeNode* {  // C++23 的递归 lambda：this auto&& dfs 让 lambda 可以调用自身
            if (!root || s.contains(root->val)) {  // 空节点或命中目标节点，直接返回当前节点（或空）
                return root;  // 返回 root 本身（可能为 nullptr）
            }  // if 结束
            auto left = dfs(root->left);  // 递归处理左子树
            auto right = dfs(root->right);  // 递归处理右子树
            if (!left) {  // 左子树没有目标节点，答案全在右子树
                return right;  // 返回右子树的结果
            }  // if 结束
            if (!right) {  // 右子树没有目标节点，答案全在左子树
                return left;  // 返回左子树的结果
            }  // if 结束
            return root;  // 左右子树各找到至少一个目标节点，当前节点就是最近公共祖先
        };  // lambda 定义结束
        return dfs(root);  // 从根节点开始搜索并返回结果
    }  // 方法结束
};  // 类定义结束
