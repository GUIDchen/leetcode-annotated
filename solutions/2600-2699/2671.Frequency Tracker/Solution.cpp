// 题目：2671. 频率跟踪器（Frequency Tracker）
// 思路：cnt 存「数字 → 出现次数」，freq 存「出现次数 → 拥有该次数的数字个数」；增删时只搬动这两个计数。
// 时间复杂度：add / deleteOne / hasFrequency 均为 O(1)；空间复杂度：O(n)，两张哈希表最多存 n 个不同数字及其次数。
class FrequencyTracker {  // 频率跟踪器：cnt 记每个数的出现次数，freq 记每种出现次数被多少个数拥有
public:  // 对外提供的三个接口
    FrequencyTracker() {  // 构造函数：两张哈希表默认构造为空表，不需要额外初始化
    }  // 构造函数体为空，这里结束

    void add(int number) {  // 让 number 的出现次数加 1
        freq[cnt[number]]--;  // number 原来的次数是 cnt[number]，先把它从「旧次数」的计数里减掉
        cnt[number]++;  // number 的出现次数真正加 1
        freq[cnt[number]]++;  // 再把 number 计入「新次数」的计数里
    }  // add 结束

    void deleteOne(int number) {  // 若 number 存在就把它的出现次数减 1，不存在则什么都不做
        if (cnt[number]) {  // cnt[number] 为 0 说明这个数从未出现过，直接跳过本次操作
            freq[cnt[number]]--;  // 从「旧次数」的计数中移除 number
            cnt[number]--;  // number 的出现次数减 1
            freq[cnt[number]]++;  // 把 number 加入「新次数」的计数；减到 0 时落到 freq[0]，不会干扰查询
        }  // if 结束
    }  // deleteOne 结束

    bool hasFrequency(int frequency) {  // 查询是否存在恰好出现了 frequency 次的数字
        return freq[frequency] > 0;  // freq[frequency] 是出现次数等于 frequency 的数字个数，大于 0 即存在
    }  // hasFrequency 结束

private:  // 内部状态，不对外暴露
    unordered_map<int, int> cnt;  // cnt[x] = 数字 x 当前出现的次数
    unordered_map<int, int> freq;  // freq[t] = 出现次数恰好为 t 的数字个数
};  // 类定义结束

// 以下调用示例由 LeetCode 判题器提供，原样保留
/**
 * Your FrequencyTracker object will be instantiated and called as such:
 * FrequencyTracker* obj = new FrequencyTracker();
 * obj->add(number);
 * obj->deleteOne(number);
 * bool param_3 = obj->hasFrequency(frequency);
 */  // 调用示例结束