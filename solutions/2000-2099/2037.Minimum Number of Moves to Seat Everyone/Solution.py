# 题目：2037. 使每位学生都有座位的最少移动次数（Minimum Number of Moves to Seat Everyone）
# 思路：排序后按位配对。座位与学生分别升序排序，第 i 小的座位配第 i 小的学生，总位移最小；答案为 ∑|seats[i] - students[i]|。
# 时间复杂度：O(n log n)，两次排序；空间复杂度：O(n)，Timsort 可能额外申请临时空间（原地修改入参）。
class Solution:  # LeetCode 约定的题解类
    def minMovesToSeat(self, seats: List[int], students: List[int]) -> int:  # seats 是座位坐标，students 是学生初始位置，返回最少总移动次数
        seats.sort()  # 座位就地升序排序
        students.sort()  # 学生位置就地升序排序
        return sum(abs(a - b) for a, b in zip(seats, students))  # zip 把排序后的座位与学生按位配对，逐对取距离并求和
