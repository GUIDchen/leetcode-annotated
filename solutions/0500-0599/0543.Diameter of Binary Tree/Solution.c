// 题目：543. 二叉树的直径（Diameter of Binary Tree）
// 思路：树形 DP。递归求每个节点的左右子树高度，路径经过该节点时的长度为 l+r，用指针 ans 记录全局最大值，向上返回 1+max(l,r)。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int dfs(struct TreeNode* root, int* ans) {  // 递归函数：返回以 root 为根的子树高度（节点数），并把经过该节点的最大路径长度更新到 *ans
    if (root == NULL) {  // 空节点高度为 0，作为递归边界
        return 0;  // 空树贡献的高度是 0
    }
    int l = dfs(root->left, ans);
    int r = dfs(root->right, ans);  // 左子树高度；dfs 内部顺带更新全局答案
    if (l + r > *ans) {  // 右子树高度
        *ans = l + r;  // 经过当前节点的路径长度就是左右子树高度之和，比已有答案大就更新
    }  // 记录新的最大直径
    return 1 + (l > r ? l : r);
}  // 当前节点向上贡献的高度：取较高的一棵子树再加 1（算上自己）
  // dfs 结束
int diameterOfBinaryTree(struct TreeNode* root) {
    int ans = 0;  // 主函数：求二叉树的直径（两节点间最长路径的边数）
    dfs(root, &ans);  // ans 作为全局答案，初始为 0，通过指针在递归中更新
    return ans;  // 一次后序遍历即可算出答案
}  // 返回最长路径长度
