# 题目：460. LFU 缓存（LFU Cache）
# 思路：键表 self.map 存「键→节点」，频次表 self.freq_map 存「频次→双向链表」；命中后把节点搬到频次+1 链表头部，满容量时从 min_freq 链表尾部淘汰，并同步维护最小频次。
# 时间复杂度：get 与 put 均摊 O(1)（哈希表 + 双向链表）；空间复杂度：O(capacity)，节点与两张哈希表都与容量同阶。
class Node:  # 双向链表节点：保存键、值、访问频次与前驱后继引用
    def __init__(self, key: int, value: int) -> None:  # 构造函数：新节点的频次初始为 1
        self.key = key  # 缓存键
        self.value = value  # 缓存值
        self.freq = 1  # 访问频次
        self.prev = None  # 前驱节点
        self.next = None  # 后继节点


class DoublyLinkedList:  # 双向链表：同一频次的键放在同一条链表，头部是最近访问的
    def __init__(self) -> None:  # 构造：建立头尾哨兵并连成空链表
        self.head = Node(-1, -1)  # 头哨兵，不存真实数据，省去边界判断
        self.tail = Node(-1, -1)  # 尾哨兵，不存真实数据
        self.head.next = self.tail  # head 的后继指向 tail
        self.tail.prev = self.head  # tail 的前驱指向 head

    def add_first(self, node: Node) -> None:  # 把节点插入链表头部（表示该频次下最近被访问）
        node.prev = self.head  # 新节点的前驱是 head
        node.next = self.head.next  # 新节点的后继是原来的第一个真实节点
        self.head.next.prev = node  # 原第一个节点的前驱改为新节点
        self.head.next = node  # head 的后继指向新节点

    def remove(self, node: Node) -> Node:  # 从链表中摘除指定节点并返回它
        node.next.prev = node.prev  # 后继节点绕过当前节点
        node.prev.next = node.next  # 前驱节点绕过当前节点
        node.next, node.prev = None, None  # 断开自身前后引用，避免悬挂引用
        return node  # 返回被摘除的节点

    def remove_last(self) -> Node:  # 删除并返回链表尾部节点（该频次下最久未使用的键）
        return self.remove(self.tail.prev)  # tail 的前驱就是最后一个真实节点

    def is_empty(self) -> bool:  # 判断链表是否为空（只剩两个哨兵）
        return self.head.next == self.tail  # head 直接指向 tail 说明没有真实节点


class LFUCache:  # LFU 缓存：按频次淘汰，频次相同则淘汰最久未使用的
    def __init__(self, capacity: int):  # 构造函数：记录容量并初始化最小频次
        self.capacity = capacity  # 保存缓存容量
        self.min_freq = 0  # 当前最小频次，用于 O(1) 定位要淘汰的链表
        self.map = defaultdict(Node)  # 键 -> 节点 的哈希表（defaultdict 保证取缺失键时自动建节点）
        self.freq_map = defaultdict(DoublyLinkedList)  # 频次 -> 双向链表 的哈希表（取缺失频次时自动建空链表）

    def get(self, key: int) -> int:  # 读取键对应的值，不存在返回 -1
        if self.capacity == 0 or key not in self.map:  # 容量为 0 或键不存在
            return -1  # 未命中，返回 -1
        node = self.map[key]  # 取出对应节点
        self.incr_freq(node)  # 命中后频次加一并移动到新频次链表
        return node.value  # 返回节点值

    def put(self, key: int, value: int) -> None:  # 写入键值对
        if self.capacity == 0:  # 容量为 0 时无法缓存任何内容
            return  # 直接返回
        if key in self.map:  # 键已存在：更新值并提升频次
            node = self.map[key]  # 取出已有节点
            node.value = value  # 覆盖旧值
            self.incr_freq(node)  # 提升频次
            return  # 更新完成
        if len(self.map) == self.capacity:  # 缓存已满，需要先淘汰一个元素
            ls = self.freq_map[self.min_freq]  # 最小频次链表：其尾部是该频次下最久未使用的节点
            node = ls.remove_last()  # 摘除链表尾部节点（即被淘汰的节点）
            self.map.pop(node.key)  # 同时从键表中删除该键
        node = Node(key, value)  # 为新键创建节点（频次初始为 1）
        self.add_node(node)  # 加入频次 1 对应的链表
        self.map[key] = node  # 记录键到节点的映射
        self.min_freq = 1  # 新插入的键频次最小，最小频次重置为 1

    def incr_freq(self, node: Node) -> None:  # 把节点的频次加一，并按新频次重新挂到对应链表
        freq = node.freq  # 记录旧频次
        ls = self.freq_map[freq]  # 取出旧频次对应的链表
        ls.remove(node)  # 先从旧链表中摘除该节点
        if ls.is_empty():  # 旧频次链表已空
            self.freq_map.pop(freq)  # 删除这个频次的映射，避免留下空链表
            if freq == self.min_freq:  # 空的正是最小频次链表时
                self.min_freq += 1  # 最小频次整体加一
        node.freq += 1  # 节点频次加一
        self.add_node(node)  # 按新频次头插到对应链表

    def add_node(self, node: Node) -> None:  # 把节点插入它当前频次对应链表的头部
        freq = node.freq  # 读取节点当前频次
        ls = self.freq_map[freq]  # 取出该频次对应的链表（缺失时自动创建）
        ls.add_first(node)  # 头插，表示该频次下最近被访问
        self.freq_map[freq] = ls  # 回写映射，确保该频次存在对应链表


# 下面是 LeetCode 给出的使用示例（原题注释，保留原样）
# Your LFUCache object will be instantiated and called as such:
# obj = LFUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
