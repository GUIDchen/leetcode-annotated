// 题目：508. 出现次数最多的子树元素和（Most Frequent Subtree Sum）
// 思路：后序 DFS 求每棵子树的元素和，用哈希表统计每个和出现的次数并维护最大频次，最后收集频次等于最大值的和。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，哈希表与递归栈。
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
    vector<int> findFrequentTreeSum(TreeNode* root) {  // root：二叉树根节点；返回出现次数最多的子树元素和
        unordered_map<int, int> cnt;  // 哈希表：子树和 → 出现次数
        int mx = 0;  // 记录目前出现过的最大频次
        function<int(TreeNode*)> dfs = [&](TreeNode* root) -> int {  // 内部递归函数：返回以 root 为根的子树元素和；按引用捕获 cnt 与 mx
            if (!root) {  // 空节点没有元素
                return 0;  // 空子树的元素和记为 0
            }  // 递归出口处理结束
            int s = root->val + dfs(root->left) + dfs(root->right);  // 后序遍历：左子树和 + 右子树和 + 根节点值
            mx = max(mx, ++cnt[s]);  // 该和的次数加一，并尝试更新最大频次
            return s;  // 把子树和返回给父节点
        };  // lambda 定义结束
        dfs(root);  // 从根开始遍历整棵树，顺便把所有子树和都统计好
        vector<int> ans;  // 收集答案
        for (const auto& [k, v] : cnt) {  // 遍历哈希表中的每一对 (子树和, 出现次数)
            if (v == mx) {  // 出现次数等于最大频次
                ans.push_back(k);  // 该子树和是答案之一
            }  // 判断结束
        }  // 遍历结束
        return ans;  // 返回所有出现次数最多的子树和
    }  // 方法结束
};  // 类定义结束
