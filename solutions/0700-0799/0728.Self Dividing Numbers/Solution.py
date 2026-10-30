# 题目：728. 自除数（Self Dividing Numbers）
# 思路：暴力枚举区间内每个数，逐位取出数字，要求该位非 0 且能整除原数，全部满足即为自除数。
# 时间复杂度：O(n·log right)，区间长度乘以位数；空间复杂度：O(1)（不计返回的结果列表）。
class Solution:  # LeetCode 约定的题解类
    def selfDividingNumbers(self, left: int, right: int) -> List[int]:  # left、right 是需要扫描的闭区间端点
        def check(x: int) -> bool:  # 内部函数：判断单个数 x 是否为自除数
            y = x  # 用 y 逐位剥离，避免破坏原数 x
            while y:  # y 为 0 时所有位都检查完了
                if y % 10 == 0 or x % (y % 10):  # 这一位是 0，或原数不能整除这一位，都不满足自除数定义
                    return False  # 提前判定失败
                y //= 10  # 剥掉最低位，继续检查下一位
            return True  # 所有位都能整除原数，返回 True

        # 上面的 check 是判定函数，下面用列表推导一次性筛出答案
        return [x for x in range(left, right + 1) if check(x)]  # 列表推导：遍历闭区间并把通过 check 的数收集成结果列表
