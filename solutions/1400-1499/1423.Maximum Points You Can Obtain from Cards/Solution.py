# 题目：1423. 可获得的最大点数（Maximum Points You Can Obtain from Cards）
# 核心思路：先取最右侧 k 张作为初始方案，再逐次用左端一张替换右端一张，滑动比较出最大点数。
# 时间复杂度：O(k)；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, cardPoints: List[int], k: int) -> int:  # cardPoints：牌面点数；k：必须取走的张数
        ans = s = sum(cardPoints[-k:])  # 初始方案：全从右端取，和记为 s，同时作为当前最优
        for i, x in enumerate(cardPoints[:k]):  # 逐张把取值从右端换到左端
            s += x - cardPoints[-k + i]  # 加上左端第 i 张，减去右端被替换掉的那张
            ans = max(ans, s)  # 更新最大点数
        return ans  # 返回最大点数
