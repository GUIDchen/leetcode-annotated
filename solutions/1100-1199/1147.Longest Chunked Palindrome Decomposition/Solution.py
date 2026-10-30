# 题目：1147. 段式回文（Longest Chunked Palindrome Decomposition）
# 思路：双指针从两端向中间走，枚举最短的相同前后缀长度 k，能匹配就左右各切一段计入答案，最后中间剩余部分单独算一段。
# 时间复杂度：O(n^2)，每次匹配最坏要比较 O(n) 个字符；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def longestDecomposition(self, text: str) -> int:  # text 为待分解的字符串
        ans = 0  # ans 记录段式回文的段数
        i, j = 0, len(text) - 1  # i 指向左端，j 指向右端
        while i <= j:  # 两指针向中间收缩
            k = 1  # 本轮尝试的切分长度
            ok = False  # 标记本轮是否成功切分
            while i + k - 1 < j - k + 1:  # 条件保证左右两段不重叠
                if text[i : i + k] == text[j - k + 1 : j + 1]:  # 左右两段完全相同
                    ans += 2  # 一次切分贡献两段
                    i += k  # 左边界右移 k
                    j -= k  # 右边界左移 k
                    ok = True  # 标记本轮成功
                    break  # 最短的合法切分成立即可跳出
                k += 1  # 长度加一，继续尝试
            if not ok:  # 找不到可以配对的相同前后缀
                ans += 1  # 中间剩下的整体算作一段
                break  # 结束整个循环
        return ans  # 返回总段数
