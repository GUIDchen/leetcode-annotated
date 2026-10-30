// 题目：2641. 二叉树的堂兄弟节点 II（Cousins in Binary Tree II）
// 思路：两次 DFS：第一次统计每一层的节点值之和 s[depth]；第二次把每个节点改成「本层总和 - 它与它的兄弟之和」。
// 时间复杂度：O(n)，每个节点访问两次；空间复杂度：O(h)，递归栈深度（外加按层统计的数组）。
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
    TreeNode* replaceValueInTree(TreeNode* root) {  // root：二叉树根节点
        memset(s, 0, sizeof(s));  // 清空按层统计数组，避免同一对象被多次调用时残留旧数据
        dfs1(root, 0);  // 第一遍 DFS：统计每一层所有节点值之和
        root->val = 0;  // 根节点没有堂兄弟，按题意直接置 0
        dfs2(root, 0);  // 第二遍 DFS：用层和减去自身与兄弟之和，得到堂兄弟之和
        return root;  // 返回原地修改后的根节点
    }

private:  // 以下是内部辅助成员，不对外暴露
    int s[100010];  // s[d] 记录深度为 d 的这一层所有节点值之和
    void dfs1(TreeNode* root, int depth) {  // 递归统计每一层的节点和
        if (!root) {  // 空节点没有值可累加，直接返回
            return;
        }
        s[depth] += root->val;  // 把当前节点值累加到它所在的层
        dfs1(root->left, depth + 1);  // 递归左子树，深度加 1
        dfs1(root->right, depth + 1);  // 递归右子树，深度加 1
    };

    void dfs2(TreeNode* root, int depth) {  // 递归改写每个子节点的值
        int l = root->left ? root->left->val : 0;  // 左孩子的值，缺失时记为 0
        int r = root->right ? root->right->val : 0;  // 右孩子的值，缺失时记为 0
        int sub = l + r;  // 两个孩子之和：同一父节点的兄弟要互相排除
        ++depth;  // 先下移一层，因为接下来处理的是孩子所在层
        if (root->left) {  // 有左孩子才需要改写
            root->left->val = s[depth] - sub;  // 新值 = 本层总和 - 自己与兄弟之和，正好是堂兄弟之和
            dfs2(root->left, depth);  // 继续递归处理左子树
        }
        if (root->right) {  // 有右孩子才需要改写
            root->right->val = s[depth] - sub;  // 右孩子同理：本层总和减去自身与兄弟
            dfs2(root->right, depth);  // 继续递归处理右子树
        }
    };
};