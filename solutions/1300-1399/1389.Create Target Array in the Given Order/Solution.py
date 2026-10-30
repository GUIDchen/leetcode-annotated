# 题目：1389. 按既定顺序创建目标数组（Create Target Array in the Given Order）
# 思路：用 zip 同步取出「数值」与「插入位置」，逐个插入 target；list.insert 会自动把插入点之后的元素右移。
# 时间复杂度：O(n^2)，每次 list.insert 平均要移动 O(n) 个元素；空间复杂度：O(n)，target 保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def createTargetArray(self, nums: List[int], index: List[int]) -> List[int]:  # nums 是待插入的数值，index 是每个数值对应的插入位置
        target = []  # 目标数组，初始为空
        for x, i in zip(nums, index):  # 同步遍历两个数组：x 是数值，i 是它要插入的下标
            target.insert(i, x)  # 把 x 插入到下标 i 处，后面的元素自动右移一位
        return target  # 返回构造完成的目标数组
