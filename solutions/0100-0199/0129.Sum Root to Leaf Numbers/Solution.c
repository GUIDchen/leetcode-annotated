// 题目：129. 求根节点到叶节点数字之和（Sum Root to Leaf Numbers）
// 思路：DFS 自顶向下把路径拼成一个数字 num = num * 10 + 当前值，走到叶子就把这个数累加进总和。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度等于树高。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */  // 上面的 TreeNode 结构体由判题器预先提供

int dfs(struct TreeNode* root, int num) {  // root：当前节点；num：从根走到父节点为止拼出的数字
    if (!root) {  // 空节点
        return 0;  // 空子树不贡献任何数字
    }  // if 结束
    num = num * 10 + root->val;  // 把当前节点的值接到已拼数字的末尾（十进制左移一位再加）
    if (!root->left && !root->right) {  // 左右子树都为空，说明当前是叶子节点
        return num;  // 叶子处得到一个完整的路径数字，直接返回
    }  // if 结束
    return dfs(root->left, num) + dfs(root->right, num);  // 非叶子节点：左右子树所有路径数字之和就是本子树的答案
}  // dfs 结束

int sumNumbers(struct TreeNode* root) {  // 题目要求的入口函数
    return dfs(root, 0);  // 从根开始，初始拼出的数字为 0
}  // sumNumbers 结束