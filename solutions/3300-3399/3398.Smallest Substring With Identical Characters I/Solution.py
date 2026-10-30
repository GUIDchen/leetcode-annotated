# 3398. 字符相同的最短子字符串 I / Smallest Substring With Identical Characters I
# 核心思路：二分答案 m，判断能否用不超过 numOps 次修改使所有相同字符连续段长度不超过 m：m=1 时只能是 0101... 或 1010...；m>1 时长度为 k 的段需要 k//(m+1) 次修改
# 复杂度：时间 O(n log n)（二分 log n 次、每次 check O(n)）、空间 O(1)
class Solution:  # 定义 Solution 类
    def minLength(self, s: str, numOps: int) -> int:  # 求至多修改 numOps 个字符后，最长相同字符子串的最小可能长度
        def check(m: int) -> bool:  # 判断最大连续长度不超过 m 时所需最少修改次数是否不超过 numOps
            cnt = 0  # 记录需要的修改次数
            if m == 1:  # m 为 1 时，结果串只能是 0101... 或 1010... 两种交替形式
                t = "01"  # 交替串模板
                cnt = sum(c == t[i & 1] for i, c in enumerate(s))  # 统计与模板相同的字符数（即可以不动的字符数）
                cnt = min(cnt, n - cnt)  # 两种交替模板取修改次数较少者
            else:  # m 大于 1 时按连续相同字符段分组处理
                k = 0  # 当前连续相同字符段的长度
                for i, c in enumerate(s):  # 逐位遍历字符串
                    k += 1  # 当前段长度加一
                    if i == len(s) - 1 or c != s[i + 1]:  # 到达末尾或与下一字符不同，说明一段结束
                        cnt += k // (m + 1)  # 长度为 k 的段每 m+1 个字符需要改一次，共需 k//(m+1) 次修改
                        k = 0  # 段长度清零
            return cnt <= numOps  # 修改次数不超过 numOps 说明 m 可行

        n = len(s)  # 记下字符串长度 n
        return bisect_left(range(n), True, lo=1, key=check)  # 在 [1, n-1] 上二分查找最小的可行长度，key=check 把下标映射为是否可行
