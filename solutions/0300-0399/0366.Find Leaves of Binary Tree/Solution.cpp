// 题目：366. 寻找二叉树的叶子节点（Find Leaves of Binary Tree）
// 思路：后序 DFS 求每个结点的高度（叶子高度为 0），把同高度的结点值收进 ans[高度]，自然形成自底向上的分层叶子。
// 时间复杂度：O(n)，每个结点只访问一次；空间复杂度：O(n)，递归栈深度与结果数组。
// 下列 block comment 是 LeetCode 题面自带的二叉树结点定义说明，原样保留
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
    vector<vector<int>> findLeaves(TreeNode* root) {  // root：二叉树根结点；返回自底向上的逐层叶子值
        vector<vector<int>> ans;  // ans[h] 保存「高度为 h 的那一层」被摘掉的叶子值
        function<int(TreeNode*)> dfs = [&](TreeNode* root) {  // 递归函数 dfs 返回子树高度；用 std::function 让 lambda 能自引用
            if (!root) {  // 空结点高度记为 0，是递归的终止条件
                return 0;  // 空子树贡献高度 0
            }
            int l = dfs(root->left);  // 先递归求左子树高度
            int r = dfs(root->right);  // 再递归求右子树高度
            int h = max(l, r);  // 当前结点高度取左右子树较高者（叶子因左右为空而得到 h = 0）
            if (ans.size() == h) {  // 第一次遇到某个高度时，说明这一层还没建立数组
                ans.push_back({});  // 为新的这一层开辟空数组
            }
            ans[h].push_back(root->val);  // 把当前结点值放入对应高度层（叶子在最前，根在最后）
            return h + 1;  // 返回给父结点的高度是 h + 1
        };  // lambda 定义结束
        dfs(root);  // 从根开始深度优先遍历，边遍历边填 ans
        return ans;  // 返回自底向上的分层结果
    }  // 方法结束
};  // 类定义结束