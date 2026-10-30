# 题目：1328. 破坏回文串（Break a Palindrome）
# 思路：贪心。前半段找到第一个非 'a' 的字符改成 'a'，字典序最小；若前半段全是 'a'，则把最后一个字符改成 'b'。
# 时间复杂度：O(n)，只扫前半段；空间复杂度：O(n)，用列表做可变副本。
class Solution:  # 题解类
    def breakPalindrome(self, palindrome: str) -> str:  # palindrome：回文串，返回破坏回文且字典序最小的结果
        n = len(palindrome)  # 字符串长度
        if n == 1:  # 长度为 1 无法破坏回文
            return ""  # 按题意返回空串
        s = list(palindrome)  # 转成列表以便原地修改字符
        i = 0  # i 为从左扫描的下标
        while i < n // 2 and s[i] == "a":  # 只看前半段，找到第一个不是 'a' 的位置
            i += 1  # 跳过 'a' 继续往后找
        if i == n // 2:  # 前半段全是 'a'：改前面只会变成更小的回文，只能动末尾
            s[-1] = "b"  # 把最后一个字符改成 'b'
        else:  # 否则存在可以改小的位置
            s[i] = "a"  # 把第一个非 'a' 的字符改成 'a'
        return "".join(s)  # 拼回字符串返回
