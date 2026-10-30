# 题目：1297. 子串的最大出现次数（Maximum Number of Occurrences of a Substring）
# 思路：只需枚举长度 minSize 的窗口——更长的合格子串，其长度 minSize 的前缀出现次数不会更少。
# 时间复杂度：O(n * minSize)，每个窗口切子串并建集合；空间复杂度：O(n * minSize)，字典存放子串。
class Solution:  # LeetCode 约定的题解类
    def maxFreq(self, s: str, maxLetters: int, minSize: int, maxSize: int) -> int:  # s：原串；maxLetters：不同字母上限；minSize/maxSize：长度下限/上限（maxSize 用不到）
        ans = 0  # 记录出现次数的最大值
        cnt = Counter()  # 统计满足条件的子串出现次数
        for i in range(len(s) - minSize + 1):  # 枚举所有长度 minSize 的窗口起点
            t = s[i : i + minSize]  # 取出当前长度为 minSize 的子串
            ss = set(t)  # 用集合统计该子串有多少种不同字母
            if len(ss) <= maxLetters:  # 不同字母数不超过上限才有资格计入答案
                cnt[t] += 1  # 该子串计数加一
                ans = max(ans, cnt[t])  # 更新最大值
        return ans  # 返回最大出现次数
