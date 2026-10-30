# 题目：3159. 查询数组中元素的出现位置（Find Occurrences of an Element in an Array）
# 核心思路：先用列表推导收集 x 每次出现的下标（天然升序），再用列表推导对每个询问取第 queries[i] 次出现的下标，次数越界则给 -1。
# 时间复杂度：O(n+m)，n 为数组长度、m 为询问数；空间复杂度：O(n)，保存 x 的全部下标。
class Solution:  # LeetCode 约定的题解类
    def occurrencesOfElement(  # 开始定义 occurrencesOfElement，参数分行书写
        self, nums: List[int], queries: List[int], x: int  # nums：原始数组；queries：询问列表；x：被统计的元素值
    ) -> List[int]:  # 返回每个询问对应的下标列表
        ids = [i for i, v in enumerate(nums) if v == x]  # 边遍历边判等，得到升序的 x 出现下标列表
        return [ids[i - 1] if i - 1 < len(ids) else -1 for i in queries]  # i 是 1 起的出现次序，取 ids[i-1]；越界说明出现次数不够，返回 -1
