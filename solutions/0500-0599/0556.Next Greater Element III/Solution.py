# 题目：556. 下一个更大元素 III（Next Greater Element III）
# 核心思路：按「下一个排列」找法：从右找第一个升位，与其右侧稍大的数交换，再将后缀反转成升序。
# 时间复杂度：O(d)，d 为位数；空间复杂度：O(d)，用于存放字符列表。
class Solution:  # LeetCode 约定的题解类
    def nextGreaterElement(self, n: int) -> int:  # n 为正整数，返回同数字组成且更大的最小整数，不存在则返回 -1
        cs = list(str(n))  # 把数字拆成字符列表，便于交换与反转
        n = len(cs)  # 复用 n 记录位数
        i, j = n - 2, n - 1  # i 指向倒数第二位，j 指向末位
        while i >= 0 and cs[i] >= cs[i + 1]:  # 从右往左找第一个升位 s[i] < s[i+1]
            i -= 1  # 不满足升位就继续左移
        if i < 0:  # 找不到升位说明序列整体非递增，没有更大的排列
            return -1  # 按题意返回 -1
        while cs[i] >= cs[j]:  # 从右往左找第一个大于 s[i] 的数字，保证换完增量最小
            j -= 1  # 继续左移直到找到
        cs[i], cs[j] = cs[j], cs[i]  # 交换这两个字符，让被选中的那一位变大
        cs[i + 1 :] = cs[i + 1 :][::-1]  # 把后缀反转成升序，得到「刚好大于原值」的最小排列
        ans = int(''.join(cs))  # 拼回字符串再转成整数
        return -1 if ans > 2**31 - 1 else ans  # 超过 32 位有符号整数上限时视为无解
