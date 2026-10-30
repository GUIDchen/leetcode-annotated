// 题目：1199. 建造街区的最短时间（Minimum Time to Build Blocks）
// 思路：逆向合并——小根堆每次取最小的两块，丢掉较小的一块，把较大的一块加 split 后放回。
// 时间复杂度：O(n log n)，每次堆操作为 O(log n)；空间复杂度：O(n)，堆中存放各块的最优时间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minBuildTime(vector<int>& blocks, int split) {  // blocks 是各街区的建造耗时，split 是一次分裂耗时，返回全部建完的最短时间
        priority_queue<int, vector<int>, greater<int>> pq;  // 小根堆：每次都取当前最小的两个时间做合并
        for (int v : blocks) pq.push(v);  // 把所有街区的耗时依次入堆
        while (pq.size() > 1) {  // 堆里还剩两块以上，就继续两两合并
            pq.pop();  // 弹出较小的一块：合并后总时间由较大的那块决定，它可被完全覆盖
            int x = pq.top();  // 弹出次小的一块 x，它是这一组里真正决定耗时的部分
            pq.pop();  // 把这个次小值从堆中移除
            pq.push(x + split);  // 把 x + split 放回堆：等价于先花 split 分裂出一个人，再由他花 x 建完这一组
        }
        return pq.top();  // 堆里只剩一个总耗时，就是全部建完的最短时间
    }
};