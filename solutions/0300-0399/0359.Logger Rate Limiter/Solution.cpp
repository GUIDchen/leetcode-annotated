// 题目：359. 日志速率限制器（Logger Rate Limiter）
// 思路：哈希表记录每条消息「下一次允许打印的时间戳」，来消息时比较当前时间戳即可判定是否放行。
// 时间复杂度：O(1) 均摊，哈希表查询；空间复杂度：O(m)，m 为不同消息条数。
class Logger {  // 日志速率限制器类
public:  // 对外接口
    Logger() {  // 构造函数：无成员需要初始化
    }  // 构造函数结束

    bool shouldPrintMessage(int timestamp, string message) {  // timestamp：当前时间戳；message：日志内容
        if (ts.contains(message) && ts[message] > timestamp) {  // 已记录且解禁时间还没到，说明 10 秒内重复
            return false;  // 不允许打印
        }  // 重复判断结束
        ts[message] = timestamp + 10;  // 记录该消息下次可打印的时间戳（当前 + 10 秒）
        return true;  // 允许打印
    }  // 方法结束

private:  // 私有成员
    unordered_map<string, int> ts;  // 消息 → 下次允许打印的时间戳
};

// 下面是 LeetCode 判题器自动生成的调用示例（代码本体已在上面结束）
/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */  // 调用示例结束
