# 题目：4091. 统计神奇子字符串对 II（Count Magical Substring Pairs II）
# 思路：calc(s)[r][k] 表示以 r 结尾、不同字符数不超过 k 的后缀个数，用「不同字符数不超过 k」的滑动窗口配合 distinct 计数在 O(26n) 内求出；对 s 与反转后的 s 各算一次，left[j][k] - left[j][k-1] 就是「以 j 结尾且恰含 k 种字符」的左半子串数，右侧同理，按 k 相乘累加。
# 时间复杂度：O(26n)，26 次双指针滑窗再加上一次 26n 的合并；空间复杂度：O(26n)，即 f 数组的大小。
class Solution:  # LeetCode 约定的题解类
    def calc(self, s: str) -> list[list[int]]:  # 辅助方法：返回 f[r][k] = 以 r 结尾、不同字符数不超过 k 的后缀个数
        n = len(s)  # n 是字符串长度
        f = [[0] * 27 for _ in range(n)]  # f[r][k] 存上述计数，第二维留 27 个位置以便用 k 直接下标
        for k in range(1, 27):  # 对每种允许的不同字符数上限 k 各做一次滑窗
            cnt = [0] * 26  # cnt[c]：窗口内字符 c 的出现次数
            l = distinct = 0  # l 是窗口左边界，distinct 是窗口内的不同字符数
            for r, c in enumerate(s):  # 右端点 r 从左到右扫描，c 是 s[r]
                c = ord(c) - ord("a")  # 把字符映射成 0..25 的下标
                if cnt[c] == 0:  # 新字符第一次进入窗口
                    distinct += 1  # 不同字符数加一
                cnt[c] += 1  # 该字符的窗口计数加一
                while distinct > k:  # 不同字符数超过上限，收缩左边界
                    c = ord(s[l]) - ord("a")  # 取出左边界字符并映射成下标
                    cnt[c] -= 1  # 左边界字符计数减一
                    if cnt[c] == 0:  # 该字符已彻底离开窗口
                        distinct -= 1  # 不同字符数减一
                    l += 1  # 左边界右移一位
                f[r][k] = r - l + 1  # 以 r 结尾、满足上限的合法后缀共有 r-l+1 个
        return f  # 返回二维计数表

    def countMagicalPairs(self, s: str) -> int:  # s：待统计的字符串；返回神奇子字符串对的总数
        n = len(s)  # n 是字符串长度
        left = self.calc(s)  # 原串上的计数表：left[j][k] 描述以 j 结尾、向左延伸的后缀
        right = self.calc(s[::-1])  # 反转串上的计数表，下标 r 对应原串从右往左的位置
        ans = 0  # ans 累计答案，Python 大整数不担心溢出
        for j in range(n - 1):  # 枚举分界点 j：左半以 j 结尾，右半从 j+1 开始
            r = n - 2 - j  # 反转串中的下标：原串的 j+1 对应反转串的 n-2-j 结尾处
            for k in range(1, 27):  # 枚举两半共同的不同字符数 k
                ans += (left[j][k] - left[j][k - 1]) * (right[r][k] - right[r][k - 1])  # 左半恰含 k 种字符的个数乘以右半恰含 k 种字符的个数
        return ans  # 返回神奇子字符串对的总数
