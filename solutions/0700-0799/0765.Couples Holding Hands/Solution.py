# 题目：765. 情侣牵手（Couples Holding Hands）
# 思路：把每对情侣看作一个并查集结点，坐同一张双人座的两人所属情侣对合并；含 k 对的连通块需要 k-1 次交换，答案为 对数减去连通分量数。
# 时间复杂度：O(n α(n))，并查集近似线性；空间复杂度：O(n)，父数组。
class Solution:  # LeetCode 约定的题解类
    def minSwapsCouples(self, row: List[int]) -> int:  # row：座位表，元素是每个人编号
        def find(x: int) -> int:  # 并查集查找函数（带路径压缩）
            if p[x] != x:  # 当前结点不是根
                p[x] = find(p[x])  # 递归找到根并顺带压缩路径
            return p[x]  # 返回根结点

        n = len(row) >> 1  # 右移一位即除以 2，得到情侣对数，也是并查集大小
        p = list(range(n))  # 初始时每对情侣各自构成一个集合
        for i in range(0, len(row), 2):  # 每两个人一组遍历座位
            a, b = row[i] >> 1, row[i + 1] >> 1  # 各自的编号右移一位即所属情侣对编号
            p[find(a)] = find(b)  # 合并这两个情侣对所在的集合
        return n - sum(i == find(i) for i in range(n))  # 对数减去根结点个数（连通分量数）即最少交换次数
