// 题目：2331. 计算布尔二叉树的值（Evaluate Boolean Binary Tree）
// 思路：对布尔表达式树做后序递归——叶子节点直接返回自身的 0/1，内部节点 val 为 2 取「或」、为 3 取「与」合并左右子树。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度为树高 h（最坏退化成链时为 O(n)）。
/**
 * Definition for a binary tree node.
 * struct TreeNode {  // 题目给出的二叉树节点结构体
 *     int val;  // 节点值：叶子存 0/1，内部节点存 2（或）或 3（与）
 *     struct TreeNode *left;  // 左子树指针
 *     struct TreeNode *right;  // 右子树指针
 * };  // 结构体定义结束
 */
bool evaluateTree(struct TreeNode* root) {  // 主函数：返回以 root 为根的布尔表达式树的取值
    if (!root->left) {  // 左孩子为空即叶子节点（题目保证布尔树是满二叉树），不需要继续递归
        return root->val == 1;  // 叶子只存 0 或 1，转成 true/false 返回
    }  // 叶子分支结束
    if (root->val == 2) {  // 内部节点值 2 代表逻辑或（OR）
        return evaluateTree(root->left) || evaluateTree(root->right);  // 递归求左右子树，任一为真即为真；C 的 || 自带短路，可省掉一次递归
    }  // 或分支结束
    return evaluateTree(root->left) && evaluateTree(root->right);  // 剩下的 val 为 3，代表逻辑与（AND），两侧都为真才为真
}  // 函数结束