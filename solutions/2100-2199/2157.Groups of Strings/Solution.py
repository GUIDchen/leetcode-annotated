# 题目：2157. 字符串分组（Groups of Strings）
# 核心思路：把每个单词压成 26 位掩码，用并查集把「只差一次字母增/删/换」的掩码合并成组，实时维护组数与最大组大小。
# 时间复杂度：O(N·26²·α)，N 为单词数；空间复杂度：O(N)，并查集与组大小的字典各存至多 N 个键。
class Solution:  # LeetCode 约定的题解类
    def groupStrings(self, words: List[str]) -> List[int]:  # words：输入单词数组；返回 [组数, 最大组大小]
        def find(x):  # 带路径压缩的并查集查找
            if p[x] != x:  # 还不是代表元就继续往上找
                p[x] = find(p[x])  # 递归找到根后，把当前点直接挂到根上（路径压缩）
            return p[x]  # 返回代表元

        def union(a, b):  # 合并 a、b 两个掩码所在的组
            nonlocal mx, n  # 声明下面要修改外层函数的 mx 与 n，而不是新建局部变量
            if b not in p:  # b 这个掩码没出现过，无法合并
                return  # 直接返回
            pa, pb = find(a), find(b)  # 分别取出两个集合的代表元
            if pa == pb:  # 代表元相同说明已经在同一组
                return  # 无需合并
            p[pa] = pb  # 把 a 的根挂到 b 的根下面
            size[pb] += size[pa]  # 组大小累加到新的根上
            mx = max(mx, size[pb])  # 合并可能产生更大的组，更新最大组大小
            n -= 1  # 两个组合并成一个，组数减一

        p = {}  # 并查集：键是掩码，值是父掩码（指向代表元）
        size = Counter()  # 每个代表元所在组的大小
        n = len(words)  # 组数先按单词个数计，之后每合并一次就减一
        mx = 0  # 最大组大小从 0 开始维护
        for word in words:  # 逐个单词建立掩码
            x = 0  # 该单词的 26 位掩码，第 k 位表示字母 k 是否出现
            for c in word:  # 遍历单词中的每个字符
                x |= 1 << (ord(c) - ord('a'))  # 字母映射到一位，重复字母只会重复置同一位
            p[x] = x  # 初始化并查集：掩码自己就是代表元
            size[x] += 1  # 相同掩码的单词属于同一组，组大小加一
            mx = max(mx, size[x])  # 用当前组的大小更新最大组大小
            if size[x] > 1:  # 该掩码之前已经出现过
                n -= 1  # 两个单词天然同组，组数减一
        for x in p.keys():  # 只遍历建表时存在的掩码；循环里只改 value 不新增 key，可安全遍历
            for i in range(26):  # 枚举要作用到的第 i 个字母
                union(x, x ^ (1 << i))  # 删掉字母 i；若原本没有 i，则等价于给单词加上字母 i
                if (x >> i) & 1:  # 只有字母 i 存在时才谈得上「换成别的字母」
                    for j in range(26):  # 枚举替换目标字母 j
                        if ((x >> j) & 1) == 0:  # 目标字母必须原本不存在
                            union(x, x ^ (1 << i) | (1 << j))  # 先异或清掉 i，再置上 j，得到替换后的掩码
        return [n, mx]  # 返回 [剩余组数, 最大组大小]
