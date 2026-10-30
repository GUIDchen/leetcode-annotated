# 题目：716. 最大栈（Max Stack）
# 核心思路：数据结构双写。双向链表当栈本体（节点对象稳定，便于被有序表引用），SortedList 以节点值为 key 保存同一批节点，于是 popMax 能 O(log n) 定位最大值并从两个结构中同步删除。
# 时间复杂度：push/pop/popMax 为 O(log n)，top/peekMax 为 O(1)；空间复杂度：O(n)，链表与有序表各存 n 个节点。
class Node:  # 双向链表节点，元素值就存在节点里，供栈与有序表共享同一个对象
    def __init__(self, val=0):  # val 默认取 0，让头尾哨兵节点的构造更简洁
        self.val = val  # 节点存放的元素值
        self.prev: Union[Node, None] = None  # 前驱指针，初始为空
        self.next: Union[Node, None] = None  # 后继指针，初始为空


class DoubleLinkedList:  # 带头尾哨兵的双向链表，用哨兵省去大量边界判断
    def __init__(self):  # 构造：创建头尾两个哨兵节点并把它们对接起来
        self.head = Node()  # 头哨兵，不存真实数据
        self.tail = Node()  # 尾哨兵，不存真实数据
        self.head.next = self.tail  # 空链表时头哨兵直接指向尾哨兵
        self.tail.prev = self.head  # 尾哨兵回指头哨兵，形成一对空的双向链接

    def append(self, val) -> Node:  # 在尾部追加新节点并返回它，方便外部持有该节点的引用
        node = Node(val)  # 创建新节点
        node.next = self.tail  # 新节点的后继是尾哨兵
        node.prev = self.tail.prev  # 新节点的前驱是原来的最后一个真实节点
        self.tail.prev = node  # 尾哨兵的前驱改为新节点
        node.prev.next = node  # 原最后一个节点的后继改为新节点，插入完成
        return node  # 返回新节点，供有序表登记

    @staticmethod  # 静态方法：只操作传入的节点，不需要访问 self
    def remove(node) -> Node:  # 把节点从链表中摘除（不释放节点对象，调用方可能还要读它的值）
        node.prev.next = node.next  # 让前驱直接跳过当前节点
        node.next.prev = node.prev  # 让后继直接指回前驱
        return node  # 返回被摘除的节点，便于继续读取它的值

    def pop(self) -> Node:  # 弹出尾部节点，即栈顶
        return self.remove(self.tail.prev)  # 尾哨兵的前驱就是最后一个真实节点

    def peek(self):  # 读取尾部节点的值但不出栈
        return self.tail.prev.val  # 尾哨兵的前驱就是栈顶节点


class MaxStack:  # 最大栈：栈本体用双向链表，另用有序表按值快速定位最大值
    def __init__(self):  # 构造：初始化链表栈与按值排序的节点集合
        self.stk = DoubleLinkedList()  # 链表本体，push/pop 都在尾部进行
        self.sl = SortedList(key=lambda x: x.val)  # 有序表以节点值作为排序 key，支持 O(log n) 插入、删除与取最大

    def push(self, x: int) -> None:  # 入栈
        node = self.stk.append(x)  # 把值追加到链表尾部，并拿到这个新节点的引用
        self.sl.add(node)  # 把同一个节点登记到有序表中，两处共享同一节点对象

    def pop(self) -> int:  # 弹出栈顶元素
        node = self.stk.pop()  # 从链表尾部摘除栈顶节点
        self.sl.remove(node)  # 同步从有序表中删除该节点，保持两个结构一致
        return node.val  # 返回被弹出元素的值

    def top(self) -> int:  # 读取栈顶值但不出栈
        return self.stk.peek()  # 直接读链表尾节点的值

    def peekMax(self) -> int:  # 读取当前最大值但不出栈
        return self.sl[-1].val  # 有序表按值升序，最后一个元素的 val 就是当前最大值

    def popMax(self) -> int:  # 弹出当前最大值（存在多个相同最大值时，取有序表末尾的那一个）
        node = self.sl.pop()  # 从有序表中取出并移除值最大的节点
        DoubleLinkedList.remove(node)  # 再把该节点从链表中摘除，两个结构保持同步
        return node.val  # 返回被弹出的最大值


# Your MaxStack object will be instantiated and called as such:
# obj = MaxStack()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.top()
# param_4 = obj.peekMax()
# param_5 = obj.popMax()
