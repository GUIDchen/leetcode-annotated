// 题目：1161. 最大层内元素和（Maximum Level Sum of a Binary Tree）
// 思路：BFS 逐层遍历二叉树，累计每层节点值之和，记录和最大的最小层号。
// 时间复杂度：O(n)，每个节点入队一次；空间复杂度：O(n)，队列最宽为最底层节点数。
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
class Solution {  // LeetCode 题解类
public:  // 解题方法对外公开
    int maxLevelSum(TreeNode* root) {  // 返回元素和最大的层号（从 1 开始，和相同取最小层号）
        queue<TreeNode*> q{{root}};  // BFS 队列，初始只有根节点
        int mx = INT_MIN;  // 历史最大层和，初始为最小整数
        int ans = 0;  // 最大层和对应的层号
        int i = 0;  // 当前层号计数器
        while (!q.empty()) {  // 队列非空说明还有层没处理
            ++i;  // 进入下一层，层号加一
            int s = 0;  // 当前层的元素和
            for (int n = q.size(); n; --n) {  // 固定处理当前层的节点数（队列长度在循环中会变化）
                root = q.front();  // 取出队首节点
                q.pop();  // 弹出队首节点
                s += root->val;  // 累加节点值到当前层和
                if (root->left) {  // 有左孩子
                    q.push(root->left);  // 左孩子入队，留给下一层
                }  // 结束左孩子分支
                if (root->right) {  // 有右孩子
                    q.push(root->right);  // 右孩子入队，留给下一层
                }  // 结束右孩子分支
            }  // 结束当前层处理
            if (mx < s) {  // 当前层和严格更大时才更新
                mx = s;  // 记录新的最大层和
                ans = i;  // 记录对应层号（相等时保留更小的层号）
            }  // 结束更新分支
        }  // 结束层遍历
        return ans;  // 返回最大层和所在层号
    }  // 方法结束
};  // 类定义结束
