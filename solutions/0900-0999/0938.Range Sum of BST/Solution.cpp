// 题目：938. 二叉搜索树的范围和（Range Sum of BST）
// 思路：利用二叉搜索树的有序性做带剪枝的 DFS —— 当前值大于下界才递归左子树、小于上界才递归右子树，避免访问全部节点。
// 时间复杂度：O(n)，最坏情况访问所有节点；空间复杂度：O(h)，h 为树高，即递归栈的最大深度。
// 下面这段注释是 LeetCode 题面给出的二叉树节点定义，判题器已内置，此处仅作说明。
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
    int rangeSumBST(TreeNode* root, int low, int high) {  // root 是 BST 根节点，low/high 是闭区间上下界，返回区间内所有节点值之和
        function<int(TreeNode*)> dfs = [&](TreeNode* root) {  // 定义递归 lambda（用 function 包装以支持递归）：返回以 root 为根的子树中落在 [low, high] 内的节点值之和
            if (!root) {  // 空节点说明下面没有值可累加
                return 0;  // 空子树对和的贡献为 0
            }
            int x = root->val;  // 当前节点的值，后面要拿它和边界比较
            int ans = low <= x && x <= high ? x : 0;  // 当前值在区间内就累加自身，否则贡献 0
            if (x > low) {  // x 大于下界时，左子树里才可能存在 >= low 的值，才值得递归
                ans += dfs(root->left);  // 累加左子树的区间和
            }
            if (x < high) {  // x 小于上界时，右子树里才可能存在 <= high 的值
                ans += dfs(root->right);  // 累加右子树的区间和
            }
            return ans;  // 返回本子树落在区间内的节点值之和
        };  // lambda 定义结束
        return dfs(root);  // 从根节点开始 DFS，得到整棵 BST 的区间和
    }
};  // 类定义结束