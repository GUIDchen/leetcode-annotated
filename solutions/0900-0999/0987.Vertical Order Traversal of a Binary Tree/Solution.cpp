// 题目：987. 二叉树的垂序遍历（Vertical Order Traversal of a Binary Tree）
// 思路：DFS 收集每个节点的 (列号, 行号, 值) 三元组，整体排序后按列号分组，组内顺序就是题目要求的顺序。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，存放全部节点信息。
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
    vector<vector<int>> verticalTraversal(TreeNode* root) {  // root 是二叉树根节点
        vector<tuple<int, int, int>> nodes;  // 每个元素是 (列号 j, 行号 i, 节点值)
        function<void(TreeNode*, int, int)> dfs = [&](TreeNode* root, int i, int j) {  // 深度优先 lambda：i 为行号，j 为列号
            if (!root) {  // 空节点直接返回
                return;  // 递归出口
            }  // if 结束
            nodes.emplace_back(j, i, root->val);  // 记录当前节点的三元组（列在前，便于默认按列排序）
            dfs(root->left, i + 1, j - 1);  // 左子节点：行号 +1，列号 -1
            dfs(root->right, i + 1, j + 1);  // 右子节点：行号 +1，列号 +1
        };  // lambda 定义结束
        dfs(root, 0, 0);  // 从根节点开始，行列坐标均为 0
        sort(nodes.begin(), nodes.end());  // 按 (列号, 行号, 值) 升序排序，正好是题目要求的优先级
        vector<vector<int>> ans;  // ans 是按列分组后的答案
        int prev = -2000;  // 上一组的列号，用越界哨兵保证第一组一定新建
        for (auto [j, _, val] : nodes) {  // 按排序结果遍历，_ 是行号占位不用
            if (j != prev) {  // 列号变化说明进入新的一列
                prev = j;  // 更新当前列号
                ans.emplace_back();  // 为这一列新建一个空数组
            }  // if 结束
            ans.back().push_back(val);  // 把节点值追加到当前列的分组
        }  // 遍历结束
        return ans;  // 返回垂序遍历结果
    }  // 方法结束
};  // 类定义结束