// 题目：3319. 第 K 大的完美二叉子树的大小（K-th Largest Perfect Subtree Size in Binary Tree）
// 思路：后序 DFS 返回「以当前节点为根的子树大小」，不是完美二叉树则返回 -1；把所有完美子树的大小收集起来降序排序，取第 k 个。
// 时间复杂度：O(n log n)，n 为节点数（DFS 遍历每个节点一次，排序开销占主导）；空间复杂度：O(n)，递归栈与存放子树大小的数组。
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
    int kthLargestPerfectSubtree(TreeNode* root, int k) {  // root：二叉树根节点；k：要求的第 k 大
        vector<int> nums;  // 收集所有完美二叉子树的大小
        auto dfs = [&](this auto&& dfs, TreeNode* root) -> int {  // C++23 的显式 this 递归 lambda：返回子树大小，非完美返回 -1
            if (!root) {  // 空节点：空树视为完美
                return 0;  // 返回 0 作为「空子树是完美」的标记
            }
            int l = dfs(root->left);  // 递归求左子树：返回其大小，或 -1 表示不完美
            int r = dfs(root->right);  // 递归求右子树：同上
            if (l < 0 || l != r) {  // 任一子树不完美，或左右大小不同，当前树必然不完美
                return -1;  // -1 作为不完美的哨兵值向上传递
            }
            int cnt = l + r + 1;  // 左右同为完美且大小相同，加上根节点得到当前完美子树大小
            nums.push_back(cnt);  // 记录一个完美子树的大小
            return cnt;  // 把大小返回给父节点继续判断
        };
        dfs(root);  // 从根开始遍历，顺便填满 nums
        if (nums.size() < k) {  // 完美二叉子树不足 k 个
            return -1;  // 按题意返回 -1
        }
        ranges::sort(nums, greater<int>());  // C++20 ranges 版排序，greater<int> 使其降序
        return nums[k - 1];  // 下标 k-1 即第 k 大的大小
    }
};
