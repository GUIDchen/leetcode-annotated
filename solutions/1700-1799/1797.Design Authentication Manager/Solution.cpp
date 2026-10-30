// 题目：1797. 设计一个验证系统（Design Authentication Manager）
// 思路：用「tokenId → 过期时间」的哈希表保存状态；generate 直接写入 currentTime + timeToLive，renew 只在未过期时刷新，countUnexpiredTokens 遍历统计过期时间大于当前时间的个数。
// 时间复杂度：generate/renew 均摊 O(1)，countUnexpiredTokens 为 O(n)；空间复杂度：O(n)，n 为存活过的 token 数。
class AuthenticationManager {  // 设计题：验证码管理器
public:  // 对外接口
    AuthenticationManager(int timeToLive) {  // 构造函数，timeToLive 是每个 token 的有效期
        t = timeToLive;  // 保存有效期，供 generate / renew 使用
    }  // 构造函数结束

    void generate(string tokenId, int currentTime) {  // 生成或覆盖一个 token 的过期时间
        d[tokenId] = currentTime + t;  // 过期时间 = 当前时间 + 有效期
    }  // 方法结束

    void renew(string tokenId, int currentTime) {  // 续期：只允许未过期的 token 续期
        if (d[tokenId] <= currentTime) return;  // 已过期（不存在的键经 operator[] 插入 0）就直接返回
        generate(tokenId, currentTime);  // 未过期，复用 generate 刷新过期时间
    }  // 方法结束

    int countUnexpiredTokens(int currentTime) {  // 统计当前仍在有效期内的 token 数
        int ans = 0;  // 计数器
        for (auto& [_, v] : d) ans += v > currentTime;  // 结构化绑定遍历哈希表；过期时间晚于当前时间即有效，布尔值直接累加
        return ans;  // 返回有效数量
    }  // 方法结束

private:  // 以下是私有成员
    int t;  // token 的存活时长
    unordered_map<string, int> d;  // tokenId → 过期时间
};  // 类定义结束

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */