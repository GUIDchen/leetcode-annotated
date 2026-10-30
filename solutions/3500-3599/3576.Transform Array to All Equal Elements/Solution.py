# 题目：3576. 数组元素相等转换 / Transform Array to All Equal Elements（中等）
# 核心思路：一次操作把相邻两个元素同时取相反数，于是从左往右扫描时用 sign 表示当前位置是否已被前一次操作翻转；逐位尝试把元素变成目标值 target，遇到不等于 target 的元素就必须和下一个元素一起再翻转一次，操作数加一；最后检查末尾元素是否也等于 target 且操作数不超过 k。target 只可能是 nums[0] 或 -nums[0]，两种都试一次。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution:  # 定义题解类
    def canMakeEqual(self, nums: List[int], k: int) -> bool:  # 判断能否在最多 k 次操作内让所有元素相等
        def check(target: int, k: int) -> bool:  # 判断能否把所有元素都变成 target
            cnt, sign = 0, 1  # cnt 记录已用操作数，sign 表示当前元素的符号（1 未翻转，-1 已被翻转）
            for i in range(len(nums) - 1):  # 从左到右处理前 n-1 个元素
                x = nums[i] * sign  # 当前元素在累积翻转后的实际值
                if x == target:  # 已经等于目标值
                    sign = 1  # 不需要再翻转，下一个元素符号为正
                else:  # 不等于目标值
                    sign = -1  # 必须与下一个元素一起翻转，下一个元素符号取反
                    cnt += 1  # 操作数加一
            return cnt <= k and nums[-1] * sign == target  # 操作数不超限且最后一个元素也已等于目标值

        return check(nums[0], k) or check(-nums[0], k)  # 目标值只能是 nums[0] 或其相反数，任一可行即可
