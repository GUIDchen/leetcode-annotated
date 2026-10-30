# 题目：1206. 设计跳表（Design Skiplist）
# 思路：用多层有序链表实现跳表，每个结点按 1/4 概率逐层晋升；查询、插入、删除都从当前最高层往下，每层先找到「最右的小于目标」的结点再下降。
# 时间复杂度：平均 O(log n)，最坏 O(n)；空间复杂度：O(n)，每个结点期望层数为常数（约 1/(1-p) 层）。
class Node:  # 跳表结点：值 + 各层的后继指针列表
    __slots__ = ['val', 'next']  # 用 __slots__ 固定属性名，省去 __dict__ 以减少内存占用

    def __init__(self, val: int, level: int):  # 构造函数：值 val，占据 level 层
        self.val = val  # 保存结点数值，头结点用 -1 作哨兵
        self.next = [None] * level  # 长度等于层数的后继列表，先全部置为 None


class Skiplist:  # 跳表主体：封装插入、删除、查询
    max_level = 32  # 最大层数，32 层足够覆盖 4^32 量级的数据，避免无限增高
    p = 0.25  # 晋升概率：每层以 1/4 的概率继续向上生长

    def __init__(self):  # 构造函数：初始化空跳表
        self.head = Node(-1, self.max_level)  # 建立占满所有层的哨兵头结点，方便每层统一从 head 出发
        self.level = 0  # 空表没有任何数据层，当前最高层数记为 0

    def search(self, target: int) -> bool:  # 查询 target 是否存在
        curr = self.head  # 从哨兵头结点开始，自顶向下逐层查找
        for i in range(self.level - 1, -1, -1):  # 从当前最高层往下遍历到第 0 层
            curr = self.find_closest(curr, i, target)  # 在第 i 层找到最后一个小于 target 的结点，逐层缩小范围
            if curr.next[i] and curr.next[i].val == target:  # 第 i 层的下一个结点就是 target，说明存在
                return True  # 命中，立即返回真
        return False  # 所有层都没命中，说明 target 不存在

    def add(self, num: int) -> None:  # 插入 num，若已存在则再插入一份（跳表允许重复值）
        curr = self.head  # 从哨兵头结点出发，逐层寻找插入位置的前驱
        level = self.random_level()  # 随机决定新结点占据的层数
        node = Node(num, level)  # 创建新结点，其指针列表长度恰为该层数
        self.level = max(self.level, level)  # 若新结点层数更高，则提升整张表的当前最高层数
        for i in range(self.level - 1, -1, -1):  # 从最高层往第 0 层下降，边下降边挂接指针
            curr = self.find_closest(curr, i, num)  # 在第 i 层找到插入位置的前一个结点
            if i < level:  # 只有低于新结点层数的层才需要真正插入指针
                node.next[i] = curr.next[i]  # 新结点接管前驱原本的后继
                curr.next[i] = node  # 前驱改为指向新结点，完成第 i 层的链表插入

    def erase(self, num: int) -> bool:  # 删除一个值为 num 的结点，返回是否真的删到了
        curr = self.head  # 从哨兵头结点出发，逐层寻找待删结点的前驱
        ok = False  # 标记是否至少在一层删到了该值
        for i in range(self.level - 1, -1, -1):  # 自顶向下逐层处理，保证每层的指针都被摘下
            curr = self.find_closest(curr, i, num)  # 在第 i 层找到待删结点之前的结点
            if curr.next[i] and curr.next[i].val == num:  # 第 i 层的下一个结点正是待删结点
                curr.next[i] = curr.next[i].next[i]  # 前驱跨过待删结点，把它从第 i 层链表摘除
                ok = True  # 记录本次删除成功
        while self.level > 1 and self.head.next[self.level - 1] is None:  # 若最高层已经没有数据结点，就收缩表的层数，避免无效的顶层遍历
            self.level -= 1  # 把当前最高层数降一层，再继续检查新的顶层
        return ok  # 返回是否删到过该值

    def find_closest(self, curr: Node, level: int, target: int) -> Node:  # 在第 level 层从 curr 出发，找到最后一个值小于 target 的结点
        while curr.next[level] and curr.next[level].val < target:  # 只要下一个结点仍小于 target 就继续右移
            curr = curr.next[level]  # 沿第 level 层向右跳到下一个结点
        return curr  # 返回这一层上最靠右的「小于 target」的结点

    def random_level(self) -> int:  # 随机生成新结点的层数
        level = 1  # 层数至少为 1，保证每个结点一定出现在第 0 层
        while level < self.max_level and random.random() < self.p:  # 每层以 1/4 的概率继续晋升，直到随机失败或触顶
            level += 1  # 晋升一层
        return level  # 返回最终层数


# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
