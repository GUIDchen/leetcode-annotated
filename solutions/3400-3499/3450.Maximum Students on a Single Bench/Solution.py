# 题目：3450. 一张长椅上的最多学生（Maximum Students on a Single Bench）
# 思路：同一张长椅上可能有多条记录，同一个学生也可能被重复记录，所以用「长椅编号 -> 学生编号集合」的字典聚拢数据，集合天然去重；最后取每个集合大小的最大值。
# 时间复杂度：O(n)，每条记录只做一次集合插入；空间复杂度：O(n)，最坏情况下存下所有记录。
class Solution:  # LeetCode 约定的题解类
    def maxStudentsOnBench(self, students: List[List[int]]) -> int:  # students：每条记录是 [student_id, bench_id]；返回单张长椅上的最多学生数
        if not students:  # 数据为空时直接返回 0，避免后面 max 取空序列报错
            return 0  # 没有任何记录，最多人数就是 0
        d = defaultdict(set)  # d：长椅编号 -> 坐在这张长椅上的学生集合（自动去重）
        for student_id, bench_id in students:  # 遍历每条学生与长椅的记录，逐项解包
            d[bench_id].add(student_id)  # 把学生放进对应长椅的集合，重复添加不会生效
        return max(map(len, d.values()))  # 取每张长椅集合的大小，返回其中的最大值
