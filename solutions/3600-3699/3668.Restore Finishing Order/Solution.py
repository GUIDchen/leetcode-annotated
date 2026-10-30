# 3668. Restore Finishing Order（重排完成顺序）
# 核心思路：用字典记录每个运动员在 order 中的名次下标，再以该下标为键对 friends 排序。
# 复杂度：时间 O(n + m log m)，空间 O(n)；n 为 order 长度，m 为 friends 长度。
class Solution:  # 定义 Solution 类
    def recoverOrder(self, order: List[int], friends: List[int]) -> List[int]:  # 恢复完成顺序：返回按 order 名次排好的 friends
        d = {x: i for i, x in enumerate(order)}  # 运动员 x 到其在 order 中下标 i 的映射
        return sorted(friends, key=lambda x: d[x])  # 按名次下标升序排序 friends 并返回
