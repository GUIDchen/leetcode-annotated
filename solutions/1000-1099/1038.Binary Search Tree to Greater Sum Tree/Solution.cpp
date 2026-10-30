// 题目：1038. 从二叉搜索树到更大和树（Binary Search Tree to Greater Sum Tree）
// 思路：按「右 → 根 → 左」的反中序遍历，用成员变量 s 累加已访问节点值，把每个节点的值就地改写为累加和。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
/**
 * Definition for a binary tree node.  （二叉树节点结构体，由判题器提供）
 * struct TreeNode {  （节点结构体开始）
 *     int val;  （节点值）
 *     TreeNode *left;  （左孩子指针）
 *     TreeNode *right;  （右孩子指针）
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}  （默认构造：值 0，左右空）
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}  （指定值构造）
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}  （指定值与左右孩子的构造）
 * };  （结构体结束）
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    TreeNode* bstToGst(TreeNode* root) {  // root 是 BST 根节点，返回转换后的根（结构不变，值被改写）
        int s = 0;  // 累加器：已经遍历过的（更大的）节点值之和
        auto dfs = [&](this auto&& dfs, TreeNode* root) {  // 泛型递归 lambda：反中序遍历整棵树
            if (!root) {  // 空节点直接返回
                return;  // 空节点无需处理
            }  // 空节点判断结束
            dfs(root->right);  // 先走右子树，保证按值从大到小访问
            s += root->val;  // 把当前节点值累加进总和
            root->val = s;  // 当前节点新值 = 所有不小于它的节点值之和
            dfs(root->left);  // 最后走左子树，处理更小的那些节点
        };  // 递归 lambda 结束
        dfs(root);  // 从根节点启动遍历，整棵树的节点值被就地改写
        return root;  // 返回根节点
    }  // 方法结束
};  // 类结束