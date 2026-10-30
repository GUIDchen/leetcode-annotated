# 题目：1166. 设计文件系统（Design File System）
# 思路：用字典树按 '/' 切分路径逐段建树；创建时要求父路径已存在且自身不重复，查询时沿路径走到底返回末端节点的值。
# 时间复杂度：创建与查询均为 O(L)（L 为路径段数）；空间复杂度：O(S)，S 为所有已创建路径的字符总数。
class Trie:  # 字典树节点类：一个节点代表一层路径
    def __init__(self, v: int = -1):  # 构造：children 存子节点，v 存该路径的值（默认 -1）
        self.children = {}  # 子节点字典：路径段 → 子节点
        self.v = v  # 当前节点保存的值

    def insert(self, w: str, v: int) -> bool:  # 创建路径 w 并赋值为 v，成功返回 True
        node = self  # 从根节点出发
        ps = w.split("/")  # 按 "/" 切分，例如 "/a/b" → ["", "a", "b"]
        for p in ps[1:-1]:  # 只遍历父目录部分，跳过首段空串与最后一段
            if p not in node.children:  # 父目录不存在
                return False  # 父路径缺失，创建失败
            node = node.children[p]  # 沿路径下沉一层
        if ps[-1] in node.children:  # 目标路径已存在时不允许重复创建
            return False  # 重复创建，返回失败
        node.children[ps[-1]] = Trie(v)  # 新建叶子节点并挂到父节点上，同时保存值
        return True  # 创建成功

    def search(self, w: str) -> int:  # 查询路径 w 的值，不存在返回 -1
        node = self  # 从根节点出发
        for p in w.split("/")[1:]:  # 逐段向下查找，这里要走完所有段
            if p not in node.children:  # 某一段路径不存在
                return -1  # 路径不存在，返回 -1
            node = node.children[p]  # 继续下沉一层
        return node.v  # 走到末端节点，返回它保存的值


class FileSystem:  # 题目要求实现的文件系统类
    def __init__(self):  # 构造函数：初始化字典树的根节点
        self.trie = Trie()  # 根节点使用默认值 -1，代表根目录 "/"

    def createPath(self, path: str, value: int) -> bool:  # 创建新路径
        return self.trie.insert(path, value)  # 委托字典树完成插入

    def get(self, path: str) -> int:  # 查询路径的值
        return self.trie.search(path)  # 委托字典树完成查找


# Your FileSystem object will be instantiated and called as such:
# obj = FileSystem()
# param_1 = obj.createPath(path,value)
# param_2 = obj.get(path)
