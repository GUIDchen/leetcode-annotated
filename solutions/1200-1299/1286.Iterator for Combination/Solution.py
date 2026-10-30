# 题目：1286. 字母组合迭代器（Iterator for Combination）
# 思路：构造时用 DFS 按字典序枚举所有长度为 combinationLength 的下标组合并缓存，next 与 hasNext 只做列表下标访问。
# 时间复杂度：构造 O(C(n,k)·k)，每个组合要拼接 k 个字符；next/hasNext 为 O(1)；空间复杂度：O(C(n,k)·k)，缓存全部组合。
class CombinationIterator:  # 字母组合迭代器：按字典序逐个产出定长组合
    def __init__(self, characters: str, combinationLength: int):  # 构造函数：characters 为字符集，combinationLength 为组合长度
        def dfs(i):  # 内部 DFS：i 是下一个可选的字符下标
            if len(t) == combinationLength:  # 已选够 k 个字符，得到一个完整组合
                cs.append(''.join(t))  # 把字符列表拼成字符串并加入缓存
                return  # 递归出口：不再继续向下选择
            if i == n:  # 可用下标用尽
                return  # 剪枝返回，不再继续向下选择
            t.append(characters[i])  # 分支一：选择第 i 个字符
            dfs(i + 1)  # 继续从 i + 1 开始选后面的字符
            t.pop()  # 回溯：撤销刚才的选择，恢复状态
            dfs(i + 1)  # 分支二：不选第 i 个字符，直接从 i + 1 继续

        cs = []  # 缓存所有组合的列表
        n = len(characters)  # 原字符串长度，供 DFS 判断边界
        t = []  # DFS 过程中「正在进行中的组合」
        dfs(0)  # 从下标 0 开始 DFS，预先生成全部组合
        self.cs = cs  # 把结果缓存挂到实例上，供 next 使用
        self.idx = 0  # 当前 next 应返回的组合下标

    def next(self) -> str:  # 返回下一个组合，并让内部下标前移
        ans = self.cs[self.idx]  # 先取出当前组合
        self.idx += 1  # 下标自增 1，下次返回下一个组合
        return ans  # 返回取到的组合字符串

    def hasNext(self) -> bool:  # 是否还有未返回的组合
        return self.idx < len(self.cs)  # 下标尚未越界就说明还有组合


# Your CombinationIterator object will be instantiated and called as such:  # 以下为 LeetCode 提供的调用示例注释（原样保留）
# obj = CombinationIterator(characters, combinationLength)
# param_1 = obj.next()
# param_2 = obj.hasNext()
