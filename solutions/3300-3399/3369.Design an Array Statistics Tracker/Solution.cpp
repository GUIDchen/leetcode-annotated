// 题目：3369. 设计数组统计跟踪器（Design an Array Statistics Tracker）
// 思路：双堆加延迟删除求中位数，FIFO 队列维护加入顺序，总和存均值，map/set 记录频次求众数。
// 时间复杂度：addNumber / removeFirstAddedNumber 均摊 O(log n)，三个查询均 O(1)；空间复杂度：O(n)。
class MedianFinder {  // 一个用双堆 + 延迟删除实现的可增可删中位数结构
public:  // 对外接口：加数、删数、取中位数
    void addNum(int num) {  // 加入一个数，按大小分到两个堆里
        if (small.empty() || num <= small.top()) {  // 左堆为空，或 num 不大于左堆堆顶，说明它属于较小的那一半
            small.push(num);  // 压入左半部分（大根堆）
            ++smallSize;  // 左半部分有效计数 +1
        } else {  // 否则它属于较大的那一半
            large.push(num);  // 压入右半部分（小根堆）
            ++largeSize;  // 右半部分有效计数 +1
        }  // 结束分支
        reblance();  // 插入后两堆大小关系可能被破坏，需要重新平衡
    }  // addNum 结束

    void removeNum(int num) {  // 删除一个数：采用延迟删除，先记账，等它浮到堆顶再真正弹出
        ++delayed[num];  // 为 num 记一次待删除次数
        if (num <= small.top()) {  // 判断这个数本应属于左半部分
            --smallSize;  // 左半部分有效计数 -1（不计待删除元素）
            if (num == small.top()) {  // 它正好在左堆顶时才能立刻真删
                prune(small);  // 清理左堆顶所有待删除元素
            }  // 结束堆顶判断
        } else {  // 否则它属于右半部分
            --largeSize;  // 右半部分有效计数 -1
            if (num == large.top()) {  // 同样要等它来到右堆顶才能真删
                prune(large);  // 清理右堆顶所有待删除元素
            }  // 结束堆顶判断
        }  // 结束分支
        reblance();  // 删除后重新平衡两堆
    }  // removeNum 结束

    int findMedian() {  // 返回当前中位数
        return smallSize == largeSize ? large.top() : small.top();  // 两堆元素个数相等时中位数在右堆顶，否则在左堆顶（左堆最多多一个）
    }  // findMedian 结束

private:  // 私有成员与内部工具函数
    priority_queue<int> small;  // 大根堆：保存较小的一半数
    priority_queue<int, vector<int>, greater<int>> large;  // 小根堆：保存较大的一半数
    unordered_map<int, int> delayed;  // 每个值还有多少次待删除（延迟删除的记账表）
    int smallSize = 0;  // 左半部分有效元素个数（不含待删除的）
    int largeSize = 0;  // 右半部分有效元素个数

    template <typename T>  // 泛型模板：两种堆类型共用同一套清理逻辑
    void prune(T& pq) {  // 把堆顶所有处于待删除状态的元素真正弹出
        while (!pq.empty() && delayed[pq.top()]) {  // 堆非空且堆顶还记有待删除次数时继续
            if (--delayed[pq.top()] == 0) {  // 先消耗一次待删除计数
                delayed.erase(pq.top());  // 计数归零就从哈希表里删掉这个键，避免表里留下垃圾项
            }  // 结束计数判断
            pq.pop();  // 真正把堆顶元素弹出
        }  // 清理循环结束
    }  // prune 结束

    void reblance() {  // 调整两堆大小：保证左堆元素个数等于右堆或多一个
        if (smallSize > largeSize + 1) {  // 左半部分偏多（超过一个）
            large.push(small.top());  // 把左堆的最大元素移给右堆
            small.pop();  // 从左堆弹出该元素
            --smallSize;  // 左堆计数 -1
            ++largeSize;  // 右堆计数 +1
            prune(small);  // 左堆顶可能正是一个延迟删除的元素，顺手清理
        } else if (smallSize < largeSize) {  // 否则右半部分偏多
            small.push(large.top());  // 把右堆的最小元素移给左堆
            large.pop();  // 从右堆弹出该元素
            ++smallSize;  // 左堆计数 +1
            --largeSize;  // 右堆计数 -1
            prune(large);  // 顺手清理右堆顶的延迟删除元素
        }  // 结束分支
    }  // reblance 结束
};  // MedianFinder 类定义结束

class StatisticsTracker {  // 滑动窗口统计器：维护均值、中位数与众数
private:  // 私有状态
    queue<int> q;  // 先进先出队列：按加入顺序保存元素，用于移除最早加入的那个
    long long s = 0;  // 当前窗口元素总和，用于 O(1) 求均值
    unordered_map<int, int> cnt;  // 每个值的出现次数，用于维护众数
    MedianFinder medianFinder;  // 双堆中位数查找器
    set<pair<int, int>> ts;  // 有序集合：元素为 (-出现次数, 数值)，begin() 即众数

public:  // 对外接口
    StatisticsTracker() {}  // 构造函数：成员都有默认初始值，无需额外初始化

    void addNumber(int number) {  // 加入一个新元素
        q.push(number);  // 入队，记录加入顺序
        s += number;  // 累加窗口总和
        ts.erase({-cnt[number], number});  // 先按旧计数把该数的旧记录从有序集合中删掉
        cnt[number]++;  // 出现次数加一
        medianFinder.addNum(number);  // 同步插入双堆，以便后续求中位数
        ts.insert({-cnt[number], number});  // 再按新计数把更新后的记录插回有序集合
    }  // addNumber 结束

    void removeFirstAddedNumber() {  // 移除最早加入的元素（窗口按 FIFO 淘汰）
        int number = q.front();  // 取出队首元素
        q.pop();  // 队首出队
        s -= number;  // 总和减去该值
        ts.erase({-cnt[number], number});  // 从有序集合删掉它当前的 (-次数, 数值) 记录
        cnt[number]--;  // 出现次数减一
        if (cnt[number] > 0) {  // 计数仍大于 0 才需要把更新后的记录放回去
            ts.insert({-cnt[number], number});  // 重新插入更新后的记录
        }  // 结束计数判断
        medianFinder.removeNum(number);  // 双堆中同步删除该数
    }  // removeFirstAddedNumber 结束

    int getMean() {  // 当前窗口元素的平均值（向下取整）
        return static_cast<int>(s / q.size());  // 整数除法即向下取整；q.size() 是当前窗口元素个数
    }  // getMean 结束

    int getMedian() {  // 当前窗口元素的中位数
        return medianFinder.findMedian();  // 交给双堆结构查询中位数
    }  // getMedian 结束

    int getMode() {  // 当前窗口元素的众数（并列时取数值最小者，由有序集合的键顺序保证）
        return ts.begin()->second;  // 集合按 -次数 升序排列，begin() 就是次数最多、同次数时数值最小的元素
    }  // getMode 结束
};  // StatisticsTracker 类定义结束
