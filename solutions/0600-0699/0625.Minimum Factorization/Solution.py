# 题目：625. 最小因式分解（Minimum Factorization）🔒
# 思路：从 9 到 2 由大到小试因子，因子从低位往高位拼数；位数最少即数值最小，无解或溢出 32 位时返回 0。
# 时间复杂度：O(log num)，因子最多被取出 log num 次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def smallestFactorization(self, num: int) -> int:  # 把 num 分解成若干个大于 1 的因子，使这些因子拼成的整数最小
        if num < 2:  # 0 和 1 本身就是最小分解结果，无需再拆
            return num  # 直接返回原数
        ans, mul = 0, 1  # ans 逐步拼出最小数字，mul 是当前位的权重（1、10、100…）
        for i in range(9, 1, -1):  # 从大到小试因子：因子越大，拼出来的位数越少
            while num % i == 0:  # 把所有因子 i 一次性除干净（用 while 保证不遗漏重复因子）
                num //= i  # 先整除掉一个因子 i
                ans = mul * i + ans  # 把 i 放到当前最低位，原有数字整体左移一位
                mul *= 10  # 权重升一档，供下一次拼位使用
        return ans if num < 2 and ans <= 2**31 - 1 else 0  # 还剩大于 1 的因子（无解）或结果超出 32 位有符号范围都返回 0
