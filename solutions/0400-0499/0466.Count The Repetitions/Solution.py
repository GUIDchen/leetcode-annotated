# 题目：466. 统计重复个数（Count The Repetitions）
# 思路：预处理 s2 的每个起点在「一个 s1」中能完整匹配多少个 s2、结束时落在 s2 的哪个下标；然后按 n1 份 s1 递推累加，最后除以 n2。
# 时间复杂度：O(n·m + n1)，n = |s2|、m = |s1|；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:  # 求 s1 重复 n1 次中最多包含多少个 s2 重复 n2 次
        n = len(s2)  # s2 的长度
        d = {}  # d[i]：从 s2[i] 开始扫一个 s1，能匹配的 s2 个数与结束下标
        for i in range(n):  # 预处理 s2 的每个起点
            cnt = 0  # 这一个 s1 内能匹配完成的 s2 个数
            j = i  # 当前要匹配的 s2 下标
            for c in s1:  # 顺序扫描一个 s1
                if c == s2[j]:  # 字符相同才推进匹配位置
                    j += 1  # s2 下标后移
                if j == n:  # 匹配完一整个 s2
                    cnt += 1  # 完成一个 s2
                    j = 0  # 下一个字符从 s2 头部重新开始
            d[i] = (cnt, j)  # 记录该起点对应的转移结果

        ans = 0  # 累计 n1 份 s1 中匹配到的 s2 总数
        j = 0  # 当前匹配起点
        for _ in range(n1):  # 依次消耗 n1 份 s1
            cnt, j = d[j]  # 取出这一份 s1 的结果并更新起点
            ans += cnt  # 累加完成的 s2 个数
        return ans // n2  # 能拼出多少份 n2 个 s2 即为答案
