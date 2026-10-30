// 题目：3506. 查找消除细菌菌株所需时间（Find Time Required to Eliminate Bacterial Strains）
// 思路：小顶堆模拟。每轮弹出耗时最小的菌株（它必然最先被消除），再取新的堆顶加上 splitTime 放回堆中，表示这次分裂的代价累加到它身上；堆中只剩一个元素时，该值就是消除全部菌株的总时间。
// 时间复杂度：O(n log n)，每个元素进出堆各 O(log n)；空间复杂度：O(n)，堆中最多存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minEliminationTime(vector<int>& timeReq, int splitTime) {  // timeReq：每种菌株被消除所需时间；splitTime：一次分裂的耗时；返回消除全部菌株的总时间
        using ll = long long;  // 给 long long 起短别名，累加时避免 int 溢出
        priority_queue<ll, vector<ll>, greater<ll>> pq;  // 小顶堆（greater 让最小值在堆顶），按耗时从小到大取用
        for (int v : timeReq) {  // 遍历每个菌株的耗时
            pq.push(v);  // 逐个入堆，建立初始的小顶堆
        }  // 建堆完成
        while (pq.size() > 1) {  // 堆中多于一个菌株时继续合并
            pq.pop();  // 弹出耗时最小的菌株，它会被最先消除
            ll x = pq.top();  // 取出新的堆顶，即当前次小的菌株
            pq.pop();  // 把这次小的菌株也暂时移出堆
            pq.push(x + splitTime);  // 它承担一次分裂耗时后重新入堆，成为下一轮的候选
        }  // 全部合并结束
        return pq.top();  // 堆中仅剩的唯一值即累计的消除时间
    }  // 方法结束
};  // 类定义结束