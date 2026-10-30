// 题目：129. 求根节点到叶节点数字之和（Sum Root to Leaf Numbers）
// 思路：lambda 递归做 DFS，向下传递「已拼接的数字」s = s * 10 + val，到叶子时返回该数字，其余节点返回左右子树结果之和。
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
 */  // 上面的 TreeNode 结构体由判题器预先提供
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumNumbers(TreeNode* root) {  // root：二叉树根节点，返回所有根到叶路径数字之和
        function<int(TreeNode*, int)> dfs = [&](TreeNode* root, int s) -> int {  // 递归 lambda：root 是当前节点，s 是从根拼到父节点的数字
            if (!root) return 0;  // 空节点不贡献任何数字
            s = s * 10 + root->val;  // 把当前节点的值接到已拼数字的末尾
            if (!root->left && !root->right) return s;  // 叶子节点直接返回这个完整数字
            return dfs(root->left, s) + dfs(root->right, s);  // 非叶子：左右子树结果之和
        };  // lambda 定义结束
        return dfs(root, 0);  // 从根开始，初始数字为 0
    }  // sumNumbers 结束
};