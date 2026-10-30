// 题目：1396. 设计地铁系统（Design Underground System）
// 思路：两张哈希表；ts 按乘客 id 记录「进站站点 + 进站时间」，d 按起点站 + 连字符 + 终点站的键累计总耗时与行程次数，出站时累加、查询时相除。
// 时间复杂度：各操作平均 O(1)；空间复杂度：O(n)，两张哈希表随操作次数增长。
class UndergroundSystem {  // 题目要求设计的地铁系统类
public:  // 对外提供的接口
    UndergroundSystem() {  // 构造函数：本题不需要额外初始化，成员哈希表会自动构造
    }  // 构造函数体为空

    void checkIn(int id, string stationName, int t) {  // id 号乘客在 t 时刻从 stationName 进站
        ts[id] = {stationName, t};  // 记录该乘客的进站站点与进站时间，供出站时计算耗时
    }  // checkIn 结束

    void checkOut(int id, string stationName, int t) {  // id 号乘客在 t 时刻从 stationName 出站
        auto [station, t0] = ts[id];  // 结构化解绑，取出进站站点 station 与进站时间 t0
        auto key = station + "-" + stationName;  // 用「起点站-终点站」拼成唯一键
        auto [tot, cnt] = d[key];  // 取出该线路已累计的 (总耗时, 行程次数)；键不存在时值初始化为 (0, 0)
        d[key] = {tot + t - t0, cnt + 1};  // 把本次耗时 t - t0 累加，并把行程次数加一后写回
    }  // checkOut 结束

    double getAverageTime(string startStation, string endStation) {  // 查询从 startStation 到 endStation 的平均耗时
        auto [tot, cnt] = d[startStation + "-" + endStation];  // 取出该线路的总耗时与行程次数
        return (double) tot / cnt;  // 转成 double 后相除，得到平均时间并返回
    }  // getAverageTime 结束

private:  // 以下为内部状态，不对外暴露
    unordered_map<int, pair<string, int>> ts;  // 乘客 id → (进站站点, 进站时间)
    unordered_map<string, pair<int, int>> d;  // 「起点站-终点站」→ (总耗时, 行程次数)
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */