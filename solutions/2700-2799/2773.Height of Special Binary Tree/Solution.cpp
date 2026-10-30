// 题目：2773. 特殊二叉树的高度（Height of Special Binary Tree 🔒）
// 思路：特殊二叉树中叶子节点的 left / right 会分别指回它的中序前驱与后继，所以“孩子反过来指向父亲”的边不是真正的孩子边；从根做 DFS，跳过这类回指边并统计最大深度。
// 时间复杂度：O(n)，每个节点至多访问一次；空间复杂度：O(h)，h 为树高，即递归栈深度。
// 下面这段 TreeNode 结构体由 LeetCode 判题器提供，这里仅作签名占位说明
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
public:  // 对外暴露的解题方法
    int heightOfTree(TreeNode* root) {  // root 是这棵特殊二叉树的根节点
        int ans = 0;  // 记录搜索过程中遇到的最大深度，即树高
        function<void(TreeNode*, int)> dfs = [&](TreeNode* root, int d) {  // 递归 lambda：root 是当前节点，d 是当前深度
            ans = max(ans, d++);  // 先用当前深度更新答案，再把 d 自增后传给子节点
            if (root->left && root->left->right != root) {  // 左孩子存在，且它的 right 不是指回当前节点（否则就是叶子回指边）
                dfs(root->left, d);  // 走真正的左孩子边继续下探
            }
            if (root->right && root->right->left != root) {  // 右孩子存在，且它的 left 不是指回当前节点（否则就是叶子回指边）
                dfs(root->right, d);  // 走真正的右孩子边继续下探
            }
        };
        dfs(root, 0);  // 根节点深度记为 0，从根开始深度优先搜索
        return ans;  // 返回整棵特殊二叉树的高度
    }
};