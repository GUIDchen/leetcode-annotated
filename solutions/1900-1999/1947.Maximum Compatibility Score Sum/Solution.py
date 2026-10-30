# 题目：1947. 最大兼容性评分和（Maximum Compatibility Score Sum）
# 思路：先预处理学生 i 与导师 j 的兼容分 g[i][j]，再用回溯枚举「学生 i 配哪个没用过的导师」，取最大总分。
# 时间复杂度：O(m!·m + m²n)，回溯最多枚举 m! 种配对；空间复杂度：O(m²)，兼容分矩阵与访问数组。
class Solution:  # LeetCode 约定的题解类
    # 解题入口：students 是学生答题向量，mentors 是导师答题向量
    def maxCompatibilitySum(
        self, students: List[List[int]], mentors: List[List[int]]
    ) -> int:
        def dfs(i: int, s: int):  # 回溯：给第 i 个学生配导师，s 是已累计得分
            if i >= m:  # 所有学生都配完了
                nonlocal ans  # 声明要修改外层函数里的 ans
                ans = max(ans, s)  # 用当前总分更新最优解
                return  # 递归出口
            for j in range(m):  # 尝试把导师 j 分给第 i 个学生
                if not vis[j]:  # 导师 j 还没被占用
                    vis[j] = True  # 占用导师 j
                    dfs(i + 1, s + g[i][j])  # 递归下一个学生，并累加这一对的兼容分
                    vis[j] = False  # 回溯，释放导师 j，恢复现场

        ans = 0  # 记录最大兼容性评分和
        m = len(students)  # 学生人数，题目保证与导师人数相同
        vis = [False] * m  # vis[j] 表示导师 j 是否已经被分配
        g = [[0] * m for _ in range(m)]  # g[i][j]：学生 i 与导师 j 的兼容分
        for i, x in enumerate(students):  # 遍历每个学生的答题向量 x
            for j, y in enumerate(mentors):  # 遍历每个导师的答题向量 y
                g[i][j] = sum(a == b for a, b in zip(x, y))  # 逐位比较，布尔值求和即相同位数
        dfs(0, 0)  # 从第 0 个学生、0 分开始回溯
        return ans  # 返回最大兼容性评分和
