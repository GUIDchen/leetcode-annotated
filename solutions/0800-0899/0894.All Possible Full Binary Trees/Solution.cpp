// 题目：894. 所有可能的真二叉树（All Possible Full Binary Trees）
// 核心思路：真二叉树节点数必为奇数；枚举左子树节点数 i 与右子树 n-1-i，左右子树两两组合并记忆化。
// 时间复杂度：约 O(Catalan(n/2))，与输出规模同阶；空间复杂度：O(Catalan(n/2))，缓存全部子树。
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
    vector<TreeNode*> allPossibleFBT(int n) {  // n：节点总数；只有奇数个节点才可能构成真二叉树
        vector<vector<TreeNode*>> f(n + 1);  // 记忆化表：f[k] 存放节点数为 k 的全部真二叉树根节点
        function<vector<TreeNode*>(int)> dfs = [&](int n) -> vector<TreeNode*> {  // 递归函数：返回用 n 个节点能构成的所有真二叉树
            if (f[n].size()) {  // 缓存命中就直接复用，避免重复构造子树
                return f[n];  // 返回已经算好的结果
            }
            if (n == 1) {  // 只有一个节点时，唯一的真二叉树就是这个叶子
                return vector<TreeNode*>{new TreeNode()};  // 新建值为 0 的叶子节点
            }
            vector<TreeNode*> ans;  // 收集当前 n 的所有组合方式
            for (int i = 0; i < n - 1; ++i) {  // 枚举左子树节点数 i，根占 1 个，右子树为 n-1-i
                int j = n - 1 - i;  // 右子树节点数
                for (auto left : dfs(i)) {  // 遍历所有可能的左子树
                    for (auto right : dfs(j)) {  // 与所有可能的右子树两两组合
                        ans.push_back(new TreeNode(0, left, right));  // 以新根串起这对左右子树
                    }
                }
            }
            return f[n] = ans;  // 结果写入缓存并返回
        };
        return dfs(n);  // 答案就是 n 个节点的全部真二叉树
    }
};