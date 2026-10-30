# 题目：163. 缺失的区间（Missing Ranges）
# 核心思路：分别处理「首元素之前」「相邻元素之间」「末元素之后」三类空档，凡是差大于 1 的地方就产出一段缺失区间。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，除结果列表外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findMissingRanges(  # 形参较多，参数列表跨行书写（保持源文件原有换行）
        self, nums: List[int], lower: int, upper: int  # 参数：nums 严格递增，lower/upper 是闭区间边界
    ) -> List[List[int]]:  # 返回若干段缺失的闭区间
        n = len(nums)  # 缓存长度，最后判断尾元素时要用
        if n == 0:  # 空数组：整个 [lower, upper] 都缺失
            return [[lower, upper]]  # 直接返回这一段
        ans = []  # 收集所有缺失的闭区间
        if nums[0] > lower:  # 首元素大于下界，说明前面有空档
            ans.append([lower, nums[0] - 1])  # 记录 lower 到 nums[0]-1
        for a, b in pairwise(nums):  # pairwise 把相邻元素两两配对，省去手写下标
            if b - a > 1:  # 差值大于 1 才说明中间缺了整数
                ans.append([a + 1, b - 1])  # 缺失区间是 a+1 到 b-1
        if nums[-1] < upper:  # 末元素小于上界，说明后面还有空档
            ans.append([nums[-1] + 1, upper])  # 记录 nums[-1]+1 到 upper
        return ans  # 按从左到右的顺序返回全部缺失区间
