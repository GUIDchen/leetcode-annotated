# 题目：3517. 最小回文排列 I（Smallest Palindromic Rearrangement I）
# 思路：统计每个字母的数量，按字母序取一半拼出字典序最小的左半部分，中间放奇数次字符，再镜像拼接成回文。
# 时间复杂度：O(n + |Σ|)；空间复杂度：O(|Σ|)，|Σ| = 26。
class Solution:  # LeetCode 约定的题解类
    def smallestPalindrome(self, s: str) -> str:  # s：输入字符串；返回字典序最小的回文排列
        cnt = Counter(s)  # 统计每个字母的出现次数
        t = []  # t：收集左半部分的片段
        ch = ""  # ch：最多一个出现奇数次的字符，作为回文中心
        for c in ascii_lowercase:  # 按字母序从小到大遍历，保证字典序最小
            v = cnt[c] // 2  # v：该字母能成对使用的对数
            t.append(c * v)  # 把 v 个该字母追加到左半部分
            cnt[c] -= v * 2  # 扣掉已经成对使用的字符
            if cnt[c] == 1:  # 还剩一个说明它出现奇数次，作为中心字符
                ch = c  # 记录中心字符
        ans = "".join(t)  # 左半部分拼接成字符串
        ans = ans + ch + ans[::-1]  # 拼接中心字符与逆序的左半部分，得到回文
        return ans  # 返回字典序最小的回文排列
