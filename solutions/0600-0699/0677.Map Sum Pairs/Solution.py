# 题目：677. 键值映射（Map Sum Pairs）
# 思路：前缀树每个节点维护「经过它的所有键的值之和」，插入时只把新旧值之差累加到路径上；查询前缀时直接返回该前缀末尾节点的累计值。
# 时间复杂度：插入与查询均为 O(L)，L 为键长；空间复杂度：O(总字符数 * 26)，前缀树节点开销。
class Trie:  # 前缀树节点，val 记录经过此处的所有键值之和
    def __init__(self):  # 构造节点
        self.children: List[Trie | None] = [None] * 26  # 26 个孩子指针，下标是字符相对 'a' 的偏移
        self.val: int = 0  # 经过当前节点的所有键的值之和

    def insert(self, w: str, x: int):  # 把差值 x 累加到路径 w 上的每个节点
        node = self  # 从根节点开始
        for c in w:  # 逐字符向下
            idx = ord(c) - ord('a')  # 计算字符对应的孩子下标
            if node.children[idx] is None:  # 该分支还不存在
                node.children[idx] = Trie()  # 新建节点补上
            node = node.children[idx]  # 走到对应的孩子节点
            node.val += x  # 把差值累加到该节点代表的前缀和上

    def search(self, w: str) -> int:  # 查询以 w 为前缀的所有键的值之和
        node = self  # 从根节点开始
        for c in w:  # 沿前缀逐字符向下
            idx = ord(c) - ord('a')  # 计算字符对应的孩子下标
            if node.children[idx] is None:  # 前缀分支不存在
                return 0  # 说明没有任何键以此为前缀
            node = node.children[idx]  # 走到对应的孩子节点
        return node.val  # 该节点累计的就是答案


class MapSum:  # 题目要求的键值映射类
    def __init__(self):  # 构造对象
        self.d = defaultdict(int)  # 记录每个键当前的值，缺省为 0，便于计算覆盖时的增量
        self.tree = Trie()  # 前缀树根节点，维护前缀和

    def insert(self, key: str, val: int) -> None:  # 插入或覆盖一个键值对
        x = val - self.d[key]  # 只需把「新值 - 旧值」的增量写进树里
        self.d[key] = val  # 更新该键的最新值
        self.tree.insert(key, x)  # 把增量累加到前缀树的对应路径上

    def sum(self, prefix: str) -> int:  # 求所有以 prefix 为前缀的键的当前值之和
        return self.tree.search(prefix)  # 前缀树末尾节点累计的就是答案


# Your MapSum object will be instantiated and called as such:
# obj = MapSum()
# obj.insert(key,val)
# param_2 = obj.sum(prefix)
