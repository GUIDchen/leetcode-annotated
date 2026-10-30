// 题目：480. 滑动窗口中位数（Sliding Window Median）
// 思路：大根堆 small 存较小的一半、小根堆 large 存较大的一半，中位数只看两个堆顶；删除用「懒删除」哈希表记录待删次数，元素冒到堆顶时才真正弹出。
// 时间复杂度：每次 add/remove 是 O(log k)，共 n 次操作即 O(n log k)；空间复杂度：O(k)，两个堆和延迟删除表都只存窗口内的元素。
class MedianFinder {  // 辅助结构：维护长度固定为 k 的滑窗，支持加元素、删元素、取中位数
public:  // 对外暴露的操作
    MedianFinder(int k) {  // k 是窗口大小，决定中位数取单个堆顶还是两个堆顶的平均
        this->k = k;  // 记录窗口大小
    }  // 结束构造

    void addNum(int num) {  // 向结构中加入一个新元素
        if (small.empty() || num <= small.top()) {  // small 为空，或新值不大于 small 的最大值，说明它属于较小的一半
            small.push(num);  // 放入存较小一半的大根堆（堆顶是这一半的最大值）
            ++smallSize;  // 较小一半的有效元素数加一
        } else {  // 否则新值大于 small 的最大值，属于较大的一半
            large.push(num);  // 放入存较大一半的小根堆（堆顶是这一半的最小值）
            ++largeSize;  // 较大一半的有效元素数加一
        }  // 结束 if-else 分支
        reblance();  // 加入后两堆大小可能失衡，调整一次
    }  // 结束 addNum

    void removeNum(int num) {  // 从结构中删除一个元素：窗口右移时移出最左端的那个值
        ++delayed[num];  // 懒删除：先只记录待删次数，真正弹出留到它成为堆顶时再做
        if (num <= small.top()) {  // 要删的值属于较小一半
            --smallSize;  // 较小一半的有效元素数减一
            if (num == small.top()) {  // 只有它正压在堆顶时才需要真正弹出
                prune(small);  // 清理 small 堆顶的过期元素
            }  // 结束内层 if
        } else {  // 否则要删的值属于较大一半
            --largeSize;  // 较大一半的有效元素数减一
            if (num == large.top()) {  // 位于 large 的堆顶
                prune(large);  // 清理 large 堆顶的过期元素
            }  // 结束内层 if
        }  // 结束 if-else 分支
        reblance();  // 删除后重新平衡两堆
    }  // 结束 removeNum

    double findMedian() {  // 返回当前窗口的中位数
        return k & 1 ? small.top() : ((double) small.top() + large.top()) / 2.0;  // 奇数个元素时就是 small 堆顶；偶数时取两个堆顶的平均，先转 double 避免整数除法
    }  // 结束 findMedian

private:  // 以下为该结构的内部数据与私有工具函数
    priority_queue<int> small;  // 较小一半：大根堆，堆顶是这一半的最大值
    priority_queue<int, vector<int>, greater<int>> large;  // 较大一半：小根堆，堆顶是这一半的最小值
    unordered_map<int, int> delayed;  // 懒删除计数：值 → 尚未真正从堆中弹出的次数
    int smallSize = 0;  // small 中的有效元素个数（不含待删除的）
    int largeSize = 0;  // large 中的有效元素个数（不含待删除的）
    int k;  // 窗口大小，即当前应有的元素总数

    template <typename T>  // 模板参数让大根堆和小根堆复用同一段清理逻辑
    void prune(T& pq) {  // 反复弹出堆顶中已被标记为待删除的元素
        while (!pq.empty() && delayed[pq.top()]) {  // 堆非空且堆顶仍有待删标记时才需要处理
            if (--delayed[pq.top()] == 0) {  // 用掉一次待删标记
                delayed.erase(pq.top());  // 计数归零就从哈希表移除，避免残留 0 干扰后面的判断
            }  // 结束内层 if
            pq.pop();  // 真正弹出这个已过期的堆顶
        }  // 结束 while 循环
    }  // 结束 prune

    void reblance() {  // 维持「small 比 large 多 0 个或 1 个元素」这一不变式
        if (smallSize > largeSize + 1) {  // small 太多，挪一个到 large
            large.push(small.top());  // 把 small 的最大值交给 large
            small.pop();  // 再从 small 弹出它
            --smallSize;  // 同步两堆的有效元素计数
            ++largeSize;  // 同上：large 加一
            prune(small);  // 挪走后 small 的新堆顶也可能已过期
        } else if (smallSize < largeSize) {  // 反之 large 太多，挪一个到 small
            small.push(large.top());  // 把 large 的最小值交给 small
            large.pop();  // 再从 large 弹出它
            ++smallSize;  // 同步两堆的有效元素计数
            --largeSize;  // 同上：large 减一
            prune(large);  // large 的新堆顶同样需要清理
        }  // 结束 if-else 分支
    }  // 结束 reblance
};  // 结束辅助结构

class Solution {  // 主解：用上面的 MedianFinder 维护长度 k 的滑动窗口
public:  // 对外暴露的题解方法
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {  // nums 是原数组，k 是窗口长度；返回每个窗口的中位数
        MedianFinder finder(k);  // 构造窗口大小为 k 的维护器
        for (int i = 0; i < k; ++i) {  // 先把前 k 个元素装进窗口
            finder.addNum(nums[i]);  // 逐个加入
        }  // 结束第一个 for 循环
        vector<double> ans = {finder.findMedian()};  // 记录第一个窗口的中位数
        for (int i = k; i < nums.size(); ++i) {  // 窗口每右移一格
            finder.addNum(nums[i]);  // 加入新的右端元素
            finder.removeNum(nums[i - k]);  // 移出原来的左端元素
            ans.push_back(finder.findMedian());  // 记录当前窗口的中位数
        }  // 结束第二个 for 循环
        return ans;  // 返回所有窗口的中位数序列
    }  // 结束题解方法
};  // 结束题解类