# 题目：3088. 使字符串反回文（Make String Anti-palindrome，会员题）
# 思路：先排序；若前后两半在中点处相接会形成回文，就把后半段开头的重复字符与前半段对应位置交换，换不出字符时返回 "-1"。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，sorted 生成了新的字符列表。
class Solution:  # LeetCode 约定的题解类
    def makeAntiPalindrome(self, s: str) -> str:  # s 为输入字符串，返回字典序最小的反回文串，无解时返回 "-1"
        cs = sorted(s)  # 升序排序并转成列表，便于按 下标交换字符
        n = len(cs)  # 字符串长度
        m = n // 2  # 中点下标；前 m 个与后 n-m 个字符两两配对不等时才是反回文
        if cs[m] == cs[m - 1]:  # 中点处两字符相同，说明后半段会与前半段形成对称回文
            i = m  # i 指向后半段中第一个与 cs[m-1] 不同的字符
            while i < n and cs[i] == cs[i - 1]:  # 跳过所有等于 cs[m-1] 的字符
                i += 1  # 继续往后找分界点
            j = m  # j 从后半段起点开始，逐位修复对称位置的冲突
            while j < n and cs[j] == cs[n - j - 1]:  # 当 j 与其对称位置字符相同，就需要交换来解决
                if i >= n:  # 后半段已没有可交换的字符
                    return "-1"  # 无法构造反回文，按题目要求返回 "-1"
                cs[i], cs[j] = cs[j], cs[i]  # 把后半段的 cs[i] 与前半段的 cs[j] 互换，打破对称
                i, j = i + 1, j + 1  # 两个指针同步后移
        return "".join(cs)  # 把字符列表拼回字符串返回
