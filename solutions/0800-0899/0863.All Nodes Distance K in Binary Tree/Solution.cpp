// 题目：863. 二叉树中所有距离为 K 的结点（All Nodes Distance K in Binary Tree）
// 思路：先 DFS 记录每个结点的父结点，把二叉树补成无向图；再从 target 出发做深度为 k 的 DFS，收集到达距离 k 的结点。
// 时间复杂度：O(n)，每个结点被访问常数次；空间复杂度：O(n)，父指针表与递归栈。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {  // root：二叉树根；target：起点结点；k：期望距离；返回所有距离为 k 的结点值
        unordered_map<TreeNode*, TreeNode*> g;  // 邻接表：记录每个结点的父结点，让搜索可以沿父边向上走
        vector<int> ans;  // 存放答案结点值

        auto dfs = [&](this auto&& dfs, TreeNode* node, TreeNode* fa) {  // 第一次 DFS：递归填写每个结点的父结点
            if (!node) return;  // 空结点直接返回，递归出口
            g[node] = fa;  // 记录当前结点的父亲；根结点的父亲为 nullptr
            dfs(node->left, node);  // 递归处理左子树
            dfs(node->right, node);  // 递归处理右子树
        };  // dfs 闭包定义结束

        auto dfs2 = [&](this auto&& dfs2, TreeNode* node, TreeNode* fa, int k) {  // 第二次 DFS：从当前结点出发，向下或向上走 k 步
            if (!node) return;  // 空结点直接返回，递归出口
            if (k == 0) {  // 已经走到目标距离
                ans.push_back(node->val);  // 该结点与 target 距离正好为 k，加入答案
                return;  // 不再继续深入，避免更远
            }  // if 分支结束
            for (auto&& nxt : {node->left, node->right, g[node]}) {  // 依次枚举左儿子、右儿子、父亲三个方向（树已被补成无向图）
                if (nxt != fa) {  // 跳过刚来的结点，避免原路返回造成重复访问
                    dfs2(nxt, node, k - 1);  // 距离减一，继续向下一层搜索
                }  // if 分支结束
            }  // for 循环结束
        };  // dfs2 闭包定义结束

        dfs(root, nullptr);  // 先建好父指针，把树补成无向图
        dfs2(target, nullptr, k);  // 再从 target 出发搜索与它相距 k 的结点
        return ans;  // 返回收集到的答案
    }  // distanceK 方法结束
};  // Solution 类定义结束
