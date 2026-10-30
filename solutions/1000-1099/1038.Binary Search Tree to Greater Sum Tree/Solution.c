// 题目：1038. 从二叉搜索树到更大和树（Binary Search Tree to Greater Sum Tree）
// 思路：按「右 → 根 → 左」的反中序遍历，用 sum 累加已访问过的节点值，把每个节点的值就地改写为累加和。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
/**
 * Definition for a binary tree node.  （二叉树节点结构体，由判题器提供）
 * struct TreeNode {  （节点结构体开始）
 *     int val;  （节点值）
 *     struct TreeNode *left;  （左孩子指针）
 *     struct TreeNode *right;  （右孩子指针）
 * };  （结构体结束）
 */

int dfs(struct TreeNode* root, int sum) {  // dfs 返回「处理完当前子树后往上累加得到的总和」；root 是当前节点，sum 是比它大的所有节点值之和
    if (root) {  // 节点非空才需要处理
        sum = dfs(root->right, sum) + root->val;  // 先递归右子树，拿到更大的那些节点值之和，再加上当前节点值
        root->val = sum;  // 当前节点新值 = 所有不小于它的节点值之和（题目要求的更大和）
        sum = dfs(root->left, sum);  // 再递归左子树，把更新后的累加和传下去
    }  // 空节点判断结束
    return sum;  // 把累加和返回给上一层调用
}  // dfs 函数结束

struct TreeNode* bstToGst(struct TreeNode* root) {  // 主函数：root 是 BST 根节点，返回转换后的根（树形结构不变，只改节点的值）
    dfs(root, 0);  // 从根开始做反中序遍历，初始累加和为 0
    return root;  // 返回原来的根节点
}  // bstToGst 函数结束