# 题目：2702. 使数字变为非正数的最小操作次数（Minimum Operations to Make Numbers Non-positive）
# 核心思路：二分答案 t。t 次操作相当于每个数先减 t*y，再挑部分元素多减 t*(x-y)（即多给它一次 x 操作）；逐个元素算出至少需要几次 x 操作，总和不超过 t 即 t 次可行。
# 时间复杂度：O(n log(max(nums)))，每次 check 扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], x: int, y: int) -> int:  # nums：数组；x：每次额外单独减的量；y：每次对其余元素统一减的量
        def check(t: int) -> bool:  # 判定函数：t 次操作能否把所有数都变成非正数
            cnt = 0  # cnt：所有元素「必须用 x 操作」的次数总和
            for v in nums:  # 逐个元素估算
                if v > t * y:  # 只靠 t 次 y 还减不到非正
                    cnt += ceil((v - t * y) / (x - y))  # 向上取整，补上 x 操作比 y 多减的部分
            return cnt <= t  # 需要的 x 操作次数不超过总次数 t，则 t 次够用

        l, r = 0, max(nums)  # 二分区间：0 到最大值（最大值全用 y 减也只需要这么多次）
        while l < r:  # 二分最小的可行 t
            mid = (l + r) >> 1  # 取中点，>> 1 等价于整除 2
            if check(mid):  # mid 次可行
                r = mid  # 答案不会超过 mid，收缩上界
            else:  # mid 次不够用
                l = mid + 1  # 答案至少是 mid + 1，抬高下界
        return l  # 二分收敛到最小可行操作次数
