// 题目：101. 对称二叉树（Symmetric Tree）
// 思路：把「是否对称」转化为「左右两棵子树是否互为镜像」：根值相等，且左的左对应右的右、左的右对应右的左。
// 时间复杂度：O(n)，每个节点最多比较一次；空间复杂度：O(h)，h 为树高，递归栈深度。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x, left), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isSymmetric(TreeNode* root) {  // root：待判定的树根，返回整棵树是否左右对称
        auto dfs = [&](this auto&& dfs, TreeNode* root1, TreeNode* root2) -> bool {  // C++23 显式对象参数，让 lambda 能递归调用自己
            if (root1 == root2) {  // 两指针相同（含同时为 nullptr）说明这一对镜像位置一致
                return true;  // 直接判为匹配
            }
            if (!root1 || !root2 || root1->val != root2->val) {  // 一侧为空或值不相等，镜像关系不成立
                return false;  // 立即失败，交给上层短路
            }
            return dfs(root1->left, root2->right) && dfs(root1->right, root2->left);  // 交叉匹配：左的左对右的右、左的右对右的左
        };
        return dfs(root->left, root->right);  // 从根的两个孩子开始做镜像匹配（root 为空时两侧同为 nullptr 也成立）
    }
};
