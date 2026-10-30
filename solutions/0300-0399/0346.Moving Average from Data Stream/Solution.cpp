// 题目：346. 数据流中的移动平均值（Moving Average from Data Stream）
// 思路：用长度固定为 size 的环形数组保存最近的元素，同时维护窗口内元素之和；每次只需减去被覆盖的旧值、加上新值。
// 时间复杂度：构造 O(size)，next 为 O(1)；空间复杂度：O(size)，环形数组。
class MovingAverage {  // 移动平均值类
public:  // 构造函数与对外接口可见
    MovingAverage(int size) {  // size：滑动窗口大小，即最多保留最近多少个数据
        data.resize(size);  // 把环形数组一次性开到 size 个槽位，初值全 0
    }  // 构造函数体为空，初始化已完成

    double next(int val) {  // val：数据流新到的值；返回最近 size 个值的平均值
        int i = cnt % data.size();  // cnt % size 得到本轮要覆盖的槽位下标，cnt 递增即形成环形复用
        s += val - data[i];  // 窗口和先减去该槽位里的旧值，再加上新值，避免每次重新求和
        data[i] = val;  // 把新值写入槽位，替换掉被挤出窗口的旧值
        ++cnt;  // 已处理的数据个数加一，用来判断窗口是否已满
        return s * 1.0 / min(cnt, (int) data.size());  // 元素不足 size 个时按实际个数 cnt 求平均，满了之后按 size 求平均；乘 1.0 强制做浮点除法
    }  // next 方法结束

private:  // 私有成员只供内部使用
    int s = 0;  // 窗口内元素之和，随进出元素增量维护
    int cnt = 0;  // 累计处理过的元素个数，用于取模定位和计算真实窗口长度
    vector<int> data;  // 长度固定为 size 的环形数组，存放最近的元素
};  // 类定义结束

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */