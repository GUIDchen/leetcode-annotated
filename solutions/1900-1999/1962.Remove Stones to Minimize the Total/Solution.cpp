// 题目：1962. 移除石子使总数最小（Remove Stones to Minimize the Total）
// 思路：贪心——每次都对当前最大的一堆做 floor(x/2) 移除，收益最大；用大顶堆快速取最大值。
// 时间复杂度：O((n + k) log n)，每次堆操作 O(log n)；空间复杂度：O(n)，堆中保存所有石子堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minStoneSum(vector<int>& piles, int k) {  // piles 是每堆石子数，k 是最多操作次数
        priority_queue<int> pq;  // 大顶堆：每次都能 O(log n) 拿到当前最大的一堆
        for (int x : piles) {  // 遍历初始的石子堆
            pq.push(x);  // 把每堆石子数放入堆中
        }  // 结束 for
        while (k--) {  // 执行 k 次操作，k 减到 0 时循环自动结束
            int x = pq.top();  // 取出当前最大的那堆
            pq.pop();  // 从堆中移除它，待减半后重新入堆
            pq.push(x - x / 2);  // 该堆变为 x - floor(x/2)，即向下取整地移除一半
        }  // 结束 while
        int ans = 0;  // 累计剩余石子总数
        while (!pq.empty()) {  // 把堆里剩下的石子堆逐个弹出
            ans += pq.top();  // 累加当前堆的石子数
            pq.pop();  // 弹出，继续处理下一堆
        }  // 结束 while
        return ans;  // 返回最小化之后的总数
    }  // 结束方法
};  // 结束类