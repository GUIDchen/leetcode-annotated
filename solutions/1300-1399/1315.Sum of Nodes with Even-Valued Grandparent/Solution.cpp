// 题目：1315. 祖父节点值为偶数的节点和（Sum of Nodes with Even-Valued Grandparent）
// 思路：自顶向下递归，把当前节点值作为子节点的「祖父值」传下去；祖父值为偶数时累加两个孩子的值。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度等于树高。
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
    int sumEvenGrandparent(TreeNode* root) {  // 求所有「祖父节点值为偶数」的节点之和
        function<int(TreeNode*, int)> dfs = [&](TreeNode* root, int x) {  // 递归 lambda：root 为当前节点，x 为其祖父节点的值（根节点祖父按奇数 1 处理）
            if (!root) {  // 空节点是递归边界
                return 0;  // 空节点贡献为 0
            }  // 空节点分支结束
            int ans = dfs(root->left, root->val) + dfs(root->right, root->val);  // 先递归累加左右子树答案，同时把当前节点值作为子节点的祖父值传下去
            if (x % 2 == 0) {  // 若祖父节点值为偶数，才统计当前节点的左右孩子
                if (root->left) {  // 存在左孩子时
                    ans += root->left->val;  // 左孩子的祖父正是当前节点，祖父为偶数则累加左孩子的值
                }  // 左孩子判断结束
                if (root->right) {  // 存在右孩子时
                    ans += root->right->val;  // 右孩子的祖父同为偶数，累加右孩子的值
                }  // 右孩子判断结束
            }  // 偶数祖父分支结束
            return ans;  // 返回以当前节点为根的子树中的合法节点和
        };  // lambda 定义结束
        return dfs(root, 1);  // 从根开始，根的祖父值记为奇数 1，保证根的孩子不会被误算
    }  // 方法结束
};  // 类定义结束