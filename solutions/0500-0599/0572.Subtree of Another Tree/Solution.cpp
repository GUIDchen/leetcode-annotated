// 题目：572. 另一棵树的子树（Subtree of Another Tree）
// 核心思路：枚举 root 中的每个结点作为可能起点，用 same 递归判断两棵子树是否完全相同。
// 时间复杂度：O(|root| * |subRoot|)，每个结点都要做一次匹配；空间复杂度：O(|root|) 递归栈。
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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {  // root 为被检索的大树，subRoot 为待匹配的子树
        if (!root) {  // 大树走到空节点，说明这条分支不可能再匹配到子树
            return false;  // 空树中不存在非空子树，故返回 false
        }
        return same(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);  // 三选一：以当前结点为根可完全相同，或答案在左子树，或答案在右子树
    }  // isSubtree 结束

    bool same(TreeNode* p, TreeNode* q) {  // 判断以 p、q 为根的两棵树是否结构相同且结点值全等
        if (!p || !q) {  // 至少有一边为空，无法继续逐值比较
            return p == q;  // 两边同时为空才算相同，一边空一边不空则不同
        }  // 空判断结束
        return p->val == q->val && same(p->left, q->left) && same(p->right, q->right);  // 根值相等，且左右子树也分别相同，才是同一棵树
    }  // same 结束
};  // 类定义结束
