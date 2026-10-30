// 题目：95. 不同的二叉搜索树 II（Unique Binary Search Trees II）
// 思路：分治 + 回溯，枚举区间 [i, j] 内每个值 v 作根，左右子树分别递归生成后做笛卡尔积组合。
// 时间复杂度：O(4^n / n^{3/2})，即第 n 个卡特兰数级别的树个数；空间复杂度：O(4^n / n^{3/2})，需保存所有生成的树。
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
    vector<TreeNode*> generateTrees(int n) {  // n 是结点个数，返回所有结构互不相同的二叉搜索树
        function<vector<TreeNode*>(int, int)> dfs = [&](int i, int j) {  // 生成用 [i, j] 区间内所有值构成的全部 BST
            if (i > j) {  // 区间为空，说明这个位置没有子树
                return vector<TreeNode*>{nullptr};  // 返回「一个空子树」这一种方案，供上层组合
            }
            vector<TreeNode*> ans;  // 收集当前区间能生成的所有 BST 根结点
            for (int v = i; v <= j; ++v) {  // 枚举根结点的取值 v，左小右大自动满足 BST 性质
                auto left = dfs(i, v - 1);  // 左子树只能用比 v 小的区间 [i, v-1]
                auto right = dfs(v + 1, j);  // 右子树只能用比 v 大的区间 [v+1, j]
                for (auto l : left) {  // 枚举每一种左子树形态
                    for (auto r : right) {  // 枚举每一种右子树形态
                        ans.push_back(new TreeNode(v, l, r));  // 左右子树自由组合，得到一棵新的 BST
                    }
                }
            }
            return ans;  // 返回当前区间的全部 BST
        };
        return dfs(1, n);  // 结点值是 1..n，从整个区间开始分治
    }
};
