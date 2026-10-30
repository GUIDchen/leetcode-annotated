# 题目：1202. 交换字符串中的元素（Smallest String With Swaps）
# 思路：并查集把能互相交换的下标合并成连通块，块内字符降序排序后按原顺序弹尾，得到字典序最小的串。
# 时间复杂度：O(n log n + m α(n))，块内排序主导；空间复杂度：O(n)，并查集与每块的字符列表。
class Solution:  # LeetCode 约定的题解类
    def smallestStringWithSwaps(self, s: str, pairs: List[List[int]]) -> str:  # s 是原字符串，pairs 是可交换的下标对，返回字典序最小的串
        def find(x: int) -> int:  # 并查集的查找函数：x 是下标，返回它所在集合的根
            if p[x] != x:  # 当前节点不是根，需继续往上找
                p[x] = find(p[x])  # 路径压缩：把 x 直接挂到根上
            return p[x]  # 返回根节点

        n = len(s)  # n 是字符串长度
        p = list(range(n))  # p[i] 初始化为 i，每个下标自成一个集合
        for a, b in pairs:  # 遍历所有可交换的下标对
            p[find(a)] = find(b)  # 合并两个下标：把 a 的根挂到 b 的根下面
        d = defaultdict(list)  # d 是「根下标 -> 该连通块内的字符列表」
        for i, c in enumerate(s):  # 按下标枚举字符
            d[find(i)].append(c)  # 把字符 c 归入下标 i 所属的连通块
        for i in d.keys():  # 遍历每个连通块（只改值不动键，遍历键视图是安全的）
            d[i].sort(reverse=True)  # 块内降序排序，之后从尾部 pop 就能取到最小字符
        return "".join(d[find(i)].pop() for i in range(n))  # 按原顺序回填：每个位置取下标的桶里当前最小的字符
