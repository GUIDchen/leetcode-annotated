# 4026. 工位的最大间隔 / Maximum Gap Between Stations
# 核心思路：先从右向左贪心求出 skill 每个字符在 station 中最靠右的匹配位置 suf，再从左向右贪心求最靠左的匹配位置 pre，枚举相邻两个字符取 suf[i+1] - pre 的最大值。
# 复杂度：时间 O(n + m)，空间 O(n)（n 为 skill 长度，m 为 station 长度）。
class Solution:  # 题解类定义
    def maximumGap(self, skill: str, station: str) -> int:  # 返回把 skill 作为子序列匹配到 station 时，相邻两个匹配位置之间的最大间隔
        n, m = len(skill), len(station)  # 同时取得 skill 与 station 的长度
        suf = [0] * n  # suf[i] 记录 skill[i] 在 station 中最靠右的可行匹配位置（下标 0 不使用）
        j = m - 1  # 从 station 末尾开始扫描的指针
        for i in range(n - 1, 0, -1):  # 从右向左为 skill 的每个字符寻找最靠右的匹配位置
            while station[j] != skill[i]:  # 指针左移，直到找到与 skill[i] 相同的字符
                j -= 1  # 指针继续左移一位
            suf[i] = j  # 记录该字符最靠右的匹配位置
            j -= 1  # 指针再左移一格，保证匹配位置严格递减

        ans = pre = 0  # ans 记录最大间隔，pre 是从左向右贪心匹配的指针
        for i in range(n - 1):  # 枚举相邻的两个 skill 字符（i 与 i+1）
            while station[pre] != skill[i]:  # 指针右移，直到找到与 skill[i] 相同的字符
                pre += 1  # 指针继续右移一位
            ans = max(ans, suf[i + 1] - pre)  # 让 skill[i] 尽量靠左、skill[i+1] 尽量靠右，得到该处的最大间隔
            pre += 1  # 指针右移一格，保证下一个匹配位置严格递增
        return ans  # 返回最大间隔
