// 题目：563. 二叉树的坡度（Binary Tree Tilt）
// 思路：后序遍历求每个子树的节点和，同时把「左子树和与右子树和之差的绝对值」累加到全局答案，并把当前子树节点和返回给父节点。
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
    int findTilt(TreeNode* root) {  // root 是二叉树根节点，返回整棵树所有节点坡度之和
        int ans = 0;  // ans 累计所有节点的坡度（左右子树节点和之差的绝对值）
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> int {  // C++23 显式对象形参递归 lambda：参数 dfs 指向自身，返回值是子树节点和
            if (!root) {  // 空节点既无节点和也无坡度，直接跳过
                return 0;  // 空子树节点和为 0
            }  // 空节点处理结束
            int l = dfs(root->left), r = dfs(root->right);  // 先递归求左右子树的节点和（后序位置）
            ans += abs(l - r);  // 当前节点坡度 = |左子树和 - 右子树和|，累加到答案
            return l + r + root->val;  // 向上返回以当前节点为根的整棵子树节点和
        };  // lambda 定义结束
        dfs(root);  // 从根节点开始遍历，填充 ans
        return ans;  // 返回所有节点坡度之和
    }  // 方法结束
};
