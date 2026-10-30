// 题目：1167. 连接木棍的最低费用（Minimum Cost to Connect Sticks）
// 思路：贪心 + 小根堆，每次合并当前最短的两根木棍，合并代价为新长度并累加，新木棍放回堆中继续合并。
// 时间复杂度：O(n log n)，每次取两次堆顶再插入新值；空间复杂度：O(n)，堆里最多同时保存 n 根木棍。
class Solution {  // 题解类
public:
    int connectSticks(vector<int>& sticks) {  // 把木棍两两连接成一根，求最小总费用
        priority_queue<int, vector<int>, greater<int>> pq;  // 小根堆：保证每次都能取出当前最短的两根木棍
        for (auto& x : sticks) {  // 把所有木棍长度放进堆里
            pq.push(x);  // 长度入堆
        }  // for 结束
        int ans = 0;  // 累计总费用
        while (pq.size() > 1) {  // 堆中只剩一根木棍时结束
            int x = pq.top();  // 取出最短的一根
            pq.pop();  // 弹出堆顶
            int y = pq.top();  // 取出第二短的一根
            pq.pop();  // 弹出堆顶
            int z = x + y;  // 合并后的新木棍长度，也正是本次合并花费的代价
            ans += z;  // 累加本次费用
            pq.push(z);  // 新木棍放回堆中，继续参与后续合并
        }  // while 结束
        return ans;  // 返回最小总费用
    }  // 方法结束
};  // 类定义结束