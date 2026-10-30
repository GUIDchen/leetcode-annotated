// 题目：981. 基于时间的键值存储（Time Based Key-Value Store）
// 思路：每个 key 维护一个按时间戳递增的 (时间戳, 值) 向量，set 直接追加；get 用 upper_bound 越过「同一时间戳且值最大」的哨兵，取前一条记录的值。
// 时间复杂度：set 为 O(1) 均摊，get 为 O(log n)；空间复杂度：O(n)，需要保存全部键值对。
class TimeMap {  // 设计题要求的 TimeMap 类
public:  // 对外提供的接口
    TimeMap() {  // 构造函数
    }  // 成员由默认初始化完成，这里留空

    void set(string key, string value, int timestamp) {  // 存入 key 在 timestamp 时刻的 value
        ktv[key].emplace_back(timestamp, value);  // 追加到该 key 的记录尾部，题目保证同一 key 的时间戳严格递增
    }  // set 结束

    string get(string key, int timestamp) {  // 查询 key 在 timestamp 及之前最近一次写入的值
        auto& pairs = ktv[key];  // 取出该 key 的记录序列（不存在时会创建空向量）
        pair<int, string> p = {timestamp, string({127})};  // 构造二分哨兵：时间戳相同、字符串取最大字符，保证能越过同一时间戳的全部记录
        auto i = upper_bound(pairs.begin(), pairs.end(), p);  // upper_bound 找第一个严格大于哨兵的位置
        return i == pairs.begin() ? "" : (i - 1)->second;  // 迭代器在开头说明没有更早记录，返回空串；否则取前一条记录的值
    }  // get 结束

private:  // 内部数据成员
    unordered_map<string, vector<pair<int, string>>> ktv;  // 哈希表：键 → 按时间戳递增的 (时间戳, 值) 向量
};  // 类定义结束

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */