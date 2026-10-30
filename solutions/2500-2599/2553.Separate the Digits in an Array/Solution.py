# 题目：2553. 分割数组中数字的数位（Separate the Digits in an Array）
# 思路：对每个数字反复取 x % 10 得到逆序数位，再用切片 t[::-1] 反转后接到答案末尾。
# 时间复杂度：O(总位数)，每个数位只处理一次；空间复杂度：O(总位数)，ans 存放全部数位，t 只存单个数字的位数。
class Solution:  # LeetCode 约定的题解类
    def separateDigits(self, nums: List[int]) -> List[int]:  # nums 是输入数组，返回按原顺序拆开后的数位列表
        ans = []  # ans 收集最终结果
        for x in nums:  # 依次处理每个数字
            t = []  # t 暂存当前数字的数位，顺序是从低位到高位
            while x:  # x 为 0 时说明数位已经取完
                t.append(x % 10)  # 把最低位追加到 t 中
                x //= 10  # 整除 10 去掉最低位，准备取下一位
            ans.extend(t[::-1])  # 反转后接到答案末尾，得到高位在前的正确顺序
        return ans  # 返回拆好的数位列表
