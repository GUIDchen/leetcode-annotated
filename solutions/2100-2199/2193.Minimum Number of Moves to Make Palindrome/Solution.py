# 题目：2193. 得到回文串的最少操作次数（Minimum Number of Moves to Make Palindrome）
# 思路：双指针从两端向中间夹逼；对左端字符在右侧找最近的相同字符并逐个相邻交换到对称位置，找不到说明它是落单的中位字符，直接累加挪到中间的次数。
# 时间复杂度：O(n²)，每次配对最多交换 O(n) 次；空间复杂度：O(n)，需要可变的字符列表。
class Solution:  # LeetCode 约定的题解类
    def minMovesToMakePalindrome(self, s: str) -> int:  # s：待构造成回文串的字符串
        cs = list(s)  # Python 字符串不可变，转成字符列表才能就地交换
        ans, n = 0, len(s)  # ans 累计交换次数；n 是字符串长度
        i, j = 0, n - 1  # 左右指针，向中间收缩待处理区间
        while i < j:  # 区间缩到中心即结束
            even = False  # 本轮是否在右侧找到了与 cs[i] 相同的字符
            for k in range(j, i, -1):  # 从右端向左查找配对字符（不含 i 自身）
                if cs[i] == cs[k]:  # 找到相同字符
                    even = True  # 说明 cs[i] 不是落单字符
                    while k < j:  # 把 cs[k] 一路向右搬到对称位置 j
                        cs[k], cs[k + 1] = cs[k + 1], cs[k]  # 与右邻字符交换，等价于右移一位
                        k += 1  # 指针右移，继续搬运
                        ans += 1  # 交换次数加一
                    j -= 1  # 右端配对完成，右指针左移
                    break  # 本轮处理结束
            if not even:  # 找不到配对字符：它是落单的中位字符
                ans += n // 2 - i  # 把它挪到中间所需的交换次数
            i += 1  # 左指针右移，处理下一个字符
        return ans  # 返回最少交换次数
