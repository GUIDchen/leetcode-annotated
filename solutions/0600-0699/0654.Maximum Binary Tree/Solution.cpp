// 题目：654. 最大二叉树（Maximum Binary Tree）
// 核心思路：区间最大值作根，左右两段递归建树（分治）。
// 时间复杂度：最坏 O(n^2)（每次线性找最大值）；空间复杂度：O(n)（节点数与递归栈）。
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
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {  // 入口：在整个下标区间 [0, n-1] 上递归建树
        return dfs(nums, 0, nums.size() - 1);  // 闭区间 [0, n-1] 交给 dfs 处理
    }

    TreeNode* dfs(vector<int>& nums, int l, int r) {  // dfs：在闭区间 [l, r] 内取最大值作根，再递归左右两段
        if (l > r) return nullptr;  // 区间为空（l 越过 r）说明没有节点，返回空指针
        int i = l;  // i 记录区间最大值下标，先假设在左端点
        for (int j = l; j <= r; ++j) {  // 顺序扫描整个闭区间 [l, r]
            if (nums[i] < nums[j]) {  // 发现更大的元素就把最大值下标移过去
                i = j;  // 更新最大值下标
            }
        }
        TreeNode* root = new TreeNode(nums[i]);  // 用最大值作为当前子树的根节点
        root->left = dfs(nums, l, i - 1);  // 左子树只能在最大值左侧 [l, i-1] 中递归选根
        root->right = dfs(nums, i + 1, r);  // 右子树只能在最大值右侧 [i+1, r] 中递归选根
        return root;  // 返回当前子树的根
    }
};  // 题解类定义结束
