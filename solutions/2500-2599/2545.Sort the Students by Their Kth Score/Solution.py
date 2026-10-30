# 题目：2545. 根据第 K 场考试的分数排序（Sort the Students by Their Kth Score）
# 思路：用 key 函数按每个学生第 k 列成绩取负，借默认升序实现按该列降序排序。
# 时间复杂度：O(m log m)，m 为学生人数；空间复杂度：O(m)，sorted 返回新列表。
class Solution:  # LeetCode 约定的题解类
    def sortTheStudents(self, score: List[List[int]], k: int) -> List[List[int]]:  # score 每行是一个学生的各科成绩，k 是排序依据的列下标
        return sorted(score, key=lambda x: -x[k])  # 按第 k 列成绩取负值作为排序键，得到该列从大到小的顺序
