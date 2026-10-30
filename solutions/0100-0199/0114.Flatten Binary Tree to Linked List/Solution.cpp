// 题目：114. 二叉树展开为链表（Flatten Binary Tree to Linked List）
// 思路：对每个节点，若存在左子树，就先找到左子树的最右节点当作前驱，把原右子树挂到前驱右侧，再把整棵左子树搬到右侧并清空左指针，随后沿右链前进。
// 时间复杂度：O(n)，每条边只被走常数次（摊还）；空间复杂度：O(1)，只用了几个指针变量。
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
    void flatten(TreeNode* root) {  // root 为树根；函数原地修改，不返回任何值
        while (root) {  // 逐个节点处理：每轮把当前节点的左子树搬到右侧，然后前进一格
            if (root->left) {  // 没有左子树时无需搬运，直接看下一个节点
                TreeNode* pre = root->left;  // pre 用来找左子树的最右节点，它将成为原右子树的新前驱
                while (pre->right) {  // 一直往右走，直到左子树的最右端
                    pre = pre->right;  // 前进到右孩子
                }
                pre->right = root->right;  // 把原来的右子树整体挂到前驱右边，保证先序顺序不丢失
                root->right = root->left;  // 整棵左子树搬到右侧，成为链表的后半段
                root->left = nullptr;  // 题目要求展开后左指针全为空
            }
            root = root->right;  // 沿右链前进；此刻右孩子正是先序遍历的下一个节点
        }
    }
};  // 类定义结束