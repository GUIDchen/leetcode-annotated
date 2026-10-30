// 题目：1348. 推文计数（Tweet Counts Per Frequency）
// 思路：用哈希表「推文名 → 有序多重集合」保存时间戳；查询时把 [startTime, endTime] 按频率切成若干桶，用 lower_bound/upper_bound 框出区间，再逐个时间戳累加到它所属的桶。
// 时间复杂度：recordTweet 为 O(log n)，getTweetCountsPerFrequency 为 O(log n + k)，k 是区间内时间戳个数；空间复杂度：O(N)，N 为已记录的时间戳总数。
class TweetCounts {  // LeetCode 要求实现的推文计数器类
public:  // 对外提供的接口部分
    TweetCounts() {  // 构造函数：没有额外资源需要初始化，成员容器会自行默认构造
    }  // 空函数体

    void recordTweet(string tweetName, int time) {  // 记录一条推文：tweetName 是推文名，time 是发布时刻（秒）
        data[tweetName].insert(time);  // 把时间戳插入该推文名对应的有序集合；multiset 允许同一时刻重复记录
    }  // 方法结束

    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {  // 按频率统计区间内的推文数：[startTime, endTime] 闭区间，freq 取 minute/hour/day
        int f = 60;  // 默认按分钟统计，一分钟 60 秒
        if (freq == "hour")  // 频率为小时时，准备把步长改成 3600 秒
            f = 3600;  // if 的单语句体：更新步长
        else if (freq == "day")  // 否则再判断是否按天统计
            f = 86400;  // 按天时步长是 86400 秒
        vector<int> ans((endTime - startTime) / f + 1);  // 桶的个数：闭区间按步长切分，(endTime - startTime) / f 向下取整后再加 1
        auto l = data[tweetName].lower_bound(startTime);  // l 指向第一个 >= startTime 的时间戳
        auto r = data[tweetName].upper_bound(endTime);  // r 指向第一个 > endTime 的时间戳，所以 [l, r) 正好是区间内的全部时间戳
        for (; l != r; ++l) {  // 遍历区间内的每一个时间戳
            ++ans[(*l - startTime) / f];  // 该时间戳落在第 (t - startTime) / f 个桶，对应桶的计数加一
        }  // 遍历结束
        return ans;  // 返回每个桶的推文数量
    }  // 方法结束

private:  // 私有成员部分
    unordered_map<string, multiset<int>> data;  // 核心数据结构：推文名 → 有序时间戳集合，查询时才能二分定位区间
};  // 类定义结束（源文件末尾无换行，逐字节保持不变）

// 下面是判题器给出的实例化与调用示例，属于题面说明，原样保留这段注释块
/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 = obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */