// 题目：285. 二叉搜索树中的中序后继（Inorder Successor in BST）🔒
// 思路：利用 BST 的有序性：节点值大于 p 时它可能是答案，先记录再去左子树找更小的候选；否则答案一定在右子树，最终记录的最后一个候选就是中序后继。
// 时间复杂度：O(h)，h 为树高；空间复杂度：O(1)，只用了一个指针。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {  // root：BST 根节点，p：目标节点，返回其中序后继
        TreeNode* ans = nullptr;  // ans 保存目前最接近的候选后继
        while (root) {  // 沿树向下搜索，直到走到空节点
            if (root->val > p->val) {  // 当前节点大于 p，说明它可能是后继
                ans = root;  // 先把它记为当前最佳候选
                root = root->left;  // 再往左子树找是否有更小的合法候选
            } else {  // 当前节点不大于 p，后继必然在右子树
                root = root->right;  // 转向右子树继续搜索
            }
        }
        return ans;  // 返回最后一个记录的候选，即中序后继
    }
};