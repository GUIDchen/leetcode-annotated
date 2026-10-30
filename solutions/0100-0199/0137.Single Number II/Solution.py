# 题目：137. 只出现一次的数字 II（Single Number II）
# 思路：逐位统计 1 的个数。其余元素都出现三次，所以每一位上 1 的总数模 3 就是答案该位的值；第 31 位按补码负数单独处理。
# 时间复杂度：O(32 * n) = O(n)，定长 32 位逐位扫描；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def singleNumber(self, nums: List[int]) -> int:  # 返回只出现一次的那个数
        ans = 0  # 逐位拼出来的答案
        for i in range(32):  # 32 位整数逐位枚举
            cnt = sum(num >> i & 1 for num in nums)  # 统计所有元素在第 i 位上的 1 的个数（生成器表达式求和）
            if cnt % 3:  # 模 3 不为 0 说明这一位属于那个只出现一次的数
                if i == 31:  # 第 31 位是符号位；Python 整数无溢出，1 << 31 会变成正数
                    ans -= 1 << i  # 用减法把它按补码解释成负数
                else:  # 其余普通位
                    ans |= 1 << i  # 直接把第 i 位置 1
        return ans  # 返回拼好的答案
