// 题目：230. 二叉搜索树中第 K 小的元素（Kth Smallest Element in a BST）
// 思路：用显式栈模拟中序遍历，二叉搜索树的中序序列严格升序，第 k 个被访问的结点就是答案，找到即可提前返回。
// 时间复杂度：O(H + k)，H 为树高（最坏 O(n)）；空间复杂度：O(H)，即栈的最大深度。
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
    int kthSmallest(TreeNode* root, int k) {  // root 是二叉搜索树根结点，k 是目标排名（从 1 开始），返回第 k 小的值
        stack<TreeNode*> stk;  // 显式栈：用来保存一路向左时经过的结点，替代递归调用栈
        while (root || !stk.empty()) {  // 只要还有未访问的结点，或栈里还有待回溯的结点，就继续遍历
            if (root) {  // 当前结点非空：一路向左压栈，先把更小的结点走完
                stk.push(root);  // 把当前结点压栈，留待回溯时访问
                root = root->left;  // 向左孩子继续深入，直到没有左孩子
            } else {  // 左边走到头了，该弹出栈顶结点访问了
                root = stk.top();  // 取栈顶：此时它是当前最小的未访问结点
                stk.pop();  // 弹出，表示这个结点已经被访问过
                if (--k == 0) return root->val;  // 访问一个结点就把 k 减一；减到 0 说明这个结点就是第 k 小
                root = root->right;  // 转向右子树，右子树的所有值都比当前结点大
            }  // 分支结束
        }  // 循环结束
        return 0;  // 理论上不会走到这里（题目保证 k 有效），返回 0 只为满足函数必须有返回值
    }  // 方法结束
};  // 题解类结束