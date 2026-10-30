// 题目：933. 最近的请求次数（Number of Recent Calls）
// 思路：用队列维护滑动窗口。每次 ping 先入队，再把早于 t-3000 的队首弹掉，剩下的元素个数就是答案。
// 时间复杂度：均摊 O(1)，每个请求最多入队、出队各一次；空间复杂度：O(W)，W 为 3000 毫秒窗口内的请求数。
class RecentCounter {  // 按题目要求实现的计数器类
public:  // 构造函数与 ping 方法对外可见
    queue<int> q;  // 队列只保存最近 3000 毫秒内的请求时间，队首是最早的那个

    RecentCounter() {  // 构造函数：空的队列就表示还没有任何请求
    }  // 成员已默认初始化，因此函数体为空

    int ping(int t) {  // t 是本次请求的时间戳（毫秒，严格递增）
        q.push(t);  // 新请求先入队
        while (q.front() < t - 3000) q.pop();  // 把落在 [t-3000, t] 之外的旧请求全部弹出
        return q.size();  // 队内元素个数即最近 3000 毫秒内的请求次数
    }
};

// 下面三行是 LeetCode 判题器给出的调用示例（本题实现的是类而不是单个函数）。
/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */