// 题目：1367. 二叉树中的链表（Linked List in Binary Tree）
// 思路：外层枚举树中每个节点作为起点，内层 DFS 同时沿链表 next 与树的左右孩子向下匹配。
// 时间复杂度：O(N·L)，N 为树节点数、L 为链表长度；空间复杂度：O(H + L)，递归栈深度。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
    bool isSubPath(ListNode* head, TreeNode* root) {  // head：链表头；root：二叉树根；判断链表的节点序列是否落在某条向下的路径上
        if (!root) {  // 当前子树为空，不可能再匹配
            return false;  // 返回 false
        }  // if 结束
        return dfs(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);  // 以 root 为起点尝试匹配，或递归到左右子树里寻找新的起点
    }  // 方法结束

    bool dfs(ListNode* head, TreeNode* root) {  // 深度优先匹配：从 root 开始能否依次匹配完链表剩余部分
        if (!head) {  // 链表已经走完，说明前面全部匹配成功
            return true;  // 返回 true
        }  // if 结束
        if (!root || head->val != root->val) {  // 树节点为空，或当前值不相等，都算匹配失败
            return false;  // 返回 false
        }  // if 结束
        return dfs(head->next, root->left) || dfs(head->next, root->right);  // 链表指针后移，左右子树任一条路径成功即可
    }  // 方法结束
};  // 类定义结束