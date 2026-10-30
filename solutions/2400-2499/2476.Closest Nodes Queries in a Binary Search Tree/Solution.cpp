// 题目：2476. 二叉搜索树最近节点查询（Closest Nodes Queries in a Binary Search Tree）
// 思路：中序遍历 BST 得到升序数组 nums，再对每个查询 x 二分出「小于 x 的最大值」和「大于等于 x 的最小值」，不存在则填 -1。
// 时间复杂度：O(n + q log n)，一次遍历加每个查询两次二分；空间复杂度：O(n)，存中序数组与答案。
// 下面是题目给定的二叉树结点定义（判题器会注入），保持原样不作改动
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
public:  // 方法对外可见，判题器据此调用
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {  // root 是 BST 根；queries 是查询数组；返回每个查询的 [小于 x 的最大值, 大于等于 x 的最小值]
        vector<int> nums;  // 存放中序遍历结果，BST 的中序序列天然升序
        function<void(TreeNode*)> dfs = [&](TreeNode* root) {  // 递归中序遍历，把结点值按中序顺序收进 nums
            if (!root) {  // 空结点直接返回，作为递归出口
                return;  // 递归出口，什么都不做
            }
            dfs(root->left);  // 先递归遍历左子树，得到所有更小的值
            nums.push_back(root->val);  // 再访问根结点，保证升序排列
            dfs(root->right);  // 最后递归遍历右子树，得到所有更大的值
        };
        dfs(root);  // 从根开始做一次完整的中序遍历
        vector<vector<int>> ans;  // 每个查询对应一个长度为 2 的答案向量
        int n = nums.size();  // 中序数组长度，用于后续下标越界判断
        for (int& x : queries) {  // 逐个处理查询
            int i = lower_bound(nums.begin(), nums.end(), x + 1) - nums.begin() - 1;  // 第一个 ≥ x+1 的位置减一即「小于 x 的最大值」的下标
            int j = lower_bound(nums.begin(), nums.end(), x) - nums.begin();  // 第一个 ≥ x 的位置即「大于等于 x 的最小值」的下标
            int mi = i >= 0 && i < n ? nums[i] : -1;  // 下标越界说明不存在小于 x 的值，按题目要求填 -1
            int mx = j >= 0 && j < n ? nums[j] : -1;  // 下标越界说明不存在大于等于 x 的值，填 -1
            ans.push_back({mi, mx});  // 按题目顺序放入 [最小值, 最大值]
        }  // 查询循环结束
        return ans;  // 返回全部查询的答案
    }  // 方法结束
};  // 类定义结束