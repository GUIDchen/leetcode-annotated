// 3879. 二叉树中的最大不同路径和 / Maximum Distinct Path Sum in a Binary Tree
// 核心思路：先把二叉树建成无向图，再以每个节点为起点回溯搜索，路径上节点值去重后取最大路径和。
// 复杂度：时间 O(n^2)（每个起点一次搜索，单次 O(n)），空间 O(n)（邻接表、访问集合与递归栈）。
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
class Solution {  // 定义题解类
public:  // 公有接口
    int maxSum(TreeNode* root) {  // 返回节点值互不相同的最大路径和
        unordered_map<TreeNode*, vector<TreeNode*>> g;  // 邻接表：每个节点连向父节点与左右孩子
        unordered_set<int> vis;  // 记录当前路径上已使用过的节点值

        auto dfs = [&](this auto&& dfs, TreeNode* node, TreeNode* p) -> void {  // 建图：把二叉树当成无向图处理
            if (!node) return;  // 空节点直接返回
            g[node].push_back(p);  // 记录父节点
            g[node].push_back(node->left);  // 记录左孩子
            g[node].push_back(node->right);  // 记录右孩子
            dfs(node->left, node);  // 递归处理左子树
            dfs(node->right, node);  // 递归处理右子树
        };  // 建图 lambda 结束

        auto dfs2 = [&](this auto&& dfs2, TreeNode* node) -> int {  // 回溯搜索：求以 node 为起点、节点值互不重复的最大路径和
            if (!node || vis.count(node->val)) return 0;  // 空节点或该值已用过，此方向不可走
            vis.insert(node->val);  // 标记当前节点值已使用
            int res = node->val;  // 当前节点值先计入路径
            int best = 0;  // 记录自当前节点延伸出去的最优子路径和
            for (auto nxt : g[node]) {  // 枚举无向图中的所有邻居
                best = max(best, dfs2(nxt));  // 取各分支中的最大值
            }  // 邻居枚举结束
            vis.erase(node->val);  // 回溯：撤销当前节点值的标记
            return res + best;  // 当前节点值加上最优子路径
        };  // 回溯 lambda 结束

        dfs(root, nullptr);  // 从根节点开始建图

        int ans = INT_MIN;  // 答案初始化为最小整数
        for (auto& [node, _] : g) {  // 枚举每个节点作为路径起点
            ans = max(ans, dfs2(node));  // 更新全局最大值
            vis.clear();  // 清空访问标记，保证不同起点互不影响
        }  // 起点枚举结束
        return ans;  // 返回最大不同路径和
    }  // maxSum 方法结束
};  // Solution 类定义结束
