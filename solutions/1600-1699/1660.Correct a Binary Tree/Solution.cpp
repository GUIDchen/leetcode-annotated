// 题目：1660. 纠正二叉树（Correct a Binary Tree）
// 思路：非法边一定指向已被访问过的节点，DFS 时若发现右孩子已在访问集合中就把它剪掉。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，访问集合与递归栈。
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
    TreeNode* correctBinaryTree(TreeNode* root) {  // root：被篡改的二叉树根节点；返回纠正后的根节点
        unordered_set<TreeNode*> vis;  // 哈希集合记录已经访问过的节点，用于判断指针是否回指
        function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* root) -> TreeNode* {  // 定义递归函数：返回修正后的子树根节点
            if (!root || vis.count(root->right)) {  // 空节点直接返回；右孩子已被访问过说明这条边非法（指向祖先/重复节点）
                return nullptr;  // 返回空指针，表示把这条非法边剪掉
            }  // 递归边界分支结束
            vis.insert(root);  // 标记当前节点已访问，供后代检测
            root->right = dfs(root->right);  // 递归修正右子树，非法连接会被置空
            root->left = dfs(root->left);  // 递归修正左子树
            return root;  // 当前节点本身合法，返回它
        };  // lambda 定义结束
        return dfs(root);  // 从根节点开始 DFS 修正
    }  // 方法结束
};  // 类定义结束