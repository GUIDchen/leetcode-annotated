// 题目：105. 从前序与中序遍历序列构造二叉树（Construct Binary Tree from Preorder and Inorder Traversal）
// 思路：前序首元素是根，用哈希表在中序里 O(1) 定位根的位置 k，左子树长度 k-j，据此切分两个区间并递归建树。
// 时间复杂度：O(n)，建哈希表 O(n)、每个节点只建一次；空间复杂度：O(n)，哈希表与递归栈的规模。
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {  // preorder 前序序列，inorder 中序序列，返回建好的树根
        int n = preorder.size();  // 节点总个数
        unordered_map<int, int> d;  // 哈希表：值 → 它在中序序列中的下标，用于 O(1) 定位根
        for (int i = 0; i < n; ++i) {  // 遍历一遍中序序列
            d[inorder[i]] = i;  // 记录每个值的中序下标（题目保证值互不相同）
        }
        function<TreeNode*(int, int, int)> dfs = [&](int i, int j, int n) -> TreeNode* {  // 递归 lambda：i 为前序起点，j 为中序起点，n 为本段节点数
            if (n <= 0) {  // 区间为空表示没有节点
                return nullptr;  // 返回空子树
            }
            int v = preorder[i];  // 前序区间的第一个元素就是本子树的根值
            int k = d[v];  // 根在中序序列中的位置，用它把中序区间切成左、右两段
            TreeNode* l = dfs(i + 1, j, k - j);  // 左子树：前序紧随根之后，中序从 j 开始，长度 k-j
            TreeNode* r = dfs(i + 1 + k - j, k + 1, n - 1 - (k - j));  // 右子树：前序跳过左子树长度，中序从 k+1 开始，长度 n-1-(k-j)
            return new TreeNode(v, l, r);  // 用根值和已建好的左右子树构造节点并返回
        };
        return dfs(0, 0, n);  // 从整个前序、中序区间开始递归建树
    }
};