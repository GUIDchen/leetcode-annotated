// 题目：108. 将有序数组转换为二叉搜索树（Convert Sorted Array to Binary Search Tree）
// 思路：有序数组的中点作根，左右两半分别递归建子树，这样左右高度差不超过 1，自然是平衡 BST。
// 时间复杂度：O(n)，每个元素建一个结点；空间复杂度：O(log n)，递归栈深度为树高。
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {  // nums 是升序数组，返回一棵平衡二叉搜索树的根
        auto dfs = [&](this auto&& dfs, int l, int r) -> TreeNode* {  // C++23 的显式对象参数（this auto&&），让 lambda 能递归调用自己
            if (l > r) {  // 区间 [l, r] 为空，说明没有元素可建
                return nullptr;  // 空区间对应空子树
            }  // 空区间处理完毕
            int mid = (l + r) >> 1;  // 取区间中点（向下取整）作根，保证左右两侧元素个数尽量相等
            return new TreeNode(nums[mid], dfs(l, mid - 1), dfs(mid + 1, r));  // 根取 nums[mid]，左右两半递归建子树后挂上去
        };  // 递归 lambda 定义结束
        return dfs(0, nums.size() - 1);  // 从整个数组区间开始建树
    }  // 方法结束
};  // 题解类结束
