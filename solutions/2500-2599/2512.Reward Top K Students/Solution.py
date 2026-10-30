# 题目：2512. 奖励最顶尖的 K 名学生（Reward Top K Students）
# 思路：正面词、负面词各存一个集合，逐条评语按空格拆词累计得分，再按「分数降序、学号升序」排序后取前 k 个学号。
# 时间复杂度：O(R·L + R log R)，R 为学生数、L 为评语单词数，排序占 R log R；空间复杂度：O(R + P + N)，即结果表与两个词表。
class Solution:  # LeetCode 约定的题解类
    def topStudents(  # 返回得分最高的 k 名学生的学号
        self,  # 方法自身
        positive_feedback: List[str],  # 正面评语词表
        negative_feedback: List[str],  # 负面评语词表
        report: List[str],  # 每个学生的评语
        student_id: List[int],  # 每个学生的学号
        k: int,  # 要奖励的人数
    ) -> List[int]:  # 返回前 k 名学生的学号列表
        ps = set(positive_feedback)  # 正面词集合，判断是否加分只需 O(1)
        ns = set(negative_feedback)  # 负面词集合，判断是否扣分只需 O(1)
        arr = []  # 存放 (得分, 学号) 二元组
        for sid, r in zip(student_id, report):  # 学号与评语一一对应，用 zip 同时遍历
            t = 0  # 当前学生的得分
            for w in r.split():  # 按空白把评语拆成单词
                if w in ps:  # 该词属于正面评语
                    t += 3  # 加 3 分
                elif w in ns:  # 该词属于负面评语
                    t -= 1  # 扣 1 分
            arr.append((t, sid))  # 记录这个学生的得分与学号
        arr.sort(key=lambda x: (-x[0], x[1]))  # 排序键：分数取负实现降序，第二关键字学号升序
        return [v[1] for v in arr[:k]]  # 取前 k 个二元组中的学号组成答案
