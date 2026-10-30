# 题目：67. 二进制求和（Add Binary）
# 思路：双指针从两串末尾逐位相加，carry 保存进位；低位结果依次加入列表，最后反转拼接成字符串。
# 时间复杂度：O(max(m, n))，循环次数由较长串决定；空间复杂度：O(max(m, n))，用于保存结果各位。
class Solution:  # LeetCode 约定的题解类
    def addBinary(self, a: str, b: str) -> str:  # a、b：两个二进制数的字符串表示
        ans = []  # 逐位收集结果的字符（先低位后高位）
        i, j, carry = len(a) - 1, len(b) - 1, 0  # i、j 指向两串末尾（最低位），carry 为进位初值 0
        while i >= 0 or j >= 0 or carry:  # 只要还有位没处理完或还有进位就继续
            carry += (0 if i < 0 else int(a[i])) + (0 if j < 0 else int(b[j]))  # 累加两串当前位，越界时按 0 处理
            carry, v = divmod(carry, 2)  # 同时求出进位 carry 与当前位的值 v（累加和除以 2 的商与余数）
            ans.append(str(v))  # 把当前位转成字符追加到结果中
            i, j = i - 1, j - 1  # 两个指针同时向高位移动一位
        return "".join(ans[::-1])  # 结果是从低位到高位收集的，反转后再拼接成字符串返回
