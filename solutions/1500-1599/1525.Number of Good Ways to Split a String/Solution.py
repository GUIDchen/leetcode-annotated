# 题目：1525. 字符串的好分割数目（Number of Good Ways to Split a String）
# 核心思路：用 Counter 统计整串频次（视为右半），从左到右把字符搬进左半集合，左右不同字符数相等时计数。
# 时间复杂度：O(n)；空间复杂度：O(σ)，σ 为字符种数（≤26）。
class Solution:  # LeetCode 约定的题解类
    def numSplits(self, s: str) -> int:  # s：待分割字符串
        cnt = Counter(s)  # Counter(s)：整串字符频次，先全部算作右半
        vis = set()  # vis：左半出现过的字符集合
        ans = 0  # 答案计数
        for c in s:  # 从左到右枚举分割点
            vis.add(c)  # 当前字符进入左半
            cnt[c] -= 1  # 从右半计数减一
            if cnt[c] == 0:  # 右半已经没有该字符
                cnt.pop(c)  # 删除该键，len(cnt) 才等于右半不同字符数
            ans += len(vis) == len(cnt)  # 左右不同字符数相等则计数加一（布尔值可直接相加）
        return ans  # 返回好分割的数目
