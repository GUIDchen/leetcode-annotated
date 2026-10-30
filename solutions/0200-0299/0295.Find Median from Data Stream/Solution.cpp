// 题目：295. 数据流的中位数（Find Median from Data Stream）
// 思路：对顶堆——大顶堆存较小的一半、小顶堆存较大的一半，并始终保持小顶堆元素个数为 ⌈n/2⌉。
// 时间复杂度：addNum 为 O(log n)、findMedian 为 O(1)；空间复杂度：O(n)，两个堆共存 n 个数。
class MedianFinder {  // 数据流中位数：用两个堆把数据分成较小、较大两半
public:  // 对外接口
    MedianFinder() {  // 构造函数，两个堆默认为空
    }  // 构造函数体为空

    void addNum(int num) {  // num：新加入数据流的数
        maxQ.push(num);  // 先无条件压入大顶堆（较小的一半）
        minQ.push(maxQ.top());  // 再把大顶堆堆顶（较小一半中的最大值）挪到小顶堆
        maxQ.pop();  // 弹出刚被挪走的堆顶

        if (minQ.size() > maxQ.size() + 1) {  // 平衡条件：小顶堆最多比大顶堆多 1 个元素，保证中位数只在堆顶
            maxQ.push(minQ.top());  // 超出时把小顶堆堆顶（较大一半中的最小值）挪回大顶堆
            minQ.pop();  // 弹出刚被挪走的堆顶
        }  // if 块结束
    }  // addNum 方法结束

    double findMedian() {  // 返回当前数据流的中位数
        return minQ.size() == maxQ.size() ? (minQ.top() + maxQ.top()) / 2.0 : minQ.top();  // 两堆等长取中间两数平均，否则多出的那个元素就在小顶堆堆顶
    }  // findMedian 方法结束

private:  // 内部数据结构
    priority_queue<int> maxQ;  // 大顶堆：存较小的一半元素
    priority_queue<int, vector<int>, greater<int>> minQ;  // 小顶堆：存较大的一半元素
};  // 类定义结束

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
