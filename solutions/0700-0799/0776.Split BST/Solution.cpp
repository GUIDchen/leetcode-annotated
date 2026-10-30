// 题目：776. 拆分二叉搜索树（Split BST）
// 核心思路：按 target 递归拆树——根不大于 target 时它属于左半边，递归拆右子树并把其中较大的部分接回根的右侧；否则对称处理左子树。
// 时间复杂度 O(h)，h 为树高；空间复杂度 O(h)，递归栈深度。
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
public:  // 题解方法对判题器可见
    int t;  // 成员变量 t 保存目标值，供递归函数 dfs 直接读取，省去一层参数传递

    vector<TreeNode*> splitBST(TreeNode* root, int target) {  // root：BST 根；target：分界值；返回 {不大于 target 的树, 大于 target 的树}
        t = target;  // 把 target 记到成员变量，递归时逐层读取
        return dfs(root);  // 递归拆分并返回两棵树的根
    }  // 方法结束

    vector<TreeNode*> dfs(TreeNode* root) {  // 递归拆分：返回 ans[0] 为不大于 t 的子树，ans[1] 为大于 t 的子树
        if (!root) return {nullptr, nullptr};  // 空节点拆成两个空树
        if (root->val <= t) {  // 当前根不大于 t，它属于左半边，只需继续拆它的右子树
            auto ans = dfs(root->right);  // 递归拆右子树：ans[0] 是其中仍不大于 t 的部分
            root->right = ans[0];  // 把不大于 t 的那部分接回根的右边，保持 BST 性质
            ans[0] = root;  // 当前根成为左半边的根
            return ans;  // 返回 {左半边根, 右子树中大于 t 的部分}
        } else {  // 当前根大于 t，它属于右半边，继续拆左子树
            auto ans = dfs(root->left);  // 递归拆左子树：ans[1] 是其中大于 t 的部分
            root->left = ans[1];  // 把大于 t 的那部分接回根的左边，保持 BST 性质
            ans[1] = root;  // 当前根成为右半边的根
            return ans;  // 返回 {左子树中不大于 t 的部分, 右半边根}
        }  // if/else 结束
    }  // dfs 结束
};  // 类定义结束