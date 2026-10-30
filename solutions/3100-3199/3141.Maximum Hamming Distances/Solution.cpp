// 题目：3141. 最大汉明距离（Maximum Hamming Distances）
// 思路：以 nums 中所有数为源做多源 BFS，求出每个 m 位掩码到最近源数的距离；x 的最远数就是它的按位取反，故答案为 m 减去到补码的距离。
// 时间复杂度：O(2^m * m)，每个掩码只入队一次并枚举 m 个邻居；空间复杂度：O(2^m)，dist 数组与 BFS 队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maxHammingDistances(vector<int>& nums, int m) {  // nums：源数组（会被原地改写为答案）；m：二进制位数
        int dist[1 << m];  // dist[mask]：该掩码到最近源数的汉明距离
        memset(dist, -1, sizeof(dist));  // 全部置为 -1，表示还没被 BFS 访问到
        queue<int> q;  // 多源 BFS 队列
        for (int x : nums) {  // 所有源数一起入队
            dist[x] = 0;  // 源数到自己的距离是 0
            q.push(x);  // 作为 BFS 的第 0 层
        }  // 入队结束
        for (int k = 1; q.size(); ++k) {  // 逐层扩展：k 是当前层对应的距离，队列为空即结束
            for (int t = q.size(); t; --t) {  // 先固定本层节点数，避免新入队的节点被当成同一层处理
                int x = q.front();  // 取出队首节点（一个掩码）
                q.pop();  // 弹出队首
                for (int i = 0; i < m; ++i) {  // 枚举要翻转的比特位
                    int y = x ^ (1 << i);  // 异或实现单比特翻转，得到只差一位的邻居
                    if (dist[y] == -1) {  // 只处理还没被访问过的邻居
                        dist[y] = k;  // 记录它到最近源数的距离
                        q.push(y);  // 加入队列，等下一层再扩展
                    }  // 访问标记判断结束
                }  // 比特位枚举结束
            }  // 本层节点处理结束
        }  // 多源 BFS 结束
        for (int& x : nums) {  // 按引用遍历，原地把源数改写成答案
            x = m - dist[x ^ ((1 << m) - 1)];  // 全 1 掩码与 x 异或得到补码，最远距离 = m 减去到补码的最短距离
        }  // 改写结束
        return nums;  // 返回原地修改后的数组
    }  // 方法结束
};  // 类定义结束