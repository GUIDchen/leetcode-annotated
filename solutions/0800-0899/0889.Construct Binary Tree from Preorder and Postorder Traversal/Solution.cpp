// 题目：889. 从前序与后序遍历序列构造二叉树（Construct Binary Tree from Preorder and Postorder Traversal）
// 思路：前序首元素是根，前序第二个元素必为左子树根；用后序下标表定位它，算出左子树大小，再递归切分两个区间。
// 时间复杂度：O(n)，建表与建树各线性；空间复杂度：O(n)，下标表与递归栈。
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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {  // preorder 前序序列，postorder 后序序列
        unordered_map<int, int> pos;  // 后序「值 → 下标」的映射，用来 O(1) 求出左子树的规模
        int n = postorder.size();  // 结点个数
        for (int i = 0; i < n; ++i) {  // 遍历后序序列建立映射
            pos[postorder[i]] = i;  // 记下每个值在后序遍历中的位置
        }  // 映射建立完毕
        function<TreeNode*(int, int, int, int)> dfs = [&](int a, int b, int c, int d) -> TreeNode* {  // dfs(a,b,c,d)：用 preorder[a..b] 与 postorder[c..d] 还原出一棵子树
            if (a > b) {  // 区间为空，说明没有结点
                return nullptr;  // 空区间对应空子树
            }  // 空区间分支结束
            TreeNode* root = new TreeNode(preorder[a]);  // 前序区间的第一个元素就是当前子树的根
            if (a == b) {  // 区间只剩一个结点，是叶子
                return root;  // 叶子没有左右子树，直接返回
            }  // 叶子分支结束
            int i = pos[preorder[a + 1]];  // 前序第二个元素是左子树根，它在后序中的位置 i 分隔了左右子树
            int m = i - c + 1;  // 左子树的结点个数 = i - c + 1
            root->left = dfs(a + 1, a + m, c, i);  // 递归构造左子树：前序 a+1..a+m，后序 c..i
            root->right = dfs(a + m + 1, b, i + 1, d - 1);  // 递归构造右子树：前序 a+m+1..b，后序去掉末尾的根即 i+1..d-1
            return root;  // 返回构造好的当前根结点
        };  // 递归 lambda 定义结束
        return dfs(0, n - 1, 0, n - 1);  // 整棵树的区间就是两个序列的完整范围
    }  // 方法结束
};  // 类定义结束