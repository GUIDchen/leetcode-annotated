// 题目：1448. 统计二叉树中好节点的数目（Count Good Nodes in Binary Tree）
// 核心思路：DFS 向下传递「从根到当前节点路径上的最大值 mx」，节点值不小于 mx 即为好节点，然后带上新的最大值继续递归。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高（递归栈深度）。
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
    int goodNodes(TreeNode* root) {  // 返回二叉树中好节点的个数
        int ans = 0;  // 计数器，记录好节点的数量
        function<void(TreeNode*, int)> dfs = [&](TreeNode* root, int mx) {  // 递归 lambda：mx 是根到当前节点路径上的最大值，[&] 按引用捕获外面的 ans
            if (!root) {  // 空节点直接返回，作为递归的终止条件
                return;  // 不需要做任何事，直接回溯
            }  // if 分支结束
            if (mx <= root->val) {  // 当前节点值不小于路径最大值，说明它是好节点
                ++ans;  // 好节点计数加一
                mx = root->val;  // 把路径最大值更新为当前节点值，供子树使用
            }  // if 分支结束
            dfs(root->left, mx);  // 递归处理左子树，带上更新后的路径最大值
            dfs(root->right, mx);  // 递归处理右子树，带上更新后的路径最大值
        };  // lambda 定义结束
        dfs(root, -1e6);  // 从根开始 DFS，根到根的路径最大值取一个足够小的初值 -1e6
        return ans;  // 返回好节点总数
    }  // goodNodes 方法结束
};  // 类定义结束
