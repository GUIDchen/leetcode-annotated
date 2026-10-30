# 题目：1700. 无法吃午餐的学生数量（Number of Students Unable to Eat Lunch）
# 思路：用计数器统计两种偏好的学生人数，再按三明治栈顶顺序逐个消耗；栈顶类型没人要时队伍卡死。
# 时间复杂度：O(n + m)，n 为学生数、m 为三明治数；空间复杂度：O(1)，计数器最多存两个键。
class Solution:  # LeetCode 约定的题解类
    def countStudents(self, students: List[int], sandwiches: List[int]) -> int:  # students：学生偏好；sandwiches：三明治栈
        cnt = Counter(students)  # 统计每种偏好（0 或 1）各有多少名学生
        for v in sandwiches:  # 按栈的顺序逐个尝试发放三明治
            if cnt[v] == 0:  # 当前类型已经没有学生想要了，队伍无法继续
                return cnt[v ^ 1]  # 剩下的人都属于另一种偏好，v ^ 1 把 0 变 1、1 变 0
            cnt[v] -= 1  # 有人领走该型三明治并离队，计数减一
        return 0  # 三明治全部发完，没有人挨饿
