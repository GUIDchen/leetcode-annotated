// 题目：895. 最大频率栈（Maximum Frequency Stack）
// 核心思路：哈希表记每个值的出现次数，大顶堆按 (频率, 时间戳) 排序，时间戳保证同频率时后进先出。
// 时间复杂度：push/pop 均 O(log n)；空间复杂度：O(n)，每次 push 入堆一个三元组。
class FreqStack {  // 最大频率栈：pop 返回出现次数最多的元素，次数相同时取最晚入栈的
public:  // 对外接口
    FreqStack() {  // 构造函数：成员都有默认初始化，无需额外操作
    }  // 空实现

    void push(int val) {  // 入栈：更新出现次数并压入优先队列
        ++cnt[val];  // 该值出现次数加一
        q.emplace(cnt[val], ++ts, val);  // 时间戳自增保证「后进先出」；元组默认按 (频率, 时间戳) 降序比较
    }

    int pop() {  // 出栈：取出当前频率最高、且最晚入栈的元素
        auto [a, b, val] = q.top();  // 结构化绑定拆出频率、时间戳和值，前两者只用于排序
        q.pop();  // 从堆中删除堆顶
        --cnt[val];  // 该值弹出一个，出现次数减一
        return val;  // 返回被弹出的值
    }

private:  // 内部数据结构
    unordered_map<int, int> cnt;  // 记录每个值当前的出现次数
    priority_queue<tuple<int, int, int>> q;  // 大顶堆：先比频率，频率相同再比时间戳
    int ts = 0;  // 全局时间戳，模拟入栈的先后顺序
};  // 类定义结束

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */