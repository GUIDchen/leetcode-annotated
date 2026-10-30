// 题目：106. 从中序与后序遍历序列构造二叉树（Construct Binary Tree from Inorder and Postorder Traversal）
// 思路：后序序列的末尾元素一定是根，用哈希表在中序序列里 O(1) 找到根的下标，把序列切成左右两段后递归建树。
// 时间复杂度：O(n)，每个结点只创建一次；空间复杂度：O(n)，哈希表与递归栈。
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {  // inorder：中序序列；postorder：后序序列；返回构造出的树根
        unordered_map<int, int> d;  // 哈希表：记录「值 → 在 inorder 中的下标」，用来快速定位根
        int n = inorder.size();  // 结点总数
        for (int i = 0; i < n; ++i) {  // 先完整扫描一遍中序序列
            d[inorder[i]] = i;  // 记下每个值在中序中的位置
        }  // 建表结束
        function<TreeNode*(int, int, int)> dfs = [&](int i, int j, int n) -> TreeNode* {  // 递归函数：i 是中序区间起点，j 是后序区间起点，n 是当前子树的结点数
            if (n <= 0) {  // 区间为空，说明该子树不存在
                return nullptr;  // 空子树返回空指针
            }  // 空区间处理完毕
            int v = postorder[j + n - 1];  // 后序区间的最后一个元素就是当前子树的根值
            int k = d[v];  // 根值在中序中的下标，用它把中序区间切成左右两半
            auto l = dfs(i, j, k - i);  // 左子树：中序起点 i，后序起点 j，结点数是 k - i
            auto r = dfs(k + 1, j + k - i, n - k + i - 1);  // 右子树：中序起点 k+1，后序起点 j + 左子树大小，结点数是 n - 左子树大小 - 1
            return new TreeNode(v, l, r);  // 用根值新建结点，并把左右子树接上
        };  // 递归函数定义结束
        return dfs(0, 0, n);  // 整棵树：中序起点 0，后序起点 0，结点数为 n
    }  // 方法结束
};  // 题解类结束