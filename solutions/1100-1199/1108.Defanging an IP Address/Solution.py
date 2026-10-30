# 题目：1108. IP 地址无效化（Defanging an IP Address）
# 思路：直接调用字符串的 replace，把所有 '.' 一次性替换成 "[.]"，扫描与拼接交给标准库完成。
# 时间复杂度：O(n)，replace 只需扫描一遍字符串；空间复杂度：O(n)，返回的新字符串长度至多 3n。
class Solution:  # LeetCode 约定的题解类
    def defangIPaddr(self, address: str) -> str:  # address 是形如 1.1.1.1 的 IPv4 地址串
        return address.replace('.', '[.]')  # 把所有点号替换成 "[.]"，结果直接作为返回值
