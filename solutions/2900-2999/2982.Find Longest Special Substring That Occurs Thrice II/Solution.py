# 题目：2982. 找出出现至少三次的最长特殊子字符串 II（Find Longest Special Substring That Occurs Thrice II）
# 核心思路：二分答案长度 x；check(x) 用 defaultdict 累加每个字母能提供的「长度恰为 x 的特殊子串」个数，任一个达到 3 即可行。
# 时间复杂度：O(n log n)，每轮 check 扫描一遍串；空间复杂度：O(1)，字典最多 26 个键。
class Solution:  # LeetCode 约定的题解类
    def maximumLength(self, s: str) -> int:  # s 是输入串，返回最长「出现至少三次的特殊子串」长度，不存在则返回 -1
        def check(x: int) -> bool:  # 内层判定：长度 x 的特殊子串是否存在某个字母出现至少三次
            cnt = defaultdict(int)  # 字母计数器，缺省值为 0，省去按键初始化
            i = 0  # 从下标 0 开始枚举连续相同字符的段
            while i < n:  # n 由外层作用域提供，闭包在调用时才读取
                j = i + 1  # j 是右端点游标，先指向 i 的后一位
                while j < n and s[j] == s[i]:  # 字符仍与 s[i] 相同就继续向右扩
                    j += 1  # 右端点右移一格
                cnt[s[i]] += max(0, j - i - x + 1)  # 段长 L 中长度恰为 x 的子串有 L-x+1 个，不足 x 个字符时记 0
                i = j  # 跳过整段，继续处理后面的连续段
            return max(cnt.values()) >= 3  # 任一字母累计到 3 次，就说明长度 x 可行

        n = len(s)  # 串长，作为二分区间上界
        l, r = 0, n  # 二分区间 [l, r]，l = 0 代表「无解」
        while l < r:  # 二分找最大的可行长度，用上取整中点
            mid = (l + r + 1) >> 1  # 上取整的中点，保证区间每次都能收缩
            if check(mid):  # mid 这个长度可行
                l = mid  # 左边界抬到 mid
            else:  # mid 这个长度不可行
                r = mid - 1  # 右边界降到 mid - 1
        return -1 if l == 0 else l  # 收敛后 l 即答案，为 0 表示不存在合法子串，返回 -1
