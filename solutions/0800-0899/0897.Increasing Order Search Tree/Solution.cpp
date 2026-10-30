// 题目：897. 递增顺序搜索树（Increasing Order Search Tree）
// 核心思路：中序遍历二叉搜索树得到升序序列，遍历时用 prev 指针把节点原地串成只有右孩子的链。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度，h 为树高。
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
    TreeNode* increasingBST(TreeNode* root) {  // root：原二叉搜索树的根
        TreeNode* dummy = new TreeNode(0, nullptr, root);  // 哑结点，它的 right 最终指向新树的根；先把原根挂上去方便递归
        TreeNode* prev = dummy;  // prev 始终指向结果链表的最后一个节点
        function<void(TreeNode*)> dfs = [&](TreeNode* root) {  // 中序遍历：按升序依次取出节点
            if (!root) {  // 空节点直接返回，递归出口
                return;  // 没有节点可处理
            }
            dfs(root->left);  // 先处理左子树，更小的值先接到链上
            prev->right = root;  // 当前节点接到链尾的右指针
            root->left = nullptr;  // 新树中每个节点都不能有左孩子
            prev = root;  // 链尾后移
            dfs(root->right);  // 最后处理右子树
        };
        dfs(root);  // 从根开始构建递增顺序搜索树
        return dummy->right;  // 跳过哑结点，返回真正的根
    }
};  // 类定义结束