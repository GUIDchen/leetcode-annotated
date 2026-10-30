# 题目：3327. 判断 DFS 字符串是否是回文串（Check if DFS Strings Are Palindromes）
# 思路：先 DFS 建出整棵树的 dfsStr 并记下每个子树的区间；再用正序、逆序两套前缀哈希，在 O(1) 内比较区间前后两半是否相同。
# 时间复杂度：O(n)，建串与每个子树的判定都是常数次哈希查询；空间复杂度：O(n)，邻接表、dfsStr、pos 与两张哈希表都是线性。
class Hashing:  # 字符串哈希小工具：预处理前缀哈希与幂次
    __slots__ = ["mod", "h", "p"]  # 固定属性名，省一点内存也防止写错属性

    def __init__(self, s: List[str], base: int, mod: int):  # s 是待哈希的串，base 是进制，mod 是模数
        self.mod = mod  # 保存模数，query 里要用
        self.h = [0] * (len(s) + 1)  # h[i] 为前 i 个字符的哈希，多开一位给空前缀
        self.p = [1] * (len(s) + 1)  # p[i] = base^i，全部先置 1，p[0] 正好是 1
        for i in range(1, len(s) + 1):  # 从第 1 位递推到第 n 位
            self.h[i] = (self.h[i - 1] * base + ord(s[i - 1])) % mod  # 前缀哈希递推：整体左移一位再加上新字符的编码
            self.p[i] = (self.p[i - 1] * base) % mod  # 幂次递推

    def query(self, l: int, r: int) -> int:  # 查闭区间 [l, r] 的哈希，下标从 1 开始
        return (self.h[r] - self.h[l - 1] * self.p[r - l + 1]) % self.mod  # 先乘幂次对齐再相减；Python 取模会自动得到非负数


class Solution:  # LeetCode 约定的题解类
    def findAnswer(self, parent: List[int], s: str) -> List[bool]:  # parent 是父节点数组（根为 0），s 是每个节点上的字符
        def dfs(i: int):  # 递归求出子树 i 的 DFS 串，并记录它的区间
            l = len(dfsStr) + 1  # 区间左端：当前串长的下一个位置
            for j in g[i]:  # 先按顺序处理所有孩子
                dfs(j)  # 孩子的字符先写进 dfsStr
            dfsStr.append(s[i])  # 再补自己的字符，形成后序序列
            r = len(dfsStr)  # 追加后的串长就是区间右端
            pos[i] = (l, r)  # 记下子树 i 对应的连续区间

        n = len(s)  # 节点个数
        g = [[] for _ in range(n)]  # 邻接表：g[u] 存 u 的所有孩子
        for i in range(1, n):  # 除根以外逐个挂到父节点下
            g[parent[i]].append(i)  # 建立父子边，孩子顺序与输入一致
        dfsStr = []  # 整棵树的 DFS 字符串，先收集成列表
        pos = {}  # 节点到子树区间的映射
        dfs(0)  # 从根开始遍历

        base, mod = 13331, 998244353  # 常用的哈希进制与模数
        h1 = Hashing(dfsStr, base, mod)  # 正序串哈希，用于区间前半段
        h2 = Hashing(dfsStr[::-1], base, mod)  # 逆序串哈希，用于区间后半段的反向
        ans = []  # 按节点顺序收集答案
        for i in range(n):  # 逐个节点判断
            l, r = pos[i]  # 取出该子树的区间
            k = r - l + 1  # 区间长度
            v1 = h1.query(l, l + k // 2 - 1)  # 前半段的哈希
            v2 = h2.query(n - r + 1, n - r + 1 + k // 2 - 1)  # 后半段反向的哈希，下标换算到逆序串上
            ans.append(v1 == v2)  # 相等即回文；奇数长度跳过中间字符
        return ans  # 返回每个节点的判定结果
