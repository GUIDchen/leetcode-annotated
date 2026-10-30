// 题目：110. 平衡二叉树（Balanced Binary Tree）
// 思路：后序递归求高度，一旦某个结点左右子树高度差超过 1 就返回 -1 当作「已不平衡」的标记向上冒泡，避免重复计算高度。
// 时间复杂度：O(n)，每个结点只访问一次；空间复杂度：O(h)，h 为树高，即递归栈深度。
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
    bool isBalanced(TreeNode* root) {  // root 是树根，返回整棵树是否平衡
        function<int(TreeNode*)> height = [&](TreeNode* root) {  // 递归函数：返回子树高度；返回 -1 表示该子树已经不平衡
            if (!root) {  // 空结点高度记为 0
                return 0;  // 空树高度为 0
            }  // 空结点处理完毕
            int l = height(root->left);  // 递归求左子树高度（可能是 -1 这个不平衡标记）
            int r = height(root->right);  // 递归求右子树高度
            if (l == -1 || r == -1 || abs(l - r) > 1) {  // 任一子树已不平衡，或左右高度差大于 1，都判为不平衡
                return -1;  // 用 -1 把「不平衡」往上传递，省掉重复计算
            }  // 不平衡判断结束
            return 1 + max(l, r);  // 平衡则高度为左右较大者加一
        };  // 递归 lambda 定义结束
        return height(root) >= 0;  // 高度非负说明全程平衡
    }  // 方法结束
};  // 题解类结束