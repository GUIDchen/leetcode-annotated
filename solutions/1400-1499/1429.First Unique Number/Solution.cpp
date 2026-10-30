// 题目：1429. 第一个唯一数字（First Unique Number）
// 思路：哈希表记录每个值的出现次数，双端队列按出现顺序保存候选值；查询时从队头弹掉已重复的值。
// 时间复杂度：add O(1)，showFirstUnique 均摊 O(1)；空间复杂度：O(n)，n 为出现过的不同值个数。
class FirstUnique {  // 设计题：维护「每个值的出现次数」+「按插入顺序排列的候选队列」
public:  // 构造函数与两个接口对外可见
    FirstUnique(vector<int>& nums) {  // 用初始数组构造：统计频次，同时把每个数按顺序入队
        for (int& v : nums) {  // 逐个处理初始数字
            ++cnt[v];  // 频次加一；unordered_map 对缺失的键会先默认初始化为 0
            q.push_back(v);  // 原样入队，保留「谁先出现」的顺序信息
        }  // 初始数组遍历结束
    }  // 构造函数结束

    int showFirstUnique() {  // 返回当前第一个只出现一次的数字，没有则返回 -1
        while (q.size() && cnt[q.front()] != 1) q.pop_front();  // 队头可能已经重复，一直弹出直到队头频次恰为 1 或队列为空
        return q.size() ? q.front() : -1;  // 队列非空则队头就是答案，否则返回 -1
    }  // 方法结束

    void add(int value) {  // 动态追加一个数字
        ++cnt[value];  // 频次加一，它可能因此从唯一变成重复
        q.push_back(value);  // 入队尾；是否唯一留到查询时按频次判断
    }  // 方法结束

private:  // 私有成员：内部状态不对外暴露
    unordered_map<int, int> cnt;  // 值 → 出现次数
    deque<int> q;  // 按插入顺序保存出现过的值，便于找「第一个」
};  // 类定义结束

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */