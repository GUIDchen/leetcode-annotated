# 题目：2573. 找出对应 LCP 矩阵的字符串（Find the String with LCP）
# 思路：按字母从小到大贪心填，lcp[i][j] > 0 的位置合并为同一字母；再从右下向左上验证矩阵是否自洽。
# 时间复杂度：O(n^2)；空间复杂度：O(n)，只存结果字符串与若干下标。
class Solution:  # LeetCode 约定的题解类
    def findTheString(self, lcp: List[List[int]]) -> str:  # lcp 是 n × n 的 LCP 矩阵，返回对应的字符串，无解则返回空串
        n = len(lcp)  # 字符串长度
        s = [""] * n  # 用空串占位，表示该位置还未确定字母
        i = 0  # i 是尚未赋值的最小下标
        for c in ascii_lowercase:  # 按字母表从小到大贪心分配
            while i < n and s[i]:  # 跳过已经赋过字母的位置
                i += 1  # 移到下一个未赋值位置
            if i == n:  # 所有位置都已赋值，字母够用
                break  # 提前结束分配
            for j in range(i, n):  # 与 i 的 LCP 大于 0 的位置必须和 i 是同一个字母
                if lcp[i][j]:  # LCP 大于 0 说明 s[i] 与 s[j] 相同
                    s[j] = c  # 把这些位置统一赋成当前字母
        if "" in s:  # 仍有位置是空串，说明需要超过 26 种字母，无解
            return ""  # 返回空串表示不存在这样的字符串
        for i in range(n - 1, -1, -1):  # 从右下角开始校验，保证用到的 lcp[i+1][j+1] 已经就绪
            for j in range(n - 1, -1, -1):  # 逐列向左扫描
                if s[i] == s[j]:  # 两个字符相同时，LCP 必须比右下方大 1
                    if i == n - 1 or j == n - 1:  # 边界情况：某一行或某一列已经到末尾
                        if lcp[i][j] != 1:  # 边界上同字母的 LCP 必须正好是 1
                            return ""  # 不满足说明矩阵非法，返回空串
                    elif lcp[i][j] != lcp[i + 1][j + 1] + 1:  # 内部位置：LCP 应当等于右下方 LCP 加 1
                        return ""  # 不满足说明矩阵非法，返回空串
                elif lcp[i][j]:  # 字符不同时 LCP 必须为 0
                    return ""  # LCP 不为 0 说明矩阵非法，返回空串
        return "".join(s)  # 拼接并返回构造出的字符串
