// 题目：2034. 股票价格波动（Stock Price Fluctuation）
// 思路：哈希表记录「时间戳 → 当前价格」，multiset 维护全部当前价格以支持 O(log n) 的极值查询；更新时若该时间戳已有价格，先从 multiset 删掉旧值，再插入新值，同时用 last 记录最新时间戳。
// 时间复杂度：update 为 O(log n)，current/maximum/minimum 分别为 O(1)/O(1)/O(1)（取 begin 与 rbegin）；空间复杂度：O(n)，每个时间戳存一份价格。
class StockPrice {  // 维护「时间戳 → 价格」并支持查询最新/最高/最低价的数据结构类
public:  // 对外接口
    StockPrice() {  // 构造函数：成员已用默认值初始化，无需额外动作
    }  // 空函数体

    void update(int timestamp, int price) {  // timestamp 时刻的价格变成 price；同一时间戳的旧价格要作废
        if (d.count(timestamp)) {  // 该时间戳之前出现过，需要先把旧价格从有序集合里删掉
            ls.erase(ls.find(d[timestamp]));  // 只删一个旧值（multiset 可能有重复价格，用 find 定位单个元素）
        }  // 结束旧值清理
        d[timestamp] = price;  // 用新价格覆盖哈希表中的记录
        ls.insert(price);  // 新价格加入有序集合，参与后续极值查询
        last = max(last, timestamp);  // 最新时间戳只增不减（时间戳不保证按顺序到来）
    }  // 结束 update

    int current() {  // 返回最新时间戳对应的价格
        return d[last];  // last 始终是出现过的最大时间戳
    }  // 结束 current

    int maximum() {  // 返回当前最高价格
        return *ls.rbegin();  // multiset 升序，反向迭代器首元素即最大值
    }  // 结束 maximum

    int minimum() {  // 返回当前最低价格
        return *ls.begin();  // multiset 升序，begin 即最小值
    }  // 结束 minimum

private:  // 私有成员
    unordered_map<int, int> d;  // 时间戳 → 当前价格
    multiset<int> ls;  // 所有有效价格的升序可重复集合
    int last = 0;  // 出现过的最大时间戳，初始为 0
};  // 结束 StockPrice 类

// 下面是 LeetCode 判题器自动生成的调用示例注释，原样保留。
/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */