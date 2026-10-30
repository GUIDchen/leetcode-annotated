// 题目：635. 设计日志存储系统（Design Log Storage System）
// 思路：日志按插入顺序存进数组；查询时按粒度把时间戳截成等长前缀（年 4 位、月 7 位……），前缀落在 [start, end] 内即命中。
// 时间复杂度：put 为 O(1)，retrieve 为 O(m)（m 为日志条数）；空间复杂度：O(m)。
class LogSystem {  // 设计题：日志存储系统
public:  // 对外接口
    LogSystem() {  // 构造函数：建立「粒度名 → 时间戳前缀长度」的映射表
        d["Year"] = 4;  // 年粒度：截取前 4 位，如 2017
        d["Month"] = 7;  // 月粒度：截取前 7 位，如 2017:01
        d["Day"] = 10;  // 日粒度：截取前 10 位，如 2017:01:01
        d["Hour"] = 13;  // 时粒度：截取前 13 位，如 2017:01:01:23
        d["Minute"] = 16;  // 分粒度：截取前 16 位，如 2017:01:01:23:59
        d["Second"] = 19;  // 秒粒度：截取前 19 位，即完整时间戳
    }  // 构造函数结束

    void put(int id, string timestamp) {  // 插入一条日志
        logs.push_back({id, timestamp});  // 按到达顺序追加 (id, timestamp)，数组天然保持插入顺序
    }  // put 结束

    vector<int> retrieve(string start, string end, string granularity) {  // 查询 [start, end] 区间内、指定粒度下的日志 id
        vector<int> ans;  // ans 收集命中的日志 id，保持插入顺序
        int i = d[granularity];  // 查表得到该粒度需要比较的时间戳前缀长度
        auto s = start.substr(0, i);  // 起点按粒度截断成前缀
        auto e = end.substr(0, i);  // 终点按粒度截断成前缀
        for (auto& [id, ts] : logs) {  // 遍历所有日志，结构化绑定解包出 id 与时间戳
            auto t = ts.substr(0, i);  // 日志时间戳也只取同长度前缀，保证等长字符串比较等价于时间比较
            if (s <= t && t <= e) {  // 前缀落在 [start, end] 闭区间内即命中
                ans.emplace_back(id);  // 记录该日志的 id
            }  // 命中分支结束
        }  // 遍历结束
        return ans;  // 返回所有命中的 id
    }  // retrieve 结束

private:  // 私有成员
    vector<pair<int, string>> logs;  // 所有日志按插入顺序保存为 (id, timestamp)
    unordered_map<string, int> d;  // 粒度名到前缀长度的映射表
};  // 类定义结束

// 下面是判题器给出的调用示例，原样保留作说明
/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem* obj = new LogSystem();
 * obj->put(id,timestamp);
 * vector<int> param_2 = obj->retrieve(start,end,granularity);
 */