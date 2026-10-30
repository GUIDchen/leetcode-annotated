// 题目：589. N 叉树的前序遍历（N-ary Tree Preorder Traversal）
// 思路：递归 DFS，先访问根节点并把值写入答案，再按顺序对每个孩子递归（前序 = 根 → 各子树）。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，答案数组与递归栈（最坏 n 层）。
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void dfs(struct Node* root, int* ans, int* i) {  // root 是当前子树的根；ans 是结果数组；i 指向下一个要写入的位置
    if (!root) {  // 空节点直接返回，这是递归出口
        return;  // 什么都不做，直接返回
    }
    ans[(*i)++] = root->val;  // 先写下根节点的值，再把写入位置后移（*i 必须加括号，优先级高于 ++）
    for (int j = 0; j < root->numChildren; j++) {  // 依次遍历当前节点的所有孩子
        dfs(root->children[j], ans, i);  // 对孩子递归做同样的前序遍历，把同一个 i 传下去保持连续写入
    }
}

int* preorder(struct Node* root, int* returnSize) {  // 判题入口：返回结果数组，并通过 returnSize 回传长度
    int* ans = malloc(sizeof(int) * 10000);  // 题目保证节点数不超过 1e4，一次申请足够大的空间
    *returnSize = 0;  // 结果长度先置 0
    dfs(root, ans, returnSize);  // 递归填表，顺便把已填长度写回 returnSize
    return ans;  // 返回 malloc 出来的数组，由调用方负责 free
}
