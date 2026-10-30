// 题目：515. 在每个树行中找最大值（Find Largest Value in Each Tree Row）
// 思路：BFS 逐层遍历，每层用一个变量维护最大值，处理完一层就把它加入答案数组。
// 时间复杂度：O(n)，每个节点进出队各一次；空间复杂度：O(n)，队列最多保存一层节点（答案数组另计）。
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
    vector<int> largestValues(TreeNode* root) {  // 返回二叉树每一行的最大值
        vector<int> ans;  // 逐行存放每一层的最大值
        if (!root) {  // 空树直接返回空数组，避免把空指针入队
            return ans;  // 提前返回空结果
        }  // 空树分支结束
        queue<TreeNode*> q{{root}};  // BFS 队列，初始只放根节点
        while (q.size()) {  // 队列非空说明还有层未处理
            int x = INT_MIN;  // 本层最大值初值取最小整数，任何节点值都能刷新它
            for (int i = q.size(); i; --i) {  // 固定次数弹出，正好处理完当前这一层
                TreeNode* node = q.front();  // 取出队首节点
                q.pop();  // 把它从队列移除
                x = max(x, node->val);  // 用当前节点值刷新本层最大值
                if (node->left) {  // 左孩子存在
                    q.push(node->left);  // 左孩子进入下一层
                }  // 左孩子分支结束
                if (node->right) {  // 右孩子存在
                    q.push(node->right);  // 右孩子进入下一层
                }  // 右孩子分支结束
            }  // 当前层处理完毕
            ans.push_back(x);  // 记录本层最大值
        }  // 所有层处理完毕
        return ans;  // 返回按层收集的最大值数组
    }  // 方法结束
};  // 类定义结束
