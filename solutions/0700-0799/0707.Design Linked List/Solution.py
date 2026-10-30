# 题目：707. 设计链表（Design Linked List）
# 思路：带虚拟头结点（dummy）的单链表，另存长度 cnt；按下标操作时先从 dummy 走到目标的前驱，再改指针。
# 时间复杂度：get / addAtIndex / deleteAtIndex 为 O(index)，addAtHead 为 O(1)；空间复杂度：O(n)，n 为链表长度。
class MyLinkedList:  # 自定义单链表类
    def __init__(self):  # 构造函数：创建虚拟头结点并清零元素计数
        self.dummy = ListNode()  # 虚拟头结点，dummy.next 才是真正的首结点，可统一边界处理
        self.cnt = 0  # 记录元素个数，用于越界判断与尾插定位

    def get(self, index: int) -> int:  # get：返回下标 index 处的值，越界返回 -1
        if index < 0 or index >= self.cnt:  # 下标为负或不小于长度，说明该位置没有结点
            return -1  # 越界时按题目要求返回 -1
        cur = self.dummy.next  # 从真正的首结点开始走
        for _ in range(index):  # 走 index 步
            cur = cur.next  # 指针后移一个结点
        return cur.val  # 返回目标结点的值

    def addAtHead(self, val: int) -> None:  # addAtHead：在头部插入值为 val 的结点
        self.addAtIndex(0, val)  # 头部插入等价于在下标 0 之前插入

    def addAtTail(self, val: int) -> None:  # addAtTail：在尾部插入值为 val 的结点
        self.addAtIndex(self.cnt, val)  # 尾部插入等价于在末尾下标 cnt 处插入

    def addAtIndex(self, index: int, val: int) -> None:  # addAtIndex：在下标 index 之前插入值为 val 的结点
        if index > self.cnt:  # 下标大于长度说明位置非法，题目要求直接忽略
            return  # 非法位置：什么都不做就返回
        pre = self.dummy  # pre 从 dummy 出发，最终停在插入位置的前一个结点
        for _ in range(index):  # 走 index 步
            pre = pre.next  # pre 后移，逐步逼近插入位置的前驱
        pre.next = ListNode(val, pre.next)  # 新建结点挂在 pre 之后，原来的 pre.next 成为它的后继
        self.cnt += 1  # 元素个数加一

    def deleteAtIndex(self, index: int) -> None:  # deleteAtIndex：删除下标 index 处的结点
        if index >= self.cnt:  # 下标不小于长度，该位置没有结点可删
            return  # 直接返回
        pre = self.dummy  # pre 从 dummy 出发，最终停在待删结点的前驱
        for _ in range(index):  # 走 index 步
            pre = pre.next  # pre 后移
        t = pre.next  # 记下真正要被删除的结点
        pre.next = t.next  # 让前驱指针跨过该结点
        t.next = None  # 断开被删结点的 next，避免残留悬挂引用
        self.cnt -= 1  # 元素个数减一


# Your MyLinkedList object will be instantiated and called as such:
# obj = MyLinkedList()
# param_1 = obj.get(index)
# obj.addAtHead(val)
# obj.addAtTail(val)
# obj.addAtIndex(index,val)
# obj.deleteAtIndex(index)
