# 题目：1156. 单字符重复子串的最大长度（Swap For Longest Repeated Character Substring）
# 思路：统计每个字符总数，再双指针找出「连续段 + 隔一个字符 + 连续段」，长度受该字符总数限制。
# 时间复杂度：O(n)；空间复杂度：O(1)（字符集固定为 26 个字母）。
class Solution:  # LeetCode 约定的题解类
    def maxRepOpt1(self, text: str) -> int:  # 允许交换一次任意两个字符，返回同字符重复子串的最大长度
        cnt = Counter(text)  # 统计每个字符在整串中的总出现次数
        n = len(text)  # 字符串长度
        ans = i = 0  # ans 记录答案；i 是当前连续段的起点
        while i < n:  # 逐个处理连续相同字符段
            j = i  # j 用于探测当前段 [i, j) 的右端点
            while j < n and text[j] == text[i]:  # 向后找与 text[i] 相同的连续字符
                j += 1  # 右端点右移
            l = j - i  # l：当前连续段的长度
            k = j + 1  # k 从隔一个位置开始，跳过中间被换掉的那个字符
            while k < n and text[k] == text[i]:  # 找下一段同字符的连续段
                k += 1  # 继续右移
            r = k - j - 1  # r：第二段长度（两段中间隔了 1 个字符）
            ans = max(ans, min(l + r + 1, cnt[text[i]]))  # 两段拼起来最多用完全部同字符，取较小值
            i = j  # 从下一段继续扫描
        return ans  # 返回最大长度
