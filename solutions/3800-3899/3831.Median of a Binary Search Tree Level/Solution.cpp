// 3831. 二叉搜索树某一层的中位数 / Median of a Binary Search Tree Level（中等）
// 核心思路：对二叉搜索树做中序遍历，访问目标层的顺序天然递增，因此收集到该层所有值后直接取下标 size/2 的元素即为中位数。
// 复杂度：遍历整棵树，时间 O(n)，递归栈与结果数组空间 O(h + k)。
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
class Solution {  // 设计一个求 BST 指定层中位数的算法
public:  // 对外接口区
    int levelMedian(TreeNode* root, int level) {  // 返回第 level 层（根为第 0 层）的中位数，该层为空时返回 -1
        vector<int> nums;  // 按中序顺序收集目标层节点值

        auto dfs = [&](this auto&& dfs, TreeNode* node, int i) -> void {  // 递归 lambda：i 为当前层号，根节点层号为 0
            if (!node) {  // 空节点直接返回
                return;  // 结束当前递归分支
            }
            dfs(node->left, i + 1);  // 先递归左子树，层号加一
            if (i == level) {  // 当前节点恰好在目标层
                nums.push_back(node->val);  // 记录该节点的值（中序保证递增有序）
            }
            dfs(node->right, i + 1);  // 再递归右子树，层号加一
        };

        dfs(root, 0);  // 从根节点（第 0 层）开始遍历
        return nums.empty() ? -1 : nums[nums.size() / 2];  // 该层为空返回 -1，否则取有序数组的中间下标即上中位数
    }
};
