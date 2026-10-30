# 题目：2609. 最长平衡子字符串（Find the Longest Balanced Substring of a Binary String）
# 思路：枚举所有子串，校验「前半全为 0、后半全为 1 且两段长度相等」，取满足条件的最大长度。
# 时间复杂度：O(n^3)，枚举 O(n^2) 个子串、每个校验 O(n)；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findTheLongestBalancedSubstring(self, s: str) -> int:  # s 是只含 0/1 的字符串，返回最长平衡子串长度
        def check(i, j):  # 判断 s[i..j] 是否为「前半全 0、后半全 1 且两段等长」
            cnt = 0  # cnt：子串中字符 '1' 的个数
            for k in range(i, j + 1):  # 从左到右扫描子串
                if s[k] == '1':  # 遇到字符 '1'
                    cnt += 1  # '1' 的个数加一
                elif cnt:  # 已经出现过 '1'，却又遇到 '0'
                    return False  # 顺序被破坏，不是平衡子串
            return cnt * 2 == (j - i + 1)  # '1' 的个数乘以 2 等于长度，说明 0 与 1 各占一半

        n = len(s)  # n：字符串长度
        ans = 0  # ans：目前的最长平衡子串长度
        for i in range(n):  # 枚举子串左端点
            for j in range(i + 1, n):  # 枚举右端点，长度至少为 2
                if check(i, j):  # 该子串是平衡子串
                    ans = max(ans, j - i + 1)  # 用它的长度更新答案
        return ans  # 返回最长平衡子串长度
