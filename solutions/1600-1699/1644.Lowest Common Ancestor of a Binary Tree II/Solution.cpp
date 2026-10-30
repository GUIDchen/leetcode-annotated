// 题目：1644. 二叉树的最近公共祖先 II（Lowest Common Ancestor of a Binary Tree II）
// 思路：后序 DFS 返回「以当前节点为根的子树里是否出现 p 或 q」；左、右两支各含一个，或当前节点本身是 p/q 而另一支含另一个，则该节点即答案。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高 h。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */  // 节点结构体由判题器提供，这里只是题面说明，不参与逻辑
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外开放
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {  // root：二叉树根；p、q：两个目标节点，返回它们的最近公共祖先
        dfs(root, p, q);  // 先做一次后序 DFS，答案会在遍历过程中写入成员变量 ans
        return ans;  // 返回 DFS 确定下来的最近公共祖先
    }  // 方法结束

private:  // 私有成员区
    TreeNode* ans = nullptr;  // ans 保存最近公共祖先，DFS 过程中被赋值，初值为空

    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) {  // dfs 返回值：以 root 为根的子树中是否出现过 p 或 q
        if (!root) {  // 空节点显然不含目标节点
            return false;  // 返回 false
        }  // 空节点分支结束
        bool l = dfs(root->left, p, q);  // 递归左子树，得到左子树中是否出现 p 或 q
        bool r = dfs(root->right, p, q);  // 递归右子树，得到右子树中是否出现 p 或 q
        if (l && r) {  // 左右子树各含一个目标节点，当前节点就是最近公共祖先
            ans = root;  // 记录答案
        }  // 左右各含一个的分支结束
        if ((l || r) && (root->val == p->val || root->val == q->val)) {  // 当前节点本身就是 p 或 q，且另一支里出现了另一个目标节点
            ans = root;  // 记录答案
        }  // 当前节点为目标节点之一的分支结束
        return l || r || root->val == p->val || root->val == q->val;  // 当前节点、左子树、右子树任意一处出现 p/q 就向上返回 true
    }  // dfs 方法结束
};  // 类定义结束