// 题目：742. 二叉树最近的叶节点（Closest Leaf in a Binary Tree）
// 思路：把树看成无向图（父子之间双向连边），从值为 k 的节点出发做 BFS，第一次遇到的叶子就是离 k 最近的叶子。
// 时间复杂度：O(n)，每个节点在建图和 BFS 中各访问一次；空间复杂度：O(n)，邻接表、队列与访问集合都是 O(n)。
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
    int findClosestLeaf(TreeNode* root, int k) {  // root：二叉树根节点；k：起点节点的值，返回离它最近的叶子节点值
        unordered_map<TreeNode*, vector<TreeNode*>> g;  // 邻接表：节点 → 它的邻居（父亲 + 左右孩子），用来把树当图遍历
        function<void(TreeNode*, TreeNode*)> dfs = [&](TreeNode* root, TreeNode* fa) {  // 递归 lambda：把树转成无向图；用 function 包一层才能递归调用自己
            if (root) {  // 空节点直接返回
                g[root].push_back(fa);  // 记录当前节点的父节点（根节点的父节点为 nullptr）
                g[fa].push_back(root);  // 记录反向边：父节点也能走到当前节点，这样才能从 k 往父方向搜索
                dfs(root->left, root);  // 递归处理左子树
                dfs(root->right, root);  // 递归处理右子树
            }  // 结束 if
        };  // 结束递归函数定义
        dfs(root, nullptr);  // 从根节点开始建图
        queue<TreeNode*> q;  // BFS 队列
        unordered_set<TreeNode*> vis;  // 记录已入队的节点，避免重复访问
        for (auto& [node, _] : g) {  // 在邻接表中寻找值为 k 的节点
            if (node && node->val == k) {  // 跳过 nullptr 这个虚拟节点，值相等即为起点
                q.push(node);  // 起点入队
                vis.insert(node);  // 标记起点已访问
            }  // 结束 for
        }  // 结束起点搜索
        while (1) {  // BFS 循环：按距离从近到远逐层扩展
            auto node = q.front();  // 取出队首节点
            q.pop();  // 队首出队
            if (node) {  // 空节点的邻居是 nullptr 这条虚拟边，直接忽略
                if (node->left == node->right) {  // 左右孩子同时为空 ⇔ 叶子节点
                    return node->val;  // BFS 保证第一次遇到的叶子离 k 最近，直接返回它的值
                }  // 结束叶子判断
                for (auto& nxt : g[node]) {  // 遍历这个节点的所有邻居
                    if (vis.count(nxt)) {  // 已经访问过就跳过，避免走回头路
                        continue;  // 继续看下一个邻居
                    }  // 结束 if
                    q.push(nxt);  // 邻居加入队列，等待下一层扩展
                    vis.insert(nxt);  // 标记邻居已访问
                }  // 结束邻居循环
            }  // 结束 if (node)
        }  // 结束 BFS 循环
    }  // 结束 findClosestLeaf
};  // 结束 Solution 类