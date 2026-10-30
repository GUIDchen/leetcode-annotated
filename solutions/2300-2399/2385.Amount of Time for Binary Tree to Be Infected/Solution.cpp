// 题目：2385. 感染二叉树需要的总时间（Amount of Time for Binary Tree to Be Infected）
// 核心思路：先把二叉树当作无向图建邻接表（父子双向加边），再从 start 出发做一次求「最远距离」的 DFS，得到感染完所有节点所需的分钟数。
// 时间复杂度：O(n)，每个节点在两次 DFS 中各访问常数次；空间复杂度：O(n)，邻接表与递归栈都随节点数线性增长。
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
    int amountOfTime(TreeNode* root, int start) {  // root：二叉树根；start：初始感染节点值；返回感染整棵树需要的分钟数
        unordered_map<int, vector<int>> g;  // g 是无向图的邻接表：节点值 -> 与它相邻的节点值列表
        function<void(TreeNode*, TreeNode*)> dfs = [&](TreeNode* node, TreeNode* fa) {  // 第一个 DFS：递归遍历树，同时把每条父子边双向写入邻接表
            if (!node) {  // 走到空节点就直接回退，避免继续递归
                return;  // 递归出口：当前分支没有节点可处理
            }  // 结束空节点判断
            if (fa) {  // fa 非空说明 node 有父节点，两者之间需要连一条无向边
                g[node->val].push_back(fa->val);  // node -> fa 方向加边，这样从子节点也能走到父节点
                g[fa->val].push_back(node->val);  // fa -> node 方向加边，父子关系变成双向可达
            }  // 结束父子连边
            dfs(node->left, node);  // 继续递归左子树，把当前节点 node 作为左孩子的父节点传入
            dfs(node->right, node);  // 继续递归右子树，把当前节点 node 作为右孩子的父节点传入
        };  // 结束建图 DFS 的 lambda
        function<int(int, int)> dfs2 = [&](int node, int fa) -> int {  // 第二个 DFS：在无向图上求从 node 出发能走的最长距离（fa 用于防止走回父节点）
            int ans = 0;  // ans 记录从当前节点出发的最远步数，初始为 0
            for (int nxt : g[node]) {  // 枚举与当前节点相邻的所有节点
                if (nxt != fa) {  // 跳过来时的父节点，避免在无向图上原地绕圈
                    ans = max(ans, 1 + dfs2(nxt, node));  // 走一步到 nxt 后继续求最远距离，取所有分支的最大值
                }  // 结束对单个邻居的处理
            }  // 结束邻居枚举
            return ans;  // 返回以当前节点为根的最远距离
        };  // 结束求深度 DFS 的 lambda
        dfs(root, nullptr);  // 先以根节点、无父节点（nullptr）为起点，把整棵树建成无向图
        return dfs2(start, -1);  // 再从 start 出发（父节点用 -1 占位，节点值不会是 -1）求最远距离
    }  // 结束方法体
};  // 结束题解类