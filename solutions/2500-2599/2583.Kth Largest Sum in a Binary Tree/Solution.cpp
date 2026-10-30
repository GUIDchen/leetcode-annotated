// 题目：2583. 二叉树中的第 K 大层和（Kth Largest Sum in a Binary Tree）
// 思路：用 BFS 逐层遍历二叉树，累加每层节点值得到层和，把层和收集到数组，降序排序后取第 k 大；层数不足 k 时返回 -1。
// 时间复杂度：O(n + L log L)，n 为节点数、L 为层数；空间复杂度：O(n)，队列与层和数组最多各存 O(n) 个元素。
/**  // 题目给出的二叉树节点定义注释块
 * Definition for a binary tree node.  // 二叉树节点定义
 * struct TreeNode {  // 节点结构体：值、左孩子、右孩子
 *     int val;  // 节点值
 *     TreeNode *left;  // 左孩子指针
 *     TreeNode *right;  // 右孩子指针
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}  // 默认构造：值 0、左右为空
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}  // 只给值的构造
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}  // 给值和孩子指针的构造
 * };  // 结构体定义结束
 */  // 注释块结束
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long kthLargestLevelSum(TreeNode* root, int k) {  // root 为根节点，k 为要求的第几大；返回第 k 大层和
        vector<long long> arr;  // 保存每一层的节点值之和；用 long long 防溢出
        queue<TreeNode*> q{{root}};  // BFS 队列，初始化只放根节点
        while (!q.empty()) {  // 队列非空说明还有待处理的层
            long long t = 0;  // 当前层的节点值累加和，每层开始时清零
            for (int n = q.size(); n; --n) {  // 先固定本层节点个数，循环这么多次只处理这一层
                root = q.front();  // 取出队首节点
                q.pop();  // 把它从队列中移除
                t += root->val;  // 把该节点的值累加到本层和
                if (root->left) {  // 左孩子存在才入队
                    q.push(root->left);  // 左孩子留到下一层处理
                }
                if (root->right) {  // 右孩子存在才入队
                    q.push(root->right);  // 右孩子留到下一层处理
                }
            }
            arr.push_back(t);  // 本层处理完毕，把该层和存入数组
        }
        if (arr.size() < k) {  // 层数不足 k，不存在第 k 大层和
            return -1;  // 按题意返回 -1
        }
        sort(arr.rbegin(), arr.rend());  // 用反向迭代器降序排序，使 arr[0] 成为最大层和
        return arr[k - 1];  // 下标 k-1 正好是第 k 大层和
    }
};