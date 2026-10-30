// 题目：337. 打家劫舍 III（House Robber III）
// 核心思路：树形 DP，后序遍历每个节点并返回「选当前节点」与「不选当前节点」两种状态的最大收益，相邻父子不能同时被选。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，递归栈与返回的状态对。
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
    int rob(TreeNode* root) {  // root 为二叉树根节点，返回能偷到的最大金额
        function<pair<int, int>(TreeNode*)> dfs = [&](TreeNode* root) -> pair<int, int> {  // 后序 DFS：返回 pair{选当前节点, 不选当前节点} 两种状态下的最大收益
            if (!root) {  // 空节点没有任何收益
                return make_pair(0, 0);  // 两种状态都返回 0
            }  // 空节点分支结束
            auto [la, lb] = dfs(root->left);  // 左子树的两个状态：la 表示选左孩子，lb 表示不选左孩子
            auto [ra, rb] = dfs(root->right);  // 右子树同理：ra 表示选右孩子，rb 表示不选右孩子
            return make_pair(root->val + lb + rb, max(la, lb) + max(ra, rb));  // 选当前节点时孩子都不能选；不选当前节点时孩子各自取较优值
        };  // lambda 定义结束
        auto [a, b] = dfs(root);  // 从根节点拿到最终两种状态
        return max(a, b);  // 两者取最大即为答案
    }  // 方法结束
};  // 类定义结束