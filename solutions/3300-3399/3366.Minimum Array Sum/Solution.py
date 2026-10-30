# 题目：3366. 最小数组和（Minimum Array Sum）
# 思路：三维 DP，f[i][j][k] 表示处理前 i 个数、已用 j 次除 2 与 k 次减 d 时的最小和，逐个数枚举不用操作、单用一种操作、两种操作同用的三种搭配。
# 时间复杂度：O(n * op1 * op2)，每个状态常数次转移；空间复杂度：O(n * op1 * op2)，需要保存整张 DP 表。
class Solution:  # LeetCode 约定的题解类
    def minArraySum(self, nums: List[int], d: int, op1: int, op2: int) -> int:  # nums：原数组；d：减法操作的减数；op1、op2：两种操作各自可用的次数
        n = len(nums)  # 元素个数
        f = [[[inf] * (op2 + 1) for _ in range(op1 + 1)] for _ in range(n + 1)]  # 三维 DP 表：f[i][j][k] 表示处理前 i 个数、用 j 次操作一、k 次操作二的最小和，先整体置 inf
        f[0][0][0] = 0  # 边界：什么都没处理、什么都没操作时，和为 0
        for i, x in enumerate(nums, 1):  # i 从 1 开始既当元素个数又是下标，x 为当前元素值
            for j in range(op1 + 1):  # 枚举已经用掉的操作一次数 j
                for k in range(op2 + 1):  # 枚举已经用掉的操作二次数 k
                    f[i][j][k] = f[i - 1][j][k] + x  # 情况一：当前元素不做任何操作，直接累加原值
                    if j > 0:  # 情况二：只对当前元素用一次操作一（除以 2）
                        f[i][j][k] = min(f[i][j][k], f[i - 1][j - 1][k] + (x + 1) // 2)  # (x + 1) // 2 就是 x 除以 2 的上取整，与「不用」取较小值
                    if k > 0 and x >= d:  # 情况三：只对当前元素用一次操作二（减去 d），且减完不能为负
                        f[i][j][k] = min(f[i][j][k], f[i - 1][j][k - 1] + (x - d))  # 减去 d 后与当前最优值比较
                    if j > 0 and k > 0:  # 情况四：两种操作都作用在同一个元素上，先后顺序不同结果不同
                        y = (x + 1) // 2  # 先取「除以 2 上取整」的结果 y
                        if y >= d:  # 顺序一：先除 2 再减 d，要求 y >= d
                            f[i][j][k] = min(f[i][j][k], f[i - 1][j - 1][k - 1] + y - d)  # 用 y - d 做转移，与当前最优值取小
                        if x >= d:  # 顺序二：先减 d 再除 2，要求原值 x >= d
                            f[i][j][k] = min(
                                f[i][j][k], f[i - 1][j - 1][k - 1] + (x - d + 1) // 2  # 转移来源是「对 x - d 上取整除以 2」，即 (x - d + 1) // 2
                            )
        ans = inf  # 答案取所有可能剩余操作次数状态中的最小值
        for j in range(op1 + 1):  # 枚举最终用掉的操作一次数
            for k in range(op2 + 1):  # 枚举最终用掉的操作二次数
                ans = min(ans, f[n][j][k])  # 在所有合法结束状态中取最小
        return ans  # 返回最小数组和
