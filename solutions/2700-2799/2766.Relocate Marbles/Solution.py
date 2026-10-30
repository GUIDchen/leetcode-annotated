# 题目：2766. 重新放置石块（Relocate Marbles）
# 思路：用哈希集合维护所有石块当前的位置；逐次把源位置从集合删掉、把目标位置加进去，最后返回升序排列的结果。
# 时间复杂度：O(n + k + p log p)，p 是最终不同位置数；空间复杂度：O(p)，集合与排序结果都只存这些位置。
class Solution:  # LeetCode 约定的题解类
    def relocateMarbles(  # nums：初始位置；moveFrom/moveTo：逐次移动的源与目标（形参跨两行书写）
        self, nums: List[int], moveFrom: List[int], moveTo: List[int]  # 三个入参分别是初始位置、移动源数组、移动目标数组
    ) -> List[int]:  # 返回所有石块最终位置的升序列表
        pos = set(nums)  # 用集合去重地记录所有石块当前所在的位置
        for f, t in zip(moveFrom, moveTo):  # 并排取出每一次移动的源位置 f 与目标位置 t
            pos.remove(f)  # 石块离开 f；题目保证 f 上一定有石块，所以可以安全 remove
            pos.add(t)  # 石块到达 t，集合自动去重
        return sorted(pos)  # sorted 返回新列表，不改动集合本身
