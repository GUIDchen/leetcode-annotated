# 题目：432. 全 O(1) 的数据结构（All O`one Data Structure）
# 思路：用按 cnt 严格递增排序的双向循环链表存「同一计数的 key 集合」，哈希表记录 key → 所在节点；inc/dec 只需挪到相邻节点或插入新节点。
# 时间复杂度：inc/dec/getMaxKey/getMinKey 均为 O(1)；空间复杂度：O(n)，n 为不同 key 的数量。
class Node:  # 链表节点：一个节点代表一种出现次数 cnt，以及取到该次数的所有 key
    def __init__(self, key='', cnt=0):  # key 是首个放入该节点的键，cnt 是该节点的出现次数
        self.prev = None  # 前驱指针：循环链表，初始为空由外部链接
        self.next = None  # 后继指针：与 prev 一起构成双向循环链表
        self.cnt = cnt  # 该节点代表的出现次数，链表从头到尾严格递增
        self.keys = {key}  # 同一计数的键集合，用 set 保证增删查都是 O(1)

    def insert(self, node):  # 把新节点 node 插入到 self 之后（self 的后继位置）
        node.prev = self  # node 的前驱指向 self
        node.next = self.next  # node 的后继指向 self 原来的后继
        node.prev.next = node  # 让 self 的后继节点回指 node，完成前半段链接
        node.next.prev = node  # 让原后继节点的前驱指向 node，完成后半段链接
        return node  # 返回插入的节点，方便调用处直接用哈希表记录

    def remove(self):  # 把当前节点从双向循环链表中摘除（O(1)）
        self.prev.next = self.next  # 前驱绕过自己，直接指向后继
        self.next.prev = self.prev  # 后继绕过自己，直接指向前驱


class AllOne:  # 主数据结构：root 是 cnt=0 的哨兵，真实节点按 cnt 升序挂在环上
    def __init__(self):  # 初始化数据结构
        self.root = Node()  # 哨兵节点，不存放任何真实 key
        self.root.next = self.root  # 初始只有哨兵自己，next 自环
        self.root.prev = self.root  # prev 同样自环，构成空的双向循环链表
        self.nodes = {}  # 哈希表：key → 该 key 当前所在的链表节点

    def inc(self, key: str) -> None:  # 把 key 的出现次数加 1，并维护链表与哈希表
        root, nodes = self.root, self.nodes  # 取局部变量，减少重复的属性查找
        if key not in nodes:  # 情况一：key 是第一次出现，计数从 0 变成 1
            if root.next == root or root.next.cnt > 1:  # 链表为空，或最小计数大于 1（不存在 cnt=1 的节点）时需要新建节点
                nodes[key] = root.insert(Node(key, 1))  # 在哨兵之后插入 cnt=1 的新节点，并让哈希表指向它
            else:  # 否则最小的真实节点恰好就是 cnt=1，复用它即可
                root.next.keys.add(key)  # 把 key 放进 cnt=1 节点的键集合
                nodes[key] = root.next  # 哈希表指向该节点
        else:  # 情况二：key 已存在，计数从 c 增加到 c+1
            curr = nodes[key]  # 取出 key 当前所在的节点
            next = curr.next  # 它的后继是计数更大的下一个节点
            if next == root or next.cnt > curr.cnt + 1:  # 后继是哨兵，或后继计数跳过了 c+1，说明不存在 cnt=c+1 的节点
                nodes[key] = curr.insert(Node(key, curr.cnt + 1))  # 就在 curr 之后新建 cnt=c+1 的节点，并把哈希表改指向它
            else:  # 否则后继计数正好是 c+1，直接加入该节点
                next.keys.add(key)  # 把 key 放进后继节点的键集合
                nodes[key] = next  # 哈希表改指向后继节点
            curr.keys.discard(key)  # 把 key 从原节点移除；discard 在 key 不存在时也不会报错
            if not curr.keys:  # 原节点的键集合空了，说明这个计数已无人使用
                curr.remove()  # 把它从链表中摘除

    def dec(self, key: str) -> None:  # 把 key 的出现次数减 1，减到 0 时删除该 key
        root, nodes = self.root, self.nodes  # 取局部变量，减少重复的属性查找
        curr = nodes[key]  # 先找到 key 当前所在的节点（题目保证 key 存在）
        if curr.cnt == 1:  # 计数为 1，减 1 后就是 0，key 应该彻底消失
            nodes.pop(key)  # 直接从哈希表删除该 key
        else:  # 否则计数从 c 减到 c-1，需要迁移到前驱方向
            prev = curr.prev  # 前驱是计数更小的那个节点
            if prev == root or prev.cnt < curr.cnt - 1:  # 前驱是哨兵，或前驱计数小于 c-1，说明不存在 cnt=c-1 的节点
                nodes[key] = prev.insert(Node(key, curr.cnt - 1))  # 在前驱之后插入 cnt=c-1 的新节点，并让哈希表指向它
            else:  # 否则前驱计数正好是 c-1，直接加入该节点
                prev.keys.add(key)  # 把 key 放进前驱节点的键集合
                nodes[key] = prev  # 哈希表改指向前驱节点
        curr.keys.discard(key)  # 把 key 从原节点移除
        if not curr.keys:  # 原节点的键集合空了
            curr.remove()  # 把空节点从链表摘除

    def getMaxKey(self) -> str:  # 返回出现次数最多的某个 key
        return next(iter(self.root.prev.keys))  # 环尾节点 root.prev 计数最大，取它键集合里的任意一个即可（空表时为哨兵的 ''）

    def getMinKey(self) -> str:  # 返回出现次数最少的某个 key
        return next(iter(self.root.next.keys))  # 环首节点 root.next 计数最小，取它键集合里的任意一个即可（空表时为哨兵的 ''）


# Your AllOne object will be instantiated and called as such:
# obj = AllOne()
# obj.inc(key)
# obj.dec(key)
# param_3 = obj.getMaxKey()
# param_4 = obj.getMinKey()
