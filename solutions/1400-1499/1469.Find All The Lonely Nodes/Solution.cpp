// 题目：1469. 寻找所有的独生节点（Find All The Lonely Nodes）
// 核心思路：DFS 遍历整棵树，若某节点只有一个孩子，就把这个唯一孩子的值加入答案。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高。
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
    vector<int> getLonelyNodes(TreeNode* root) {  // root 是二叉树根节点，返回所有独生节点的值
        vector<int> ans;  // 收集独生节点的值
        auto dfs = [&](this auto&& dfs, TreeNode* root) {  // C++23 的显式对象参数写法：用 this auto&& dfs 让 lambda 能递归调用自身
            if (!root || (root->left == root->right)) {  // 空节点直接返回；左右指针相等说明两个孩子都不存在（叶子），也没有独生节点
                return;  // 结束本层递归
            }  // 出口判断结束
            if (!root->left) {  // 只有右孩子
                ans.push_back(root->right->val);  // 右孩子是独生节点，记录它的值
            }  // 分支一结束
            if (!root->right) {  // 只有左孩子
                ans.push_back(root->left->val);  // 左孩子是独生节点，记录它的值
            }  // 分支二结束
            dfs(root->left);  // 递归处理左子树
            dfs(root->right);  // 递归处理右子树
        };  // lambda 定义结束
        dfs(root);  // 从根开始遍历
        return ans;  // 返回结果
    }  // 方法结束
};  // 类定义结束
