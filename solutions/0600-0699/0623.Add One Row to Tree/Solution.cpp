// 题目：623. 在二叉树中增加一行（Add One Row to Tree）
// 思路：深度为 1 时新建根节点；否则 DFS 找到第 depth-1 层的节点，把新节点插在它和原孩子之间。
// 时间复杂度：O(n)，最坏要遍历整棵树；空间复杂度：O(h)，递归栈深度为树高。
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
public:  // 题解方法与内部状态对外可见
    int val;  // 把要插入的值存成成员变量，dfs 递归时直接取用
    int depth;  // 把目标深度也存成成员变量，省去递归时层层传参

    TreeNode* addOneRow(TreeNode* root, int val, int depth) {  // 在指定深度插入一行新节点，值均为 val
        if (depth == 1) return new TreeNode(val, root, nullptr);  // 深度为 1：新值成为新根，原树整体挂到新根的左孩子上
        this->val = val;  // 记录插入值，供 dfs 使用
        this->depth = depth;  // 记录目标深度，供 dfs 使用
        dfs(root, 1);  // 从第 1 层开始向下递归处理
        return root;  // 走的不是换根分支，原根节点不变，直接返回
    }

    void dfs(TreeNode* root, int d) {  // 递归辅助函数：root 为当前节点，d 为它所在的深度
        if (!root) return;  // 空节点无需处理，直接回溯
        if (d == depth - 1) {  // 到达目标深度的上一层：新的一行就插在它的两个孩子位置
            auto l = new TreeNode(val, root->left, nullptr);  // 新左孩子：值为 val，原来的左子树挂到它的左孩子上
            auto r = new TreeNode(val, nullptr, root->right);  // 新右孩子：值为 val，原来的右子树挂到它的右孩子上
            root->left = l;  // 把新左孩子接到当前节点
            root->right = r;  // 把新右孩子接到当前节点
            return;  // 本层已处理完，不再往下递归，避免重复插入
        }
        dfs(root->left, d + 1);  // 继续处理左子树的下一层
        dfs(root->right, d + 1);  // 继续处理右子树的下一层
    }
};