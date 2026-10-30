# 题目：2032. 至少在两个数组中出现的值（Two Out of Three）
# 思路：先把三个数组各自转成集合（自动去重），再枚举 1..100；三个「是否存在」布尔值相加即为出现过的数组个数，大于 1 就是答案。
# 时间复杂度：O(n1 + n2 + n3 + 100)，建集合一趟遍历加固定 100 次判断；空间复杂度：O(n1 + n2 + n3)，三个集合最多存下所有元素。
class Solution:  # LeetCode 约定的题解类
    def twoOutOfThree(  # 方法签名第一行，参数较多所以折行书写
        self, nums1: List[int], nums2: List[int], nums3: List[int]  # nums1/nums2/nums3 是三个输入数组
    ) -> List[int]:  # 返回至少在两个数组中出现过的值（升序）
        s1, s2, s3 = set(nums1), set(nums2), set(nums3)  # 转成 set：既去掉同一个数组内的重复值，也让后面的 in 判断是 O(1)
        return [i for i in range(1, 101) if (i in s1) + (i in s2) + (i in s3) > 1]  # 列表推导式：布尔值参与加法，True 计 1，三个之和大于 1 即至少两个数组含有
