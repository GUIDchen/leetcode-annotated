# 题目：1529. 最少的后缀翻转次数（Minimum Suffix Flips）
# 思路：贪心地从左向右比较实际位与目标位，ans 的奇偶就是当前位被翻转后的真实值，不相等就再翻一次后缀。
# 时间复杂度：O(n)，一趟线性扫描；空间复杂度：O(1)，只维护一个计数器。
class Solution:  # LeetCode 约定的题解类
    def minFlips(self, target: str) -> int:  # target 是目标二进制串，初始串为全 '0'
        ans = 0  # ans 同时表示翻转次数和当前位被翻转的奇偶性
        for v in target:  # 逐字符遍历目标串
            if (ans & 1) ^ int(v):  # ans 为偶数时实际位仍是 0，为奇数时已被翻成 1；异或结果非零说明与目标不符
                ans += 1  # 这一位不匹配，需要对从该位开始的后缀再翻转一次
        return ans  # 返回累计的最少翻转次数
