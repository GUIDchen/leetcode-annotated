# 3399. 字符相同的最短子字符串 II / Smallest Substring With Identical Characters II
# 核心思路：二分答案 m，判定能否用不超过 numOps 次操作把所有同字符段压到长度 ≤ m（m == 1 时与 01 交替串比较，取两种模板中较小的改动数）
# 复杂度：时间 O(n log n)，空间 O(1)
class Solution:  # 定义题目解答类
    def minLength(self, s: str, numOps: int) -> int:  # 方法入口：s 为 01 串，numOps 为最多可修改的字符数
        def check(m: int) -> bool:  # 判定函数：所有同字符段长度都不超过 m 时是否可行
            cnt = 0  # 累计需要修改的字符数
            if m == 1:  # 上限为 1 时目标串只能是 01 交替串
                t = "01"  # 交替模板，按下标奇偶取 "0" 或 "1"
                cnt = sum(c == t[i & 1] for i, c in enumerate(s))  # 计算与模板相同的位置个数，即改成 "01…" 的代价
                cnt = min(cnt, n - cnt)  # 改成 "10…" 的代价是 n - cnt，两者取较小者
            else:  # 上限大于 1 时按连续相同段分别计算
                k = 0  # 当前连续相同段的长度
                for i, c in enumerate(s):  # 遍历整个字符串
                    k += 1  # 当前段长度加一
                    if i == len(s) - 1 or c != s[i + 1]:  # 到达末尾或与下一个字符不同，说明一段结束
                        cnt += k // (m + 1)  # 长度为 k 的段每 m + 1 个字符需改 1 个，共需 k // (m + 1) 次
                        k = 0  # 清零，开始统计下一段
            return cnt <= numOps  # 所需操作次数不超过 numOps 即可行

        n = len(s)  # 记录串长，供判定函数闭包使用
        return bisect_left(range(n), True, lo=1, key=check)  # 在 [1, n) 内二分第一个使 check 为真的长度，即最小可行上限
