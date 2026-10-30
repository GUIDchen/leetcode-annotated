# 题目：1348. 推文计数（Tweet Counts Per Frequency）
# 思路：用「推文名 → 有序列表 SortedList」保存时间戳；查询时按频率把 [startTime, endTime] 切成连续的时间桶，再用 bisect_left 二分求出每个桶内的时间戳个数。
# 时间复杂度：recordTweet 为 O(log n)，getTweetCountsPerFrequency 为 O((区间长度/步长) * log n)；空间复杂度：O(N)，N 为所有已记录的时间戳总数。
class TweetCounts:  # LeetCode 要求实现的推文计数器类
    def __init__(self):  # 构造函数：准备频率到秒数的映射，以及按推文名分组的有序容器
        self.d = {"minute": 60, "hour": 3600, "day": 86400}  # freq 字符串到步长秒数的映射表
        self.data = defaultdict(SortedList)  # 每个推文名对应一个 SortedList，支持有序插入与二分查找

    def recordTweet(self, tweetName: str, time: int) -> None:  # 记录一条推文：tweetName 是推文名，time 是发布时刻（秒）
        self.data[tweetName].add(time)  # 把时间戳按有序方式插入该推文名的列表

    def getTweetCountsPerFrequency(  # 按频率统计区间内的推文数；参数较多所以签名拆成三行书写
        self, freq: str, tweetName: str, startTime: int, endTime: int  # 参数：freq 频率名，tweetName 推文名，startTime/endTime 为闭区间两端
    ) -> List[int]:  # 返回每个时间桶内的推文条数列表
        f = self.d[freq]  # 取出该频率对应的步长（秒）
        tweets = self.data[tweetName]  # 取出该推文名的时间戳有序列表
        t = startTime  # t 是当前时间桶的左端点，从 startTime 开始
        ans = []  # ans 依次收集每个桶的计数
        while t <= endTime:  # 桶左端点不越过 endTime 就继续切分
            l = tweets.bisect_left(t)  # l：本桶内第一个 >= t 的时间戳下标
            r = tweets.bisect_left(min(t + f, endTime + 1))  # r：第一个 >= t+f 的位置；用 min(..., endTime+1) 保证最后一个桶的右端不越过区间
            ans.append(r - l)  # 下标个数 r-l 就是本桶内的推文条数
            t += f  # 进入下一个时间桶
        return ans  # 返回所有桶的计数


# 下面几行是判题器给出的实例化与调用示例，已被 # 注释掉，原样保留
# Your TweetCounts object will be instantiated and called as such:
# obj = TweetCounts()
# obj.recordTweet(tweetName,time)
# param_2 = obj.getTweetCountsPerFrequency(freq,tweetName,startTime,endTime)
