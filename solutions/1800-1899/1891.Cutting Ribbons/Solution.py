# 题目：1891. 割绳子（Cutting Ribbons）
# 思路：可行性关于长度 L 单调不增，二分答案；mid 取上取整保证 left = mid 时区间收缩，sum(x // mid) 即当前长度能切出的总段数。
# 时间复杂度：O(n log maxRibbon)，每次判定扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxLength(self, ribbons: List[int], k: int) -> int:  # ribbons：各条丝带长度；k：需要的段数，返回能切出的最长等长段长度
        left, right = 0, max(ribbons)  # 二分区间 [0, max(ribbons)]，闭区间写法
        while left < right:  # left < right 时继续收缩
            mid = (left + right + 1) >> 1  # (left + right + 1) >> 1 是上取整中点，配合 left = mid 防止死循环
            cnt = sum(x // mid for x in ribbons)  # 生成器求和：每条丝带能切 x // mid 段
            if cnt >= k:  # 段数够用，mid 可行，答案不小于 mid
                left = mid  # 保留 mid，向右收缩
            else:  # 段数不够，mid 偏大
                right = mid - 1  # 答案严格小于 mid
        return left  # 循环结束时 left == right，即最长可切长度
