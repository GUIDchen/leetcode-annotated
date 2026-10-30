// 题目：501. 二叉搜索树中的众数（Find Mode in Binary Search Tree）
// 思路：对 BST 做中序遍历得到非递减序列，只用「前驱节点」在线统计当前值的连续出现次数；超过历史最大值就重置答案，相等则追加。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，递归栈最坏 O(n)（结果数组另计）。
// 下面这段是 LeetCode 判题器提供的 TreeNode 结构体定义，属于平台模板而非解题代码
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
public:  // 成员与方法对外可见
    TreeNode* prev;  // 中序遍历中的前一个节点，用来判断当前值是否与它相同
    int mx, cnt;  // mx 是历史最大出现次数，cnt 是当前值已连续出现的次数
    vector<int> ans;  // 存放所有出现次数等于 mx 的值

    vector<int> findMode(TreeNode* root) {  // 求 BST 中所有众数
        dfs(root);  // 一趟中序遍历即可完成统计
        return ans;  // 返回收集到的众数
    }  // 方法体结束

    void dfs(TreeNode* root) {  // 中序遍历：左子树 -> 根 -> 右子树，保证相同值连续出现
        if (!root) return;  // 空节点直接返回，是递归出口
        dfs(root->left);  // 先递归处理左子树（BST 中更小的值）
        cnt = prev != nullptr && prev->val == root->val ? cnt + 1 : 1;  // 与前驱值相同则次数加一，否则这个值从 1 重新计数
        if (cnt > mx) {  // 出现次数刷新了历史最大值
            ans.clear();  // 之前统计出的众数全部失效，先清空
            ans.push_back(root->val);  // 把当前值记为新的候选众数
            mx = cnt;  // 更新历史最大次数
        } else if (cnt == mx)  // 次数恰好等于历史最大值，当前值也是众数之一（分支体在下一行）
            ans.push_back(root->val);  // 追加这个众数
        prev = root;  // 把当前节点记为前驱，供中序遍历的下一个节点比较
        dfs(root->right);  // 最后递归处理右子树（BST 中更大的值）
    }  // dfs 方法结束
};  // 类定义结束