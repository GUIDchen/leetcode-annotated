// 题目：729. 我的日程安排表 I（My Calendar I）
// 思路：用 map 以「结束时间 → 开始时间」维护所有已预订区间；插入前只查结束时间大于 start 的第一个区间，若它的开始时间小于 end 则重叠。
// 时间复杂度：每次 book 为 O(log n) 的 lower_bound；空间复杂度：O(n)，保存 n 个已预订区间。
class MyCalendar {  // 日程表类，只支持一次预订不冲突的判断
public:  // 对外提供构造与 book 方法
    MyCalendar() {  // 构造函数无需任何初始化
    }  // 构造函数体为空

    bool book(int startTime, int endTime) {  // startTime、endTime 是本次要预订的半开区间 [startTime, endTime)
        auto e = m.lower_bound(startTime + 1);  // ends 作为 map 的键已排好序，lower_bound(startTime+1) 找到第一个结束时间大于 startTime 的区间
        if (e != m.end() && e->second < endTime) {  // 若该区间的起点小于本次 endTime，说明两段在时间轴上相交
            return false;  // 冲突则拒绝本次预订
        }  // if 分支结束
        m[endTime] = startTime;  // 不冲突，以 endTime 为键、startTime 为值登记该区间
        return true;  // 登记成功返回 true
    }  // book 方法结束

private:  // 私有成员区
    map<int, int> m;  // map：键是结束时间，值是开始时间，按结束时间有序，便于二分查找
};  // MyCalendar 类定义结束

// 下面是 LeetCode 判题器自动生成的调用示例，原样保留，仅作说明
/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(startTime,endTime);
 */
