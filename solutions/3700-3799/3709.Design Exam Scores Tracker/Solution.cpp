// 3709. Design Exam Scores Tracker（3709. 设计考试分数记录器）
// 核心思路：记录的时间天然严格递增，因此用 times 存时间、pre 存前缀和；查询时用二分找出两个端点下标，前缀和相减即得闭区间总分。
// 复杂度：record 为 O(1)，totalScore 为 O(log n)，空间 O(n)。
class ExamTracker {  // 定义考试分数记录器类
public:  // 公有成员：构造函数与两个接口
    ExamTracker() {  // 构造函数，先放入两个哨兵元素
        times.push_back(0);  // 下标 0 放时间哨兵 0，保证二分查找有下界
        pre.push_back(0LL);  // 下标 0 放前缀和哨兵 0
    }  // 构造函数结束

    void record(int time, int score) {  // 记录一条成绩：time 递增，score 为本次得分
        times.push_back(time);  // 时间序列天然有序，直接追加到末尾
        pre.push_back(pre.back() + score);  // 前缀和累加，pre[i] 表示前 i 条记录的总分
    }  // record 方法结束

    long long totalScore(int startTime, int endTime) {  // 返回闭区间 [startTime, endTime] 内的总分
        int l = lower_bound(times.begin(), times.end(), startTime) - times.begin() - 1;  // 第一个 >= startTime 的下标减一，即时间 < startTime 的记录条数
        int r = lower_bound(times.begin(), times.end(), endTime + 1) - times.begin() - 1;  // 第一个 >= endTime + 1 的下标减一，即时间 <= endTime 的记录条数（把闭区间右端转为开区间）
        return pre[r] - pre[l];  // 前缀和相减得到区间总分
    }  // totalScore 方法结束

private:  // 私有成员：时间序列与前缀和数组
    vector<int> times;  // 按下标递增保存的记录时间
    vector<long long> pre;  // 与 times 一一对应的前缀和
};  // 类定义结束

/**
 * Your ExamTracker object will be instantiated and called as such:
 * ExamTracker* obj = new ExamTracker();
 * obj->record(time,score);
 * long long param_2 = obj->totalScore(startTime,endTime);
 */
