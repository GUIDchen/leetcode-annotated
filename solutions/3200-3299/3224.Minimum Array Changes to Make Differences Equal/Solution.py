# 题目：3224. 使差值相等的最少数组改动次数（Minimum Array Changes to Make Differences Equal）
# 思路：枚举目标差值 t，用差分数组累计每对 (x,y) 的代价：t=y-x 为 0，t<=max(y,k-x) 且 t!=x-y 为 1，其余为 2；前缀和的最小值即答案。
# 时间复杂度：O(n + k)，遍历数组与前缀和各一次；空间复杂度：O(k)，差分数组长度为 k+2。
class Solution:  # LeetCode 约定的题解类
    def minChanges(self, nums: List[int], k: int) -> int:  # nums：输入数组（长度 n 为偶数）；k：元素可改成 0..k 的任意整数
        d = [0] * (k + 2)  # 差分数组覆盖目标差值 0..k，多开一位防止 +1 越界
        n = len(nums)  # 数组长度
        for i in range(n // 2):  # 每一对对称下标 (i, n-1-i) 独立地贡献代价
            x, y = nums[i], nums[-i - 1]  # 取出这对对称位置的元素
            if x > y:  # 保证 x <= y，才能用 y-x 表示原差值
                x, y = y, x  # 交换成升序
            d[0] += 1  # 任意目标差值的基础代价是 1 次修改
            d[y - x] -= 1  # t 恰好等于原差值时不用修改，代价减 1
            d[y - x + 1] += 1  # 越过原差值后代价恢复为 1
            d[max(y, k - x) + 1] -= 1  # 在单次修改能凑出的最大差值 m 之后先减 1 ...
            d[max(y, k - x) + 1] += 2  # ... 再加 2，两句净增 1：超过 m 必须改两个数，代价升到 2
        return min(accumulate(d))  # 前缀和即每个目标差值的总代价，取最小（accumulate 由判题环境提供）
