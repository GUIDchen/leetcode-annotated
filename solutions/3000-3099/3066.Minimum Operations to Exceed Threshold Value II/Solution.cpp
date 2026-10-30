// 题目：3066. 超过阈值的最少操作数 II（Minimum Operations to Exceed Threshold Value II）
// 思路：贪心 + 小根堆；每次取最小的两个数 x<=y 合并成 x*2+y 放回堆，直到堆顶不小于 k。
// 时间复杂度：O(n log n)，每次操作两次出堆一次入堆；空间复杂度：O(n)，堆存全部元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums, int k) {  // nums 是输入数组，k 是阈值，返回最少操作次数
        using ll = long long;  // 给 long long 起别名，防止 x * 2 + y 在 32 位下溢出
        priority_queue<ll, vector<ll>, greater<ll>> pq;  // 小根堆：greater 让堆顶始终是最小值，便于每次取出最小的两个数
        for (int x : nums) {  // 把数组元素全部加入堆
            pq.push(x);  // 入堆，堆内部自动调整顺序
        }  // 初始化完毕
        int ans = 0;  // ans 记录已经执行的操作次数
        for (; pq.size() > 1 && pq.top() < k; ++ans) {  // 堆顶仍小于 k 且至少有两个元素时继续合并
            ll x = pq.top();  // 取出当前最小值 x
            pq.pop();  // 弹出 x
            ll y = pq.top();  // 再取最小值 y（此时 y 是剩余元素中最小的，故 x <= y）
            pq.pop();  // 弹出 y
            pq.push(x * 2 + y);  // 按规则把两数合并成新值再放回堆，参与后续比较
        }  // 一次操作结束，循环头会执行 ++ans
        return ans;  // 返回总操作次数；若堆中不足两个元素则无法继续，直接结束
    }  // 方法结束
};  // 类定义结束
