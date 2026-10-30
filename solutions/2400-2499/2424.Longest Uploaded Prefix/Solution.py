# 题目：2424. 最长上传前缀（Longest Uploaded Prefix）
# 思路：用集合记录已上传编号，并维护已连续覆盖的位置 r；每次上传后从 r+1 起向后延伸，r 即最长前缀长度。
# 时间复杂度：均摊 O(1)，每个编号最多被 while 推进一次；空间复杂度：O(n)，集合需保存全部已上传编号。
class LUPrefix:  # 设计题类：维护已上传视频的最长前缀长度
    def __init__(self, n: int):  # 构造函数，n 是视频总数
        self.r = 0  # 当前最长已上传前缀长度，初始为 0
        self.s = set()  # 用集合保存所有已上传的视频编号，便于 O(1) 查找

    def upload(self, video: int) -> None:  # 上传编号为 video 的视频
        self.s.add(video)  # 把编号加入集合，标记为已上传
        while self.r + 1 in self.s:  # 只要前缀的下一个编号也已经上传
            self.r += 1  # 最长前缀长度就可以继续加一

    def longest(self) -> int:  # 查询当前最长已上传前缀的长度
        return self.r  # r 始终是满足 1..r 全部已上传的最大值


# Your LUPrefix object will be instantiated and called as such:
# obj = LUPrefix(n)
# obj.upload(video)
# param_2 = obj.longest()
