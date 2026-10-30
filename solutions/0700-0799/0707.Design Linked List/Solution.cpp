// 题目：707. 设计链表（Design Linked List）
// 思路：带虚拟头结点（dummy）的单链表，另存长度 cnt；按下标操作时先从 dummy 走到目标的前驱，再改指针。
// 时间复杂度：get / addAtIndex / deleteAtIndex 为 O(index)，addAtHead 为 O(1)；空间复杂度：O(n)，n 为链表长度。
class MyLinkedList {  // 自定义单链表类
private:  // 私有成员区：内部实现细节
    ListNode* dummy = new ListNode();  // 虚拟头结点，dummy->next 才是真正的首结点，可统一插入/删除的边界处理
    int cnt = 0;  // 记录链表元素个数，用于越界判断与尾插定位

public:  // 对外接口：判题器会依次调用下面这些方法
    MyLinkedList() {  // 构造函数：dummy 在成员初始化时已创建，这里无需额外操作
    }  // 空链表，cnt 保持初始值 0

    int get(int index) {  // get：返回下标 index 处的值，越界返回 -1
        if (index < 0 || index >= cnt) {  // 下标为负或已达到长度，说明该位置没有结点
            return -1;  // 越界时按题目要求返回 -1
        }
        auto cur = dummy->next;  // 从真正的首结点开始走
        while (index--) {  // 走 index 步，index 随之后减到 0
            cur = cur->next;  // 指针后移一个结点
        }
        return cur->val;  // 返回目标结点的值
    }

    void addAtHead(int val) {  // addAtHead：在头部插入值为 val 的结点
        addAtIndex(0, val);  // 头部插入等价于在下标 0 之前插入
    }

    void addAtTail(int val) {  // addAtTail：在尾部插入值为 val 的结点
        addAtIndex(cnt, val);  // 尾部插入等价于在长度为 cnt 的位置插入
    }

    void addAtIndex(int index, int val) {  // addAtIndex：在下标 index 之前插入值为 val 的结点
        if (index > cnt) {  // 下标大于长度说明位置非法，题目要求直接忽略
            return;  // 非法位置：什么都不做就返回
        }
        auto pre = dummy;  // pre 从 dummy 出发，最终停在插入位置的前一个结点
        while (index-- > 0) {  // 走 index 步，index 随之后减
            pre = pre->next;  // pre 后移，逐步逼近插入位置的前驱
        }
        pre->next = new ListNode(val, pre->next);  // 新建结点挂在 pre 之后，原来的 pre->next 成为新结点的后继
        ++cnt;  // 元素个数加一
    }

    void deleteAtIndex(int index) {  // deleteAtIndex：删除下标 index 处的结点
        if (index >= cnt) {  // 下标不小于长度，该位置没有结点可删
            return;  // 直接返回
        }
        auto pre = dummy;  // pre 从 dummy 出发，最终停在待删结点的前驱
        while (index-- > 0) {  // 走 index 步
            pre = pre->next;  // pre 后移
        }
        auto t = pre->next;  // 记下真正要被删除的结点
        pre->next = t->next;  // 让前驱指针跨过该结点
        t->next = nullptr;  // 断开被删结点的 next，避免残留悬挂引用
        --cnt;  // 元素个数减一
    }
};  // 类定义结束

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */