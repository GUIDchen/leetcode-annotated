# 题目：1234. 替换子串得到平衡字符串（Replace the Substring for Balanced String）
# 思路：统计整串字符出现次数，用滑动窗口表示「待替换的子串」，窗口外每种字符都 ≤ n//4 时收缩左边界求最短窗口。
# 时间复杂度：O(n)，双指针各前进一次；空间复杂度：O(1)，计数器最多四个键。
class Solution:  # LeetCode 约定的题解类
    def balancedString(self, s: str) -> int:  # s 只含 Q/W/E/R，返回使它平衡的最短替换子串长度
        cnt = Counter(s)  # 统计每种字符在整串中的出现次数
        n = len(s)  # 字符串长度
        if all(v <= n // 4 for v in cnt.values()):  # 每种字符都不超过 n // 4，说明原串已经平衡
            return 0  # 无需替换
        ans, j = n, 0  # ans 先取上界 n；j 是滑动窗口左端点
        for i, c in enumerate(s):  # i 是窗口右端点，c 是当前字符
            cnt[c] -= 1  # 把 c 划出窗口（进入待替换区间），窗口外计数减一
            while j <= i and all(v <= n // 4 for v in cnt.values()):  # 窗口外四种字符都不超量时，尝试继续缩小窗口
                ans = min(ans, i - j + 1)  # 记录更短的窗口长度
                cnt[s[j]] += 1  # 左端点字符移出窗口，计数加回
                j += 1  # 左端点右移
        return ans  # 返回最短替换长度
