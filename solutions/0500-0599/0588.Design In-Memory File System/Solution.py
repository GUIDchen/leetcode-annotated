# 题目：588. 设计内存文件系统（Design In-Memory File System）
# 思路：用 Trie（字典树）表示目录树，路径按 '/' 切分后逐层插入或查找；节点用 isFile 区分文件与目录，文件内容用列表累加。
# 时间复杂度：单次操作 O(L)，L 为路径长度（ls 目录还需 O(k log k) 排序）；空间复杂度：O(所有路径字符总数)。
class Trie:  # 字典树节点，既可表示目录也可表示文件
    def __init__(self):  # 初始化一个节点
        self.name = None  # 节点名，只有文件节点才会被赋值为文件名
        self.isFile = False  # 默认是目录
        self.content = []  # 文件内容可能分多次写入，按顺序保存
        self.children = {}  # 子节点表：名字 → 子节点

    def insert(self, path, isFile):  # 按路径逐层创建节点，返回最末端的节点
        node = self  # 从根节点出发
        ps = path.split('/')  # 以 '/' 切分路径
        for p in ps[1:]:  # 忽略第 0 段（绝对路径开头切出来的空字符串）
            if p not in node.children:  # 该层还没有同名子节点
                node.children[p] = Trie()  # 就新建一个
            node = node.children[p]  # 下移一层
        node.isFile = isFile  # 标记末端是文件还是目录
        if isFile:  # 只有文件才需要记名字，供 ls 直接返回
            node.name = ps[-1]  # 路径最后一段就是文件名
        return node  # 返回末端节点，调用方还要继续写入内容

    def search(self, path):  # 按路径查找节点，找不到返回 None
        node = self  # 从根节点出发
        if path == '/':  # 根目录直接命中
            return node  # 返回根节点
        ps = path.split('/')  # 同样切分路径
        for p in ps[1:]:  # 逐段向下走
            if p not in node.children:  # 某一段不存在
                return None  # 说明路径无效
            node = node.children[p]  # 下移一层
        return node  # 返回命中的节点


class FileSystem:  # 内存文件系统，内部用一棵 Trie 表示整棵目录树
    def __init__(self):  # 构造函数
        self.root = Trie()  # 建立根节点，代表 "/"

    def ls(self, path: str) -> List[str]:  # 列出目录下的名字；如果路径指向文件则返回文件名
        node = self.root.search(path)  # 先找到路径对应的节点
        if node is None:  # 路径不存在
            return []  # 返回空列表
        if node.isFile:  # 是文件时，ls 返回文件名本身
            return [node.name]  # 用列表包一层返回
        return sorted(node.children.keys())  # 是目录时，按字典序返回所有子项名字

    def mkdir(self, path: str) -> None:  # 新建目录（沿途的父目录会被一并创建）
        self.root.insert(path, False)  # 插入路径并标记为目录

    def addContentToFile(self, filePath: str, content: str) -> None:  # 向文件追加内容，文件不存在则创建
        node = self.root.insert(filePath, True)  # 沿途建好节点并标记为文件
        node.content.append(content)  # 追加这次写入的内容片段

    def readContentFromFile(self, filePath: str) -> str:  # 读取文件的全部内容
        node = self.root.search(filePath)  # 找到文件节点
        return ''.join(node.content)  # 把多次追加的片段拼接成一个字符串


# Your FileSystem object will be instantiated and called as such:  # 判题器会按下面的方式调用这个类
# obj = FileSystem()  # 创建对象
# param_1 = obj.ls(path)  # 调用 ls 列出目录
# obj.mkdir(path)  # 调用 mkdir 建目录
# obj.addContentToFile(filePath,content)  # 调用 addContentToFile 写内容
# param_4 = obj.readContentFromFile(filePath)  # 调用 readContentFromFile 读内容
