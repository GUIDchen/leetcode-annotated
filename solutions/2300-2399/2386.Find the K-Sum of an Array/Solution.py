# 题目：2386. 找出数组的第 K 大和（Find the K-Sum of an Array）
# 核心思路：所有正数之和 mx 就是第 1 大和；把负数取绝对值后排序，求第 k-1 小的子集和，用小根堆按「选 / 不选 / 替换」递推弹出，最后 mx 减去该值即为答案。
# 时间复杂度：O(n log n + k log k)，一次排序加 k-1 次堆操作；空间复杂度：O(n + k)，存绝对值数组与堆。
class Solution:  # LeetCode 约定的题解类
    def kSum(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 表示要找第 k 大的子集和
        mx = 0  # mx 累加所有正数，得到最大的子集和（第 1 大和）
        for i, x in enumerate(nums):  # 同时取出下标 i 与元素值 x
            if x > 0:  # 正数直接贡献到最大和里
                mx += x  # 累加当前正数
            else:  # 否则元素为负数或 0，需要改成绝对值参与「减少量」计算
                nums[i] = -x  # 选中负元素的代价是减去它的绝对值，所以原地取反
        nums.sort()  # 按绝对值升序排序，保证堆按从小到大的让步顺序枚举
        h = [(0, 0)]  # 小根堆的初始状态：(当前子集和 0, 下一个待决策下标 0)，代表空子集
        for _ in range(k - 1):  # 只需弹出 k-1 次，堆顶就是第 k-1 小的子集和
            s, i = heappop(h)  # 取出并弹出当前最小的子集和状态
            if i < len(nums):  # 下标还在范围内才继续扩展这个状态
                heappush(h, (s + nums[i], i + 1))  # 扩展一：选上 nums[i]，子集和随之增加 nums[i]
                if i:  # i 非 0 时才存在「把上一个数换成当前数」的第二种扩展
                    heappush(h, (s + nums[i] - nums[i - 1], i + 1))  # 扩展二：用 nums[i] 替换 nums[i-1]，只补上两者的差值
        return mx - h[0][0]  # 第 k 大和 = mx 减去第 k-1 小的减少量，堆顶即该减少量
