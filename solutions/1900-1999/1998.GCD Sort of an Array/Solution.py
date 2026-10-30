# 题目：1998. 数组的最大公因数排序（GCD Sort of an Array）
# 思路：把「数值 - 其质因数」用并查集连通，再与升序数组逐位比较：位置不同却不在同一连通块则无法排序。
# 时间复杂度：O(M log log M + n α(M))，M 为最大值；空间复杂度：O(M)，并查集与质因数表。
class Solution:  # LeetCode 约定的题解类
    def gcdSort(self, nums: List[int]) -> bool:  # nums：待判断能否通过 GCD 交换完成排序的数组
        n = 10**5 + 10  # 并查集容量，覆盖题目数值上界 1e5 并留出余量
        p = list(range(n))  # 并查集父数组，初始化时每个数值自成一个连通块
        f = defaultdict(list)  # f[v] 保存数值 v 的所有不同质因数，缺省为空列表
        mx = max(nums)  # 数组中的最大数值，用于限制筛法上界
        for i in range(2, mx + 1):  # 埃氏筛的变体：i 从小到大枚举
            if f[i]:
                continue  # i 已有质因数说明是合数，跳过
            for j in range(i, mx + 1, i):
                f[j].append(i)  # i 是质数，把所有倍数 j 的质因数表里加入 i

        def find(x):  # 并查集查找，带路径压缩
            if p[x] != x:
                p[x] = find(p[x])  # 递归找到代表元，并把当前节点直接挂到代表元上
            return p[x]  # 返回所在连通块的代表元

        for i in nums:  # 遍历原数组中的每个数值
            for j in f[i]:
                p[find(i)] = find(j)  # 数值与其每个质因数合并到同一连通块（可通过 GCD 交换）

        s = sorted(nums)  # 得到目标升序数组
        for i, num in enumerate(nums):  # 逐位比较原数组与升序数组
            if s[i] != num and find(num) != find(s[i]):
                return False  # 该位置需要换数但两数不连通，说明无法完成排序
        return True  # 所有位置都满足条件，可以完成排序
