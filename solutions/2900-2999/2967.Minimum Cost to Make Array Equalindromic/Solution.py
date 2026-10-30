# 题目：2967. 使数组成为等数数组的最小代价（Minimum Cost to Make Array Equalindromic）
# 思路：预处理出 10 位以内的所有回文数并排序，取数组的中位数，用二分定位它附近的候选回文数，在这几个候选里取总绝对差最小者。
# 时间复杂度：预处理 O(2*10^5 log 2*10^5) 只做一次，每次调用 O(n log n + n + log 2*10^5)；空间复杂度：O(2*10^5)，全局回文数表。
ps = []  # 全局列表：预先存放所有 10 位以内的回文数
for i in range(1, 10**5 + 1):  # 枚举回文的「前缀」 i，用它拼出偶数位与奇数位两种回文
    s = str(i)  # 前缀转成字符串，方便做反转和拼接
    t1 = s[::-1]  # t1 是 s 的倒序，拼在 s 后面得到偶数位回文（如 12 -> 1221）
    t2 = s[:-1][::-1]  # t2 是去掉最后一位后的倒序，拼在 s 后面得到奇数位回文（如 12 -> 121）
    ps.append(int(s + t1))  # 加入偶数位回文
    ps.append(int(s + t2))  # 加入奇数位回文
ps.sort()  # 排序后即可二分查找候选回文数


class Solution:  # LeetCode 约定的题解类
    def minimumCost(self, nums: List[int]) -> int:  # nums 是输入数组，把所有元素改成同一个回文数，返回最小总代价
        def f(x: int) -> int:  # 内部函数：把数组全部改成 x 所需的总代价
            return sum(abs(v - x) for v in nums)  # 生成器求和，累加每个元素与 x 的绝对差

        nums.sort()  # 先排序，最优目标值是中位数附近的回文数
        i = bisect_left(ps, nums[len(nums) // 2])  # 二分找到第一个不小于中位数的回文数下标，答案只可能在它左右各一个候选里
        return min(f(ps[j]) for j in range(i - 1, i + 2) if 0 <= j < len(ps))  # 在 i-1、i、i+1 三个候选（且下标合法）中取总代价最小者
