// 题目：731. 我的日程安排表 II（My Calendar II）
// 思路：map 维护时间轴上的差分（startTime 处 +1，endTime 处 -1）；每次插入后按时间顺序累加前缀和，若某处超过 2 说明出现三重预订，随即回滚。
// 时间复杂度：每次 book 需遍历整张 map，为 O(n)；空间复杂度：O(n)，map 中最多存 2n 个时间点。
class MyCalendarTwo {  // 日程表类，支持在允许双重预订的前提下判断是否会三重预订
public:  // 对外提供构造与 book 方法
    MyCalendarTwo() {  // 构造函数无需额外初始化
    }  // 构造函数体为空

    bool book(int startTime, int endTime) {  // startTime、endTime 是本次要预订的半开区间 [startTime, endTime)
        ++m[startTime];  // 在起点处记 +1，表示从这一刻开始多一段占用
        --m[endTime];  // 在终点处记 -1，表示这段占用到此结束
        int s = 0;  // s 用来扫描前缀和，即当前时刻的预订层数
        for (auto& [_, v] : m) {  // 按时间从小到大遍历差分表（结构化绑定里 _ 是时间点，v 是差值）
            s += v;  // 累加差分得到当前时刻的预订层数
            if (s > 2) {  // 层数超过 2 说明这次预订会造成三重预订
                --m[startTime];  // 回滚起点处的 +1
                ++m[endTime];  // 回滚终点处的 -1
                return false;  // 预订失败并返回 false
            }  // if 分支结束
        }  // for 循环结束
        return true;  // 全程层数都不超过 2，预订成功
    }  // book 方法结束

private:  // 私有成员区
    map<int, int> m;  // map：键是时间点，值是差分，天然按时间排序
};  // MyCalendarTwo 类定义结束

// 下面是 LeetCode 判题器自动生成的调用示例，原样保留，仅作说明
/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(startTime,endTime);
 */
