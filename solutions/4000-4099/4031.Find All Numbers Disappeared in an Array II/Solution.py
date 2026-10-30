# 4031. 找到所有数组中消失的数字 II / Find All Numbers Disappeared in an Array II
# 核心思路：去重排序后顺序扫描落在 [lower, upper] 内的数字，相邻两个已出现数字之间的空缺就是消失的区间，最后再补上尾部区间。
# 复杂度：时间 O(n log n)，空间 O(n)（sorted(set(nums)) 的副本，不计结果）。
class Solution:  # 题解类定义
    def findDisappearedNumbers(  # 返回 [lower, upper] 中未出现在 nums 里的所有数字区间
        self, nums: List[int], lower: int, upper: int  # 参数：数组 nums 与闭区间上下界 lower、upper
    ) -> List[List[int]]:  # 返回值是区间列表
        ans = []  # 保存结果区间
        prev = lower - 1  # 上一个出现过的数字，从 lower - 1 开始
        for x in sorted(set(nums)):  # 去重并排序后顺序扫描，保证数字单调递增
            if x < lower:  # 小于下界的数字对答案没有影响
                continue  # 直接跳过
            if x > upper:  # 超过上界后不可能再有贡献
                break  # 提前结束扫描
            if x - prev > 1:  # 相邻两个已出现数字之间存在空缺
                ans.append([prev + 1, x - 1])  # 把空缺区间 [prev + 1, x - 1] 加入答案
            prev = x  # 更新上一个出现过的数字
        if prev < upper:  # 尾部还有未覆盖的数字
            ans.append([prev + 1, upper])  # 补上尾部区间 [prev + 1, upper]
        return ans  # 返回所有消失的数字区间
