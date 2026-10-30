# 题目：355. 设计推特（Design Twitter）
# 思路：用全局自增时间戳标记推文新旧；发推追加到该用户的推文列表，取动态时把本人与关注者各最近 10 条汇总，再用 nlargest 取最新 10 条。
# 时间复杂度：postTweet/follow/unfollow 为 O(1)，getNewsFeed 为 O(F × 10 log 10)，F 为关注人数；空间复杂度：O(U + T)，U 为用户数、T 为推文数。
class Twitter:  # 设计推特的数据结构类
    def __init__(self):  # 构造函数：初始化推文表、关注表与时间戳
        """
        Initialize your data structure here.
        """
        self.user_tweets = defaultdict(list)  # 用户 → 其发出的推文 id 列表，按发送顺序追加
        self.user_following = defaultdict(set)  # 用户 → 其关注的人集合，用 set 天然去重
        self.tweets = defaultdict()  # 推文 id → 发送时间戳，用于比较新旧
        self.time = 0  # 全局单调递增的时间戳，保证后发的推文更大

    def postTweet(self, userId: int, tweetId: int) -> None:  # 用户 userId 发一条推文 tweetId
        """
        Compose a new tweet.
        """
        self.time += 1  # 时间戳自增，保证后发的推文一定更大
        self.user_tweets[userId].append(tweetId)  # 追加到该用户推文列表的尾部
        self.tweets[tweetId] = self.time  # 记录这条推文的发送时间

    def getNewsFeed(self, userId: int) -> List[int]:  # 返回该用户及其关注者最近发布的 10 条推文 id，从新到旧
        """
        Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
        """
        following = self.user_following[userId]  # 取出该用户关注的人
        users = set(following)  # 复制一份集合，避免修改原有关注表
        users.add(userId)  # 自己发的推文也要出现在动态里
        tweets = [self.user_tweets[u][::-1][:10] for u in users]  # 每个相关用户只取最新的 10 条（先反转再切片）
        tweets = sum(tweets, [])  # 把多个列表拼成一个候选池
        return nlargest(10, tweets, key=lambda tweet: self.tweets[tweet])  # 按时间戳取最大的 10 个，nlargest 返回的天然由新到旧

    def follow(self, followerId: int, followeeId: int) -> None:  # followerId 关注 followeeId
        """
        Follower follows a followee. If the operation is invalid, it should be a no-op.
        """
        self.user_following[followerId].add(followeeId)  # 加入关注集合，重复关注自动去重

    def unfollow(self, followerId: int, followeeId: int) -> None:  # followerId 取消关注 followeeId
        """
        Follower unfollows a followee. If the operation is invalid, it should be a no-op.
        """
        following = self.user_following[followerId]  # 取出该用户的关注集合
        if followeeId in following:  # 只有确实关注过才删除，避免无意义的操作
            following.remove(followeeId)  # 移除关注关系


# 下面是 LeetCode 模板注释，仅演示对象的构造与调用方式
# Your Twitter object will be instantiated and called as such:
# obj = Twitter()
# obj.postTweet(userId,tweetId)
# param_2 = obj.getNewsFeed(userId)
# obj.follow(followerId,followeeId)
# obj.unfollow(followerId,followeeId)
