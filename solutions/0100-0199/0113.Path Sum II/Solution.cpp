// 题目：113. 路径总和 II（Path Sum II）
// 思路：DFS 回溯，用 t 记录当前路径；进入结点时把值入栈、目标值减去它；到叶子且差值归零就复制一份路径存入答案，返回时弹栈。
// 时间复杂度：O(n^2)，最坏每条路径都要复制一次；空间复杂度：O(h)，h 为树高，结果本身另算。
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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {  // root 是树根，targetSum 是目标和，返回所有满足条件的路径
        vector<vector<int>> ans;  // 收集所有答案，每个答案是一条路径（一维数组）
        vector<int> t;  // 当前正在走的路径（回溯用的栈）
        function<void(TreeNode*, int)> dfs = [&](TreeNode* root, int s) {  // 递归 lambda：root 是当前结点，s 是「还差多少」的目标值
            if (!root) return;  // 空结点直接返回
            s -= root->val;  // 减去当前结点值，剩下的就是子树需要凑出的和
            t.emplace_back(root->val);  // 把当前结点值压入路径栈
            if (!root->left && !root->right && s == 0) ans.emplace_back(t);  // 叶子结点且差值恰好为 0，说明这条路径符合要求
            dfs(root->left, s);  // 继续往左子树找
            dfs(root->right, s);  // 继续往右子树找
            t.pop_back();  // 回溯：弹出当前结点，恢复路径供兄弟分支使用
        };  // 递归 lambda 定义结束
        dfs(root, targetSum);  // 从根开始，目标值就是 targetSum
        return ans;  // 返回所有找到的路径
    }  // 方法结束
};  // 题解类结束