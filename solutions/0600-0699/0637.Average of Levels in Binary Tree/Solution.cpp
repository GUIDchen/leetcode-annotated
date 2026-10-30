// 题目：637. 二叉树的层平均值（Average of Levels in Binary Tree）
// 思路：BFS 逐层遍历，每轮先取当前层节点数，把整层出队求和并把孩子入队，最后算出该层平均值。
// 时间复杂度：O(n)，每个节点进出队列一次；空间复杂度：O(w)，w 为树的最大宽度。
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
    vector<double> averageOfLevels(TreeNode* root) {  // 返回二叉树每一层节点值的平均值（自顶向下）
        queue<TreeNode*> q{{root}};  // BFS 队列，先把根节点放入；用 initializer_list 构造
        vector<double> ans;  // ans 按层序保存每层的平均值
        while (!q.empty()) {  // 队列非空说明还有待处理的层
            int n = q.size();  // 先记下当前层的节点数；循环里只消耗这一层的节点
            long long s = 0;  // 当前层节点值之和，用 long long 防止累加溢出
            for (int i = 0; i < n; ++i) {  // 逐个处理本层的 n 个节点
                root = q.front();  // 取出队首节点
                q.pop();  // 队首出队
                s += root->val;  // 把节点值累加进本层总和
                if (root->left) {  // 左孩子非空
                    q.push(root->left);  // 左孩子入队，它属于下一层
                }  // 左孩子处理结束
                if (root->right) {  // 右孩子非空
                    q.push(root->right);  // 右孩子入队，它属于下一层
                }  // 右孩子处理结束
            }  // 本层节点处理完毕
            ans.push_back(s * 1.0 / n);  // 本层平均值：乘 1.0 转为浮点后再除，避免整数除法
        }  // 本层处理结束
        return ans;  // 按层序返回每层的平均值
    }  // 方法结束
};  // 类定义结束