// 题目：98. 验证二叉搜索树（Validate Binary Search Tree）
// 思路：BST 的中序遍历序列必须严格递增，用一个 prev 记录前驱节点，一边中序遍历一边比较大小。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，h 为树高，即递归栈的最大深度。
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
    bool isValidBST(TreeNode* root) {  // root：待验证的二叉树根，返回整棵树是否为合法 BST
        TreeNode* prev = nullptr;  // 记录中序遍历中刚刚访问过的节点（前驱），初值空表示还没访问过任何节点
        function<bool(TreeNode*)> dfs = [&](TreeNode* root) {  // 递归 lambda：对以 root 为根的子树做中序遍历校验
            if (!root) {  // 空节点不包含任何键值
                return true;  // 空子树天然满足 BST 性质，返回合法
            }
            if (!dfs(root->left)) {  // 先递归校验左子树：左子树全部键值都必须小于当前值
                return false;  // 左子树已不合法，无需继续，直接向上传递失败
            }
            if (prev && prev->val >= root->val) {  // 中序序列必须严格递增，因此前驱值不能大于等于当前值
                return false;  // 出现逆序（含相等），说明不是合法 BST
            }
            prev = root;  // 校验通过，把当前节点更新为前驱，供右子树中的节点比较
            return dfs(root->right);  // 最后校验右子树，其返回值即为本子树的结果
        };
        return dfs(root);  // 从整棵树的根开始做中序遍历校验
    }
};