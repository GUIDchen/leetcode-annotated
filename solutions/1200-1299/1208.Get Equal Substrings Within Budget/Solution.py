# 题目：1208. 尽可能使字符串相等（Get Equal Substrings Within Budget）
# 思路：先用 accumulate 对「逐位改字符的代价」求前缀和，再二分答案长度，用前缀和 O(1) 判定任一窗口是否可行。
# 时间复杂度：O(n log n)，前缀和 O(n)，二分 O(log n) 轮、每轮 O(n) 判定；空间复杂度：O(n)，需要长度为 n+1 的前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def equalSubstring(self, s: str, t: str, maxCost: int) -> int:  # s、t：两个等长字符串；maxCost：允许的总修改代价；返回最长可转化的子串长度
        def check(x):  # 判定函数：长度 x 的子串是否可行（实际用的是外层变量 mid，x 仅作占位形参）
            for i in range(n):  # 枚举窗口左端点；右越界的情况交给下一行的 j < n 兜住
                j = i + mid - 1  # 由左端点算出窗口右端点，这里的 mid 来自外层二分循环
                if j < n and f[j + 1] - f[i] <= maxCost:  # 窗口未越界且窗口内代价和不超过预算，说明该长度可行
                    return True  # 找到一个可行窗口，立即返回真
            return False  # 所有窗口都超预算，长度不可行

        n = len(s)  # 字符串长度，后续前缀和与二分上界都用到它
        f = list(accumulate((abs(ord(a) - ord(b)) for a, b in zip(s, t)), initial=0))  # 代价前缀和：f[i] 表示把前 i 个字符改成一样所需的总代价
        l, r = 0, n  # 二分答案区间：最长长度至少 0，至多 n
        while l < r:  # 二分「最大的可行长度」
            mid = (l + r + 1) >> 1  # 取上中位数，配合下面的 l = mid 避免死循环
            if check(mid):  # 长度 mid 可行；由单调性，比它短的长度一定也可行
                l = mid  # 保留 mid 作为当前最优，继续向更长的一侧尝试
            else:  # 长度 mid 不可行，答案只能更短
                r = mid - 1  # 收缩上界到下中位数
        return l  # 收敛点就是最大可行长度
