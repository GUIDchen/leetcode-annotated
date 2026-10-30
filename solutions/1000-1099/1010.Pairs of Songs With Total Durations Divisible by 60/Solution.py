# 题目：1010. 总持续时间可被 60 整除的歌曲（Pairs of Songs With Total Durations Divisible by 60）
# 核心思路：按模 60 的余数计数，用互补余数累加数对数量
# 复杂度：时间 O(n)；空间 O(1)，仅 60 个计数桶
class Solution:  # LeetCode 约定的题解类
    def numPairsDivisibleBy60(self, time: List[int]) -> int:  # time：每首歌的时长
        cnt = Counter()  # 计数桶：cnt[r] 表示已遍历过的歌里时长模 60 等于 r 的个数
        ans = 0  # 满足条件的歌曲对数量
        for x in time:  # 顺序遍历每首歌，只统计「当前歌 + 之前的歌」构成的数对
            x %= 60  # 两数之和能否被 60 整除只取决于它们模 60 的余数
            y = (60 - x) % 60  # 能与 x 配对的余数：补成 60，余数为 0 时仍取 0 避免越界
            ans += cnt[y]  # 之前有 cnt[y] 首歌能与之配对，答案就增加这么多
            cnt[x] += 1  # 把当前歌的余数计入桶中，供后面的歌配对
        return ans  # 返回满足条件的歌曲对总数
