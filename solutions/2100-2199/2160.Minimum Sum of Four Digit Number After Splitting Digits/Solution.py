# 题目：2160. 拆分数位后四位数字的最小和（Minimum Sum of Four Digit Number After Splitting Digits）
# 核心思路：把四个数位升序排序，最小的两位分别作两个数的十位、较大的两位作个位，此时两数之和最小。
# 时间复杂度：O(1)，固定只处理 4 位数位；空间复杂度：O(1)，只用长度 4 的列表。
class Solution:  # LeetCode 约定的题解类
    def minimumSum(self, num: int) -> int:  # num：输入的四位整数
        nums = []  # 存放拆出来的数位
        while num:  # 只要还剩下非零部分就继续拆
            nums.append(num % 10)  # 取出当前最低位
            num //= 10  # 整除 10 去掉最低位，准备取更高位
        nums.sort()  # 把数位升序排序
        return 10 * (nums[0] + nums[1]) + nums[2] + nums[3]  # 最小的两位放十位、其余放个位，两数之和最小
