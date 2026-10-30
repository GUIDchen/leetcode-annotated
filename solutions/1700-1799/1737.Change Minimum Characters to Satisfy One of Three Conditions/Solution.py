# 题目：1737. 满足三条件之一需改变的最少字符数（Change Minimum Characters to Satisfy One of Three Conditions）
# 思路：先统计两串的 26 个字母频次。条件三是让两串都变成同一个字母；条件一、二是以某个字母为分界，让一串全部严格小于另一串，枚举分界取最小。
# 时间复杂度：O(m + n + 26²)，统计频次加枚举分界；空间复杂度：O(26)，两个计数数组。
class Solution:  # LeetCode 约定的题解类
    def minCharacters(self, a: str, b: str) -> int:  # a、b 是两个待调整的字符串
        def f(cnt1, cnt2):  # 辅助函数：计算“第一串全部严格小于第二串”的最少改动数
            for i in range(1, 26):  # i 为分界字母：第一串取小于 i 的，第二串取不小于 i 的
                t = sum(cnt1[i:]) + sum(cnt2[:i])  # 第一串中不小于 i 的字符要改小，第二串中小于 i 的字符要改大
                nonlocal ans  # 声明 ans 来自外层函数，才能在内层为它赋值
                ans = min(ans, t)  # 用当前方案更新最优答案

        m, n = len(a), len(b)  # 两个字符串的长度
        cnt1 = [0] * 26  # cnt1[i] 表示 a 中第 i 个字母的出现次数（下标 0 对应 'a'）
        cnt2 = [0] * 26  # cnt2[i] 表示 b 中第 i 个字母的出现次数
        for c in a:  # 遍历 a 的每个字符
            cnt1[ord(c) - ord('a')] += 1  # 把字符映射到 0..25 后累加计数
        for c in b:  # 遍历 b 的每个字符
            cnt2[ord(c) - ord('a')] += 1  # 同样累加 b 的字母计数
        ans = m + n  # 答案上界：最坏情况所有字符都要改
        for c1, c2 in zip(cnt1, cnt2):  # 同时遍历两个计数数组，下标即字母
            ans = min(ans, m + n - c1 - c2)  # 条件三：两串都改成该字母，可保留 c1 + c2 个字符
        f(cnt1, cnt2)  # 条件一：a 全部严格小于 b
        f(cnt2, cnt1)  # 条件二：b 全部严格小于 a，交换参数复用逻辑
        return ans  # 三种条件中的最小值就是答案
