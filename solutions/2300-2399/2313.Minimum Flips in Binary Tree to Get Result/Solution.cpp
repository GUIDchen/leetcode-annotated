// 题目：2313. 二叉树中得到结果所需的最少翻转次数（Minimum Flips in Binary Tree to Get Result）
// 思路：树上 DP。dfs 返回 {该子树得到 0 的最少翻转次数, 得到 1 的最少翻转次数}；叶子直接得到 {x, x^1}，内部节点按 OR/AND/XOR/NOT 的真值表把左右子树的代价组合起来取最小。
// 时间复杂度：O(n)，每个节点只算一次；空间复杂度：O(h)，递归栈深度（h 为树高）。
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
    int minimumFlips(TreeNode* root, bool result) {  // root：表达式二叉树；result：希望整棵树最终得到的结果
        function<pair<int, int>(TreeNode*)> dfs = [&](TreeNode* root) -> pair<int, int> {  // 返回 pair{子树得到 0 的最少翻转次数, 得到 1 的最少翻转次数}
            if (!root) {  // 空节点不会真正出现，先用一个极大值表示「不可达」
                return {1 << 30, 1 << 30};  // 1<<30 近似无穷大，保证之后取 min 时不会被选中
            }
            int x = root->val;  // 节点值：0/1 为叶子，2=OR，3=AND，4=XOR，5=NOT
            if (x < 2) {  // 叶子节点：值本身已经固定
                return {x, x ^ 1};  // 得到 x 不需翻转，得到 x^1 需要翻转 1 次
            }
            auto [l0, l1] = dfs(root->left);  // 左子树得到 0 / 得到 1 的最少翻转次数
            auto [r0, r1] = dfs(root->right);  // 右子树得到 0 / 得到 1 的最少翻转次数
            int a = 0, b = 0;  // a：本子树得到 0 的最少翻转次数；b：本子树得到 1 的最少翻转次数
            if (x == 2) {  // 或运算：只要有一边为 1，结果就是 1
                a = l0 + r0;  // 结果为 0，必须两边都为 0
                b = min({l0 + r1, l1 + r0, l1 + r1});  // 结果为 1，三种「至少一边为 1」的组合取最小
            } else if (x == 3) {  // 与运算：只有两边都为 1，结果才是 1
                a = min({l0 + r0, l0 + r1, l1 + r0});  // 结果为 0，只要有一边为 0，三种组合取最小
                b = l1 + r1;  // 结果为 1，必须两边都为 1
            } else if (x == 4) {  // 异或运算：两边不同时结果为 1
                a = min(l0 + r0, l1 + r1);  // 结果为 0，两边同为 0 或同为 1
                b = min(l0 + r1, l1 + r0);  // 结果为 1，两边必须一 0 一 1
            } else {  // 剩下的就是非运算（x == 5）
                a = min(l1, r1);  // 结果为 0 需要孩子为 1；非运算只有一个孩子，两边取较小即可
                b = min(l0, r0);  // 结果为 1 需要孩子为 0
            }
            return {a, b};  // 返回本子树得到 0 / 得到 1 的最少翻转次数
        };  // lambda 定义结束
        auto [a, b] = dfs(root);  // 求出整棵树得到 0 与得到 1 的最少翻转次数
        return result ? b : a;  // 按题目要求的最终结果取对应答案
    }
};