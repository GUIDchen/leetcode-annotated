// 题目：687. 最长同值路径（Longest Univalue Path）
// 思路：后序 DFS，返回「以当前节点为一端、向下延伸的同值路径长度」，并用「左臂 + 右臂」在拐弯处更新全局最大边数。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 手写取最大值宏，避免为这一个函数额外引入头文件

int dfs(struct TreeNode* root, int* ans) {  // 返回以 root 向下延伸的最长同值路径长度；*ans 保存全局答案（边数）
    if (!root) {  // 空节点：没有可延伸的路径
        return 0;  // 空子树贡献长度为 0
    }
    int l = dfs(root->left, ans);  // 先递归求左子树能向下延伸的同值长度（此处还未判断与当前值是否相同）
    int r = dfs(root->right, ans);  // 同样求右子树能向下延伸的同值长度
    l = root->left && root->left->val == root->val ? l + 1 : 0;  // 只有左孩子与当前节点值相同才能接上这条边，长度 +1；否则同值路径在此断开，记 0
    r = root->right && root->right->val == root->val ? r + 1 : 0;  // 右孩子同理：值相同才 +1，否则断开记 0
    *ans = max(*ans, l + r);  // 以当前节点为拐点，左右两臂拼成完整路径，边数为 l + r，用它更新全局答案
    return max(l, r);  // 向父节点汇报时只能选择一条臂（路径不能分叉），所以取较长的一条
}

int longestUnivaluePath(struct TreeNode* root) {  // 主函数：求整棵树中最长同值路径的边数
    int ans = 0;  // 答案初值 0，空树/单节点都返回 0
    dfs(root, &ans);  // 把 ans 的地址交给 dfs，递归过程中就地更新最大值
    return ans;  // 返回最终统计到的最大边数
}
