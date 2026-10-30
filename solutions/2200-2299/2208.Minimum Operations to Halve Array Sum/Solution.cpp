// 题目：2208. 将数组和减半的最少操作次数（Minimum Operations to Halve Array Sum）
// 核心思路：贪心——每次都对当前最大的数减半，能让总和下降得最快；用大顶堆反复取最大值即可。
// 时间复杂度：O(n log n)，每次操作是一次堆弹出加一次插入；空间复杂度：O(n)，堆中存放 n 个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int halveArray(vector<int>& nums) {  // nums 是待减半的数组
        priority_queue<double> pq;  // 大顶堆，堆顶始终是当前最大的数
        double s = 0;  // 记录数组总和；用浮点是因为减半会产生小数
        for (int x : nums) {  // 遍历原数组
            s += x;  // 累加元素得到总和
            pq.push((double) x);  // 元素转成 double 后入堆
        }
        s /= 2.0;  // 目标是让总和减少「原总和的一半」，于是 s 改记还需要减少的量
        int ans = 0;  // 记录操作次数
        while (s > 0) {  // 需要减少的量还没减够，就继续操作
            double t = pq.top() / 2.0;  // 取堆顶最大值的一半，这是本次操作能减少的量
            pq.pop();  // 弹出原来的最大值
            s -= t;  // 剩余需要减少的量扣掉本次减少量
            pq.push(t);  // 减半后的值重新入堆，供后续继续减半
            ++ans;  // 操作次数加一
        }
        return ans;  // 返回最少操作次数
    }
};
