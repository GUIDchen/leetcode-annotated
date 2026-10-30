# 题目：146. LRU 缓存（LRU Cache）
# 思路：字典 key→节点 实现 O(1) 定位，双向链表维护访问顺序，头热尾冷，超容量时淘汰尾节点。
# 时间复杂度：get 与 put 均为 O(1)；空间复杂度：O(capacity)，字典与链表各存一份节点。
class Node:  # 双向链表节点：保存 key、val 以及前后指针
    def __init__(self, key: int = 0, val: int = 0):  # 构造函数给默认值，方便创建不存数据的哨兵节点
        self.key = key  # 记录 key，淘汰时要靠它从字典里删除
        self.val = val  # 记录缓存值
        self.prev = None  # 前驱指针，插入链表时再设置
        self.next = None  # 后继指针，插入链表时再设置


class LRUCache:  # 题目要求的缓存类
    def __init__(self, capacity: int):  # 初始化容量、字典与带头尾哨兵的双向链表
        self.size = 0  # 当前缓存元素个数
        self.capacity = capacity  # 容量上限
        self.cache = {}  # 字典：key → 节点，保证 get/put 平均 O(1)
        self.head = Node()  # 哨兵头：head.next 是最近使用的节点
        self.tail = Node()  # 哨兵尾：tail.prev 是最久未使用的节点
        self.head.next = self.tail  # 空链表：头指向尾
        self.tail.prev = self.head  # 尾再指回头，双向链表打通

    def get(self, key: int) -> int:  # 查询 key：命中返回值，否则返回 -1
        if key not in self.cache:  # 字典里没有这个 key
            return -1  # 未命中，按题目约定返回 -1
        node = self.cache[key]  # 取出对应节点
        self.remove_node(node)  # 先从链表中摘下
        self.add_to_head(node)  # 再插到头部，表示刚刚使用过
        return node.val  # 返回缓存值

    def put(self, key: int, value: int) -> None:  # 写入缓存：已存在就更新并刷新热度，超容量则淘汰尾部
        if key in self.cache:  # key 已存在：只更新值并移到头部
            node = self.cache[key]  # 取出已有节点
            self.remove_node(node)  # 先摘下
            node.val = value  # 覆盖旧值
            self.add_to_head(node)  # 插回头部，刷新使用权
        else:  # key 不存在：新建节点
            node = Node(key, value)  # 创建新节点
            self.cache[key] = node  # 字典登记这个 key
            self.add_to_head(node)  # 插入头部，表示最新使用
            self.size += 1  # 元素个数加一
            if self.size > self.capacity:  # 超出容量，需要淘汰最久未使用的节点
                node = self.tail.prev  # 尾部前一个节点就是最久未使用
                self.cache.pop(node.key)  # 字典中删除该 key
                self.remove_node(node)  # 链表中摘下该节点
                self.size -= 1  # 个数减一

    def remove_node(self, node):  # 从双向链表中摘除节点
        node.prev.next = node.next  # 前驱直接指向后继
        node.next.prev = node.prev  # 后继直接指向前驱

    def add_to_head(self, node):  # 把节点插到哨兵头之后（最热端）
        node.next = self.head.next  # 新节点接到原第一个节点之前
        node.prev = self.head  # 新节点的前驱是哨兵头
        self.head.next = node  # 哨兵头指向新节点
        node.next.prev = node  # 原第一个节点的前驱改为新节点，四步指针修改完成


# ↓ 下面是 LeetCode 生成的调用示例注释，按原样保留
# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
