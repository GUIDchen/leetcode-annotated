# 题目：2566. 替换一个数字后的最大差值（Maximum Difference by Remapping a Digit）
# 思路：把首位数字全部替换成 0 得到最小值；再从高位往低位找第一个非 9 的数字，把它全部替换成 9 得到最大值，两者相减。
# 时间复杂度：O(d^2)，d 为数字位数（d ≤ 10，可视为常数）；空间复杂度：O(d)，两次字符串替换产生的副本。
class Solution:  # LeetCode 约定的题解类
    def minMaxDifference(self, num: int) -> int:  # num：输入整数，可以把某一种数字全部改写成另一个数字
        s = str(num)  # 转成字符串，便于按位替换
        mi = int(s.replace(s[0], '0'))  # 把首位数字全部换成 '0' 再转回整数，得到最小值
        for c in s:  # 从高位到低位扫描，找第一个不是 '9' 的数字
            if c != '9':  # 找到了可以放大的数字
                return int(s.replace(c, '9')) - mi  # 把所有 c 换成 '9' 得到最大值，减去最小值即最大差值
        return num - mi  # 所有位都是 '9' 时无法变大，最大差值就是 num 减去最小值
