# 题目：1105. 填充书架（Filling Bookcase Shelves）
# 思路：动态规划，f[i] 表示前 i 本书的最小总高度；倒序把书并入最后一层，在宽度允许的范围内用层内最高书更新答案。
# 时间复杂度：O(n^2)，内外层合计最多 n(n+1)/2 次；空间复杂度：O(n)，f 列表保存 n+1 个状态。
class Solution:  # LeetCode 约定的题解类
    def minHeightShelves(self, books: List[List[int]], shelfWidth: int) -> int:  # books 每项是 {厚度, 高度}，shelfWidth 是书架宽度上限
        n = len(books)  # 书本总数
        f = [0] * (n + 1)  # f[i]：前 i 本书摆放后的最小总高度，f[0] 天然为 0
        for i, (w, h) in enumerate(books, 1):  # i 从 1 开始编号，同时解包出第 i 本书的厚度 w 与高度 h
            f[i] = f[i - 1] + h  # 初始方案：第 i 本书单独新起一层，直接加上它的高度
            for j in range(i - 1, 0, -1):  # 倒序枚举最后一层的起始书 j，把第 j 本也并入最后一层
                w += books[j - 1][0]  # 把第 j 本书的厚度累加进当前层宽
                if w > shelfWidth:  # 层宽超出书架宽度，继续往前只会更宽
                    break  # 宽度单调递增，提前结束内层循环
                h = max(h, books[j - 1][1])  # 同一层的高度取层内最高的那一本
                f[i] = min(f[i], f[j - 1] + h)  # 用「前 j-1 本的最优高度 + 当前层高度」更新 f[i]
        return f[n]  # 前 n 本书的最小总高度就是答案
