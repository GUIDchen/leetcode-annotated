# 题目：1044. 最长重复子串（Longest Duplicate Substring）
# 思路：字符串哈希 + 二分答案；先递推出 base=131 的前缀哈希，再二分重复子串长度 l，每次用集合 O(n) 判断是否存在长度为 l 的重复子串。
# 时间复杂度：O(n log n)，n 为串长；空间复杂度：O(n)，前缀哈希数组与去重集合。
class Solution:  # LeetCode 约定的题解类
    def longestDupSubstring(self, s: str) -> str:  # s：输入字符串；返回其中最长的重复子串
        def check(l: int) -> str:  # 内部函数：判断是否存在长度为 l 的重复子串，闭包引用外层的 n、p、h
            vis = set()  # 记录已经扫描过的区间哈希值
            for i in range(1, n - l + 2):  # i 为区间左端点的 1 基下标，右端点 j 不能超过 n
                j = i + l - 1  # j 为区间右端点的 1 基下标
                t = h[j] - h[i - 1] * p[j - i + 1]  # 区间哈希：h[j] - h[i-1]*base^l，与 C++ 版公式一致
                if t in vis:  # 该哈希值已经出现过，说明子串重复
                    return s[i - 1 : j]  # 返回这段重复子串（切片右端是开区间，正好对应 j）
                vis.add(t)  # 首次出现，加入集合供后续区间比对
            return ''  # 全部扫描完没有重复，返回空串表示长度 l 不可行

        base, n = 131, len(s)  # base 取质数 131 降低碰撞概率；n 为串长
        p = [0] * (n + 10)  # p[i] = base^i，多开 10 个位置防止越界
        h = [0] * (n + 10)  # h[i] = 前缀 s[0..i-1] 的哈希值
        p[0] = 1  # base^0 = 1，作为递推起点
        for i, c in enumerate(s):  # 一遍递推求出所有幂次与前缀哈希
            p[i + 1] = p[i] * base  # 逐项乘 base 得到 base^(i+1)
            h[i + 1] = h[i] * base + ord(c)  # 秦九韶式前缀哈希，用字符的编码接到哈希末尾
        left, right = 0, n  # 二分答案的区间端点：答案长度落在 [0, n]
        ans = ''  # 记录当前找到的最长重复子串
        while left < right:  # 二分最大的「存在重复」的子串长度
            mid = (left + right + 1) >> 1  # 上取整中点，保证 left 单调前进、循环能收敛
            t = check(mid)  # 检查长度 mid 是否可行
            if t:  # 非空说明存在长度为 mid 的重复子串
                left = mid  # 答案至少是 mid，抬高下界
                ans = t  # 记录这个可行的重复子串
            else:  # 该长度不可行
                right = mid - 1  # 收缩上界
        return ans  # 二分结束时 ans 就是最长重复子串（无重复则为空串）
