// 题目：2471. 逐层排序二叉树所需的最少操作数目（Minimum Number of Operations to Sort a Binary Tree by Level）
// 核心思路：BFS 逐层取出节点值，把每层的值替换成「排序后的名次」得到 0..n-1 的排列，再用置换环求最少交换次数，各层结果相加。
// 时间复杂度：O(n·log n)，每层排序并把值映射成名次；空间复杂度：O(n)，队列与每层的临时数组。
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
    int minimumOperations(TreeNode* root) {  // root 是二叉树根节点，返回使每一层都升序所需的最少交换次数
        queue<TreeNode*> q{{root}};  // BFS 队列，初始只放根节点
        int ans = 0;  // 累计每一层需要的最少交换次数
        auto f = [](vector<int>& t) {  // f：把一层节点值映射成排序后的名次，再用置换环统计最少交换次数
            int n = t.size();  // 这一层的节点个数
            vector<int> alls(t.begin(), t.end());  // 复制一份节点值，用来排序
            sort(alls.begin(), alls.end());  // 得到这一层的升序序列
            unordered_map<int, int> m;  // 值 → 排序后的名次
            int ans = 0;  // 本层的最少交换次数（与外层 ans 同名，但作用域更小）
            for (int i = 0; i < n; ++i) m[alls[i]] = i;  // 为每个值建立名次索引
            for (int i = 0; i < n; ++i) t[i] = m[t[i]];  // 把节点值替换成名次，问题变成把排列排成 0..n-1
            for (int i = 0; i < n; ++i) {  // 逐个位置归位，按置换的环来数交换次数
                while (t[i] != i) {  // 当前位置不对就继续交换，直到归位
                    swap(t[i], t[t[i]]);  // 把 i 位置上的元素换到它该去的名次位置
                    ++ans;  // 一次交换记一次操作
                }
            }
            return ans;  // 返回本层的最少交换次数
        };  // f 这个 lambda 定义结束
        while (!q.empty()) {  // 按层 BFS，直到所有节点都处理完
            vector<int> t;  // 收集当前这一层的所有节点值
            for (int n = q.size(); n; --n) {  // 先把队列长度固定为本层节点数，循环恰好处理本层全部节点
                auto node = q.front();  // 取出队首节点
                q.pop();  // 队首出队
                t.emplace_back(node->val);  // 记录本层的一个节点值
                if (node->left) q.push(node->left);  // 有左孩子就入队，作为下一层
                if (node->right) q.push(node->right);  // 有右孩子就入队，作为下一层
            }
            ans += f(t);  // 累加本层的最少交换次数
        }
        return ans;  // 返回整棵树所需的交换总次数
    }
};