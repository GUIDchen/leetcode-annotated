# 题目：3022. 给定操作次数内使剩余元素的或值最小（Minimize OR of Remaining Elements Using Operations）
# 核心思路：从第 29 位向低位贪心。ans 记录「已确认可以清成 0 的位」，每轮把当前位也加入约束掩码 test，扫描数组统计把各段按位与清 0 需要多做的操作数 cnt：超过 k 则该位只能为 1，计入 rans；否则把该位加入 ans 再判断低位。
# 时间复杂度：O(30n)，每一位都要线性扫一遍数组；空间复杂度：O(1)，只用常数个计数与掩码变量。
class Solution:  # LeetCode 约定的题解类
    def minOrAfterOperations(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：最多允许执行的操作次数；返回操作后剩余元素或值的最小值
        ans = 0  # ans：已确认「可以清成 0」的位组成的掩码
        rans = 0  # rans：被迫为 1 的位组成的最终答案
        for i in range(29, -1, -1):  # 元素都小于 2^30，所以从最高位 29 逐位判断到最低位 0
            test = ans + (1 << i)  # 在已有约束上再假设当前位也要清 0，得到本轮探测掩码
            cnt = 0  # cnt：在 test 约束下必须多做的合并（操作）次数
            val = 0  # val：当前这一段元素在 test 掩码下的按位与结果
            for num in nums:  # 从左到右扫描，把元素尽量并成「按位与为 0」的段
                if val == 0:  # val 为 0 说明上一段已经归零结束，当前元素开启新的一段
                    val = test & num  # 新段初值：只保留 test 关心的那些位
                else:  # 这一段还没归零，继续把当前元素并进来
                    val &= test & num  # 按位与只会让 val 的 1 越来越少，最终可能变成 0
                if val:  # 并入后这一段仍然不为 0，说明还消不掉
                    cnt += 1  # 记一次消耗；整段最终归零时这里累计的次数正好等于段长 − 1
            if cnt > k:  # 需要的操作数超过 k，这一位不可能清成 0
                rans += 1 << i  # 该位只能保留在答案中
            else:  # 操作数在 k 以内，这一位可以清成 0
                ans += 1 << i  # 把该位加入约束掩码，后续判断低位时也要一并清 0
        return rans  # 返回所有被迫为 1 的位拼成的答案
