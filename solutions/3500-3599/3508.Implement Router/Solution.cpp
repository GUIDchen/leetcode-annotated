// 题目：3508. 设计路由器（Implement Router）
// 思路：哈希集合判重 + 双端队列按入队顺序存包 + 每个目的地各维护一张按时间升序的时间戳表。入队前若已达到内存上限就先弹出队首；getCount 用 lower_bound 在「尚未被弹出」的那段后缀上二分，靠每个目的地的已弹出计数定位起点。
// 时间复杂度：addPacket 与 forwardPacket 均摊 O(1)，getCount 为两次二分 O(log m)；空间复杂度：O(memoryLimit)，队列与去重集合都受内存上限约束。
class Router {  // 路由器类，支持加包、按序弹包与区间计数
private:  // 私有数据结构区域
    int lim;  // 内存上限，队列中最多保留的包数
    unordered_set<string> vis;  // 已入队包的键集合，用于 O(1) 判重
    deque<array<int, 3>> q;  // 按入队顺序存包的队列，元素为 {源, 目的, 时间戳}
    unordered_map<int, int> idx;  // 每个目的地已被弹出的包数，即其在 d 中的有效起点
    unordered_map<int, vector<int>> d;  // 每个目的地的时间戳列表，按入队顺序天然升序

    string f(int a, int b, int c) {  // 把三元组拼成字符串键，供哈希集合判重
        return to_string(a) + "#" + to_string(b) + "#" + to_string(c);  // 用 # 分隔拼接，保证不同三元组的键互不冲突
    }  // 辅助方法结束

public:  // 对外接口区域
    Router(int memoryLimit) {  // 构造函数，读入内存上限
        lim = memoryLimit;  // 记录内存上限
    }  // 构造函数结束

    bool addPacket(int source, int destination, int timestamp) {  // 加入一个包，重复包返回 false
        string x = f(source, destination, timestamp);  // 生成该包的唯一键
        if (vis.count(x)) {  // 该包此前已经入过队
            return false;  // 重复包直接拒绝
        }  // 判重结束
        vis.insert(x);  // 标记该包已存在
        if ((int) q.size() >= lim) {  // 队列已满，需要腾出位置
            forwardPacket();  // 弹出最旧的包（返回值此处丢弃）
        }  // 腾位置结束
        q.push_back({source, destination, timestamp});  // 新包追加到队尾
        d[destination].push_back(timestamp);  // 同步写入目的地的升序时间戳表
        return true;  // 添加成功
    }  // 方法结束

    vector<int> forwardPacket() {  // 弹出并返回队首最旧的包
        if (q.empty()) {  // 队列为空
            return {};  // 没有可弹出的包，返回空数组
        }  // 空判定结束
        auto packet = q.front();  // 取出队首包
        q.pop_front();  // 从队列中移除队首
        int s = packet[0], d_ = packet[1], t = packet[2];  // 拆出源、目的、时间戳三个字段
        vis.erase(f(s, d_, t));  // 从判重集合中删掉该包的键
        idx[d_]++;  // 该目的地的已弹出计数加一，后续统计从这里开始
        return {s, d_, t};  // 返回被弹出的包
    }  // 方法结束

    int getCount(int destination, int startTime, int endTime) {  // 统计某目的地在 [startTime, endTime] 闭区间内的包数
        auto& ls = d[destination];  // 取该目的地的升序时间戳列表
        int k = idx[destination];  // 已弹出的前缀长度，二分只需在其后的后缀中进行
        auto i = lower_bound(ls.begin() + k, ls.end(), startTime);  // 第一个时间戳 >= startTime 的位置
        auto j = lower_bound(ls.begin() + k, ls.end(), endTime + 1);  // 第一个时间戳 > endTime 的位置
        return j - i;  // 两者下标之差即区间内的包数
    }  // 方法结束
};  // 类定义结束

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */
