// 题目：2458. 移除子树后的二叉树高度（Height of Binary Tree After Subtree Removal Queries）
// 思路：先自底向上用一次 DFS 求出每个节点的子树高度，再自顶向下 DFS 传递「祖先与其他分支贡献的最大深度」，得到删掉每个节点后剩余树的高度。
// 时间复杂度：O(n + q)，n 为节点数、q 为查询数；空间复杂度：O(n)，哈希表与结果数组各存 n 条。
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
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {  // root：原树根节点；queries：每次要删除的节点值
        unordered_map<TreeNode*, int> d;  // 哈希表：键是节点指针，值是以该节点为根的子树高度
        function<int(TreeNode*)> f = [&](TreeNode* root) -> int {  // 递归函数对象：自底向上求子树高度
            if (!root) return 0;  // 递归出口：空节点高度为 0
            int l = f(root->left), r = f(root->right);  // 先递归求出左右子树的高度
            d[root] = 1 + max(l, r);  // 当前子树高度 = 1 + 左右子树高度较大者，并记入哈希表
            return d[root];  // 把当前子树高度返回给上一层
        };  // 结束求子树高度的 lambda
        f(root);  // 从根节点出发，一次性算好整棵树的子树高度表
        vector<int> res(d.size() + 1);  // 答案表：res[v] 表示删除值为 v 的节点后剩余树的高度
        function<void(TreeNode*, int, int)> dfs = [&](TreeNode* root, int depth, int rest) {  // 自顶向下 DFS：depth 是父节点深度，rest 是祖先与其他分支给出的最大高度
            if (!root) return;  // 递归出口：空节点直接返回
            ++depth;  // 当前节点深度 = 父节点深度 + 1
            res[root->val] = rest;  // 删除当前节点后，剩余树高度只由当前路径之外的部分决定
            dfs(root->left, depth, max(rest, depth + d[root->right]));  // 进入左子树：候选高度取「祖先贡献」与「右兄弟子树提供的深度」
            dfs(root->right, depth, max(rest, depth + d[root->left]));  // 进入右子树：候选高度取「祖先贡献」与「左兄弟子树提供的深度」
        };  // 结束自顶向下 DFS 的 lambda
        dfs(root, -1, 0);  // 传 -1 使根节点自增后深度为 0，根之上没有其他分支贡献
        vector<int> ans;  // 按查询顺序保存答案
        for (int v : queries) ans.emplace_back(res[v]);  // 逐个查询取出对应节点被删除后的剩余高度
        return ans;  // 返回全部查询的答案
    }  // 结束 treeQueries
};  // 结束 Solution 类