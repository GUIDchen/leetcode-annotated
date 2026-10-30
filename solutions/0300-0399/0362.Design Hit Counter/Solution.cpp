// 题目：362. 敲击计数器（Design Hit Counter）
// 思路：按时间顺序保存所有敲击时间戳，查询时二分出第一个落在 [t-299, t] 窗口内的时间戳，用末尾下标差得到计数。
// 时间复杂度：hit 均摊 O(1)，getHits O(log n)；空间复杂度：O(n)，保存全部时间戳。
class HitCounter {  // 敲击计数器类
public:  // 对外接口
    HitCounter() {  // 构造函数
    }  // 无需初始化成员

    void hit(int timestamp) {  // timestamp 时刻记录一次敲击
        ts.push_back(timestamp);  // 按时间顺序追加（题目保证时间戳单调递增）
    }  // 方法结束

    int getHits(int timestamp) {  // 统计含当前时刻在内最近 300 秒的敲击数
        return ts.end() - lower_bound(ts.begin(), ts.end(), timestamp - 300 + 1);  // 二分找第一个 >= 窗口左端的时间点，其后元素个数即窗口内敲击数
    }  // 方法结束

private:  // 私有成员
    vector<int> ts;  // 记录所有敲击的时间戳
};

// 下面是 LeetCode 判题器自动生成的调用示例（代码本体已在上面结束）
/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */  // 调用示例结束