# 题目：1296. 划分数组为连续数字的集合（Divide Array in Sets of K Consecutive Numbers）
# 思路：排序后用 Counter 统计每个值的剩余次数，从小到大以每个仍有剩余的值开一组，连续消耗 k 个数。
# 时间复杂度：O(n log n)，排序占主导；空间复杂度：O(n)，Counter 存放每个值的剩余次数。
class Solution:  # LeetCode 约定的题解类
    def isPossibleDivide(self, nums: List[int], k: int) -> bool:  # nums：输入数组；k：每组连续数字个数
        if len(nums) % k:  # 总数不是 k 的整数倍，无法完全分组
            return False  # 直接返回不可能
        cnt = Counter(nums)  # 统计每个数值出现的次数，缺失的键取值按 0 处理
        for x in sorted(nums):  # 升序扫描，保证每次都从小到大开新组
            if cnt[x]:  # 该值还有剩余，说明必须从它开始新的一组
                for y in range(x, x + k):  # 组内需要 x, x+1, ..., x+k-1
                    if cnt[y] == 0:  # 某个连续值已被用光，凑不齐一组
                        return False  # 分组失败
                    cnt[y] -= 1  # 用掉一个该值
        return True  # 所有元素都被成功分组
