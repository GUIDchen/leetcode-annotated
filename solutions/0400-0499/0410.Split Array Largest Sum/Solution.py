# 题目：410. 分割数组的最大值（Split Array Largest Sum）
# 思路：二分答案，判定函数贪心地顺序切分并统计段数；用 bisect_left 在答案区间上找第一个可行值。
# 时间复杂度：O(n log(sum - max))，每次判定 O(n)；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def splitArray(self, nums: List[int], k: int) -> int:  # nums 是非负数组，k 是必须切成的连续段数
        def check(mx):  # 判定函数：子数组和上限为 mx 时，贪心分段所需段数是否 ≤ k
            s, cnt = inf, 0  # s 用 inf 保证首元素触发一次切段；cnt 记录段数
            for x in nums:  # 顺序累加，保持原数组顺序
                s += x  # 把当前元素并入当前段
                if s > mx:  # 超过上限就必须在此处切开
                    s = x  # 当前元素成为新一段的开头
                    cnt += 1  # 段数加一
            return cnt <= k  # 段数不超过 k 即可行

        left, right = max(nums), sum(nums)  # 二分下界是最大元素，上界是整个数组之和
        return left + bisect_left(range(left, right + 1), True, key=check)  # 在 [left, right] 上二分出第一个 key 为 True 的位置，即最小可行上限
