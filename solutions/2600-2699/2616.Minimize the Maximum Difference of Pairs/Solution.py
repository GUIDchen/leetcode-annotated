# 题目：2616. 最小化数对的最大差值（Minimize the Maximum Difference of Pairs）
# 思路：排序后最优配对一定发生在相邻元素之间；对答案 diff 二分，用贪心从左往右扫描，能配就配，判断「差值不超过 diff」能否凑出至少 p 对。
# 时间复杂度：O(n log n + n log(maxDiff))，排序加二分判定；空间复杂度：O(1)，只用常数个额外变量（排序本身不计入）。
class Solution:  # LeetCode 约定的题解类
    def minimizeMax(self, nums: List[int], p: int) -> int:  # nums 输入数组，p 是需要配成的对数；返回配对最大差值的最小可能值
        def check(diff: int) -> bool:  # 差值上限为 diff 时，贪心最多能凑出多少对
            cnt = i = 0  # cnt 已配对数量，i 当前扫描位置
            while i < len(nums) - 1:  # 还需要一个右邻居才能配对
                if nums[i + 1] - nums[i] <= diff:  # nums 已升序，这一对相邻元素的差不超过上限，可以配成一对
                    cnt += 1  # 配对成功，计数加一
                    i += 2  # 两个元素都用掉，指针跳过两位
                else:  # 这一对不满足约束
                    i += 1  # 只能跳过左端点继续尝试
            return cnt >= p  # 贪心得到的就是该上限下的最大对数

        nums.sort()  # 排序后最优配对只可能来自相邻元素
        return bisect_left(range(nums[-1] - nums[0] + 1), True, key=check)  # 在 0..maxDiff 的虚拟序列上二分：key=check 把每个候选映射为布尔值，返回第一个真值下标（需 Python 3.10+）
