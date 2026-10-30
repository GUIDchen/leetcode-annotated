// 题目：3157. 找到具有最小和的树的层数（Find the Level of Tree with Minimum Sum）
// 核心思路：BFS 逐层弹出节点并累加该层节点值之和，用 ans 记录当前和最小的层号；只在严格小于时更新，保证和相同时取更小的层号。
// 时间复杂度：O(n)，每个节点只入队出队各一次；空间复杂度：O(n)，队列最多同时存放最宽的一层节点。
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
    int minimumLevel(TreeNode* root) {  // root：二叉树根节点
        queue<TreeNode*> q{{root}};  // 队列初始化为只含根节点，用于层序遍历
        int ans = 0;  // 答案：和最小的层号，从 1 开始计数
        long long s = 1LL << 60;  // 当前最小层和，先用极大的哨兵值（2^60）初始化
        for (int level = 1; q.size(); ++level) {  // 外层循环：每轮处理一整层，level 为该层编号
            long long t = 0;  // 本层节点值之和
            for (int m = q.size(); m; --m) {  // 内层循环：用入队前的队列长度锁定「本层」恰好 m 个节点
                TreeNode* node = q.front();  // 取队首节点
                q.pop();  // 弹出队首
                t += node->val;  // 把该节点值累加到本层和中
                if (node->left) {  // 若存在左孩子
                    q.push(node->left);  // 左孩子入队，留给下一层处理
                }  // 左孩子分支结束
                if (node->right) {  // 若存在右孩子
                    q.push(node->right);  // 右孩子入队，留给下一层处理
                }  // 右孩子分支结束
            }  // 本层处理完毕
            if (s > t) {  // 只有严格更小才替换，保证和相同时保留更小的层号
                s = t;  // 更新最小层和
                ans = level;  // 更新答案层号
            }  // 更新分支结束
        }  // 队列为空说明所有层都处理完了
        return ans;  // 返回和最小的层号
    }  // 方法结束
};  // 类定义结束