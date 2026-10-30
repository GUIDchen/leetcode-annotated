# 题目：1570. 两个稀疏向量的点积（Dot Product of Two Sparse Vectors）
# 思路：构造时只把非零元素存进字典（下标 → 值），求点积时遍历较小的字典，用 get 取另一向量同下标的值为默认 0 再累加。
# 时间复杂度：构造 O(n)；点积 O(min(非零个数))；空间复杂度：O(非零个数)，只存非零项。
class SparseVector:  # 表示稀疏向量的类
    def __init__(self, nums: List[int]):  # 构造函数：nums 是完整向量
        self.d = {i: v for i, v in enumerate(nums) if v}  # 字典推导式，只保留下标 i 与值 v 都非零的项

    # Return the dotProduct of two sparse vectors
    def dotProduct(self, vec: "SparseVector") -> int:  # vec：另一个稀疏向量，返回两者的点积
        a, b = self.d, vec.d  # 取出两张「下标 → 值」字典
        if len(b) < len(a):  # 保证 a 是元素更少的那张表
            a, b = b, a  # 交换，使遍历代价更小
        return sum(v * b.get(i, 0) for i, v in a.items())  # 遍历较小表，缺失下标按 0 处理，把乘积求和


# Your SparseVector object will be instantiated and called as such:
# v1 = SparseVector(nums1)
# v2 = SparseVector(nums2)
# ans = v1.dotProduct(v2)
