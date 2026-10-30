# 题目：1404. 将二进制表示减到 1 的步骤数（Number of Steps to Reduce a Number in Binary Representation to One）
# 思路：从最低位向高位模拟「奇数加一、偶数除以二」：carry 记录低位传来的进位，遇 1 记一次加一并置进位，每处理一位再记一次除以二。
# 时间复杂度：O(n)，n 为二进制串长度；空间复杂度：O(1)，仅常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numSteps(self, s: str) -> int:  # s 为不含前导零的二进制字符串
        carry = False  # 低位「加一」产生的进位标志
        ans = 0  # 累计操作步数
        for c in s[:0:-1]:  # 切片 s[:0:-1] 从末尾逆序取到下标 1，跳过最高位
            if carry:  # 有进位时先处理当前位的翻转
                if c == '0':  # 0 加进位成为 1
                    c = '1'  # 本位置 1
                    carry = False  # 进位被消化，不再向高位传递
                else:  # 1 加进位成为 0，进位继续向高位传递
                    c = '0'  # 本位置 0，carry 仍为 True
            if c == '1':  # 当前位是奇数，需要一次加一
                ans += 1  # 计入加一操作
                carry = True  # 加一会向高位进位
            ans += 1  # 变偶数后必有一次除以二操作
        if carry:  # 最高位仍有进位，说明还要多一步
            ans += 1  # 补记这一步
        return ans  # 返回总步数
