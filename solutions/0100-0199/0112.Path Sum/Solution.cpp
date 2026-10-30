// 题目：112. 路径总和（Path Sum）
// 思路：DFS 自根向下累加路径和，走到叶子时比较是否等于 targetSum，任意一条成立即返回 true。
// 时间复杂度：O(n)，最坏访问每个结点一次；空间复杂度：O(h)，h 为树高，即递归栈深度。
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
    bool hasPathSum(TreeNode* root, int targetSum) {  // root 是树根，targetSum 是目标路径和，返回是否存在这样的根到叶子路径
        function<bool(TreeNode*, int)> dfs = [&](TreeNode* root, int s) -> int {  // 递归 lambda：返回类型写成 int，靠 bool 隐式转换成 0/1，不影响结果
            if (!root) return false;  // 空结点不可能构成路径
            s += root->val;  // 把当前结点值累加进路径和（s 是值传递，不会污染兄弟分支）
            if (!root->left && !root->right && s == targetSum) return true;  // 叶子结点且路径和正好等于目标，说明找到了一条路径
            return dfs(root->left, s) || dfs(root->right, s);  // 还没到叶子，就在左右子树里继续找，任意一侧成功即可
        };  // 递归 lambda 定义结束
        return dfs(root, 0);  // 从根开始，初始路径和为 0
    }  // 方法结束
};  // 题解类结束