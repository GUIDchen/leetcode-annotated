// 题目：146. LRU 缓存（LRU Cache）
// 思路：哈希表 key→节点 实现 O(1) 定位，双向链表维护访问顺序，头热尾冷，超容量时淘汰尾节点。
// 时间复杂度：get 与 put 均为 O(1)；空间复杂度：O(capacity)，哈希表与链表各存一份节点。
class LRUCache {  // 题目要求的缓存类
private:  // 以下成员只在内部使用：链表节点、容量、哨兵头尾与哈希表
    struct Node {  // 双向链表节点：存 key、val 与前驱/后继，用来维护访问顺序
        int key, val;  // key 用于淘汰时反查哈希表；val 是缓存值
        Node* prev;  // 前驱指针
        Node* next;  // 后继指针
        Node(int key, int val)  // 构造函数：新节点默认没有前驱后继
            : key(key)  // 初始化 key
            , val(val)  // 初始化 val
            , prev(nullptr)  // 前驱先置空，插入链表时再赋值
            , next(nullptr) {}  // 后继先置空
    };  // 节点定义结束

    int size;  // 当前已缓存的元素个数
    int capacity;  // 容量上限
    Node* head;  // 哨兵头：head->next 是最近使用的节点
    Node* tail;  // 哨兵尾：tail->prev 是最久未使用的节点
    unordered_map<int, Node*> cache;  // 哈希表：key → 节点指针，使 get/put 达到 O(1)

    void removeNode(Node* node) {  // 从双向链表中摘除一个节点（不释放内存）
        node->prev->next = node->next;  // 让前驱直接指向后继
        node->next->prev = node->prev;  // 让后继直接指向前驱，节点被摘下
    }

    void addToHead(Node* node) {  // 把节点插到哨兵头之后，表示它刚刚被访问过
        node->next = head->next;  // 新节点的后继指向原来的第一个节点
        node->prev = head;  // 新节点的前驱指向哨兵头，即放到最前面
        head->next->prev = node;  // 原来第一个节点的前驱改为新节点
        head->next = node;  // 哨兵头指向新节点，四步指针修改完成插入
    }

public:  // 对外接口：构造、get、put
    LRUCache(int capacity)  // 构造函数：记录容量，并建立只含两个哨兵节点的空链表
        : size(0)  // 初始没有任何缓存元素
        , capacity(capacity) {  // 保存容量上限
        head = new Node(0, 0);  // 哨兵头：不存真实数据，只为简化边界判断
        tail = new Node(0, 0);  // 哨兵尾：不存真实数据
        head->next = tail;  // 空链表时头直接指向尾
        tail->prev = head;  // 尾再指回头，双向链表打通
    }

    int get(int key) {  // 读取 key 的值，不存在返回 -1
        if (!cache.contains(key)) {  // C++20 的 contains：key 不在哈希表中
            return -1;  // 按题目约定返回 -1
        }
        Node* node = cache[key];  // 取出节点，准备把它提到链表最前面
        removeNode(node);  // 先从原位置摘下
        addToHead(node);  // 再插到头部，标记为最近使用
        return node->val;  // 返回缓存值
    }

    void put(int key, int value) {  // 写入或更新缓存，容量满时淘汰最久未使用的节点
        if (cache.contains(key)) {  // key 已存在：原地更新即可
            Node* node = cache[key];  // 取出已有节点
            removeNode(node);  // 先摘下
            node->val = value;  // 覆盖为新值
            addToHead(node);  // 插回头部，这次写入也算一次使用
        } else {  // key 不存在：需要新建节点
            Node* node = new Node(key, value);  // 创建新节点
            cache[key] = node;  // 哈希表登记这个 key
            addToHead(node);  // 新节点插到链表头部
            if (++size > capacity) {  // 计数先加一，超出容量就要淘汰
                node = tail->prev;  // 尾部前一个节点就是最久未使用的节点
                cache.erase(node->key);  // 哈希表中同步删除该 key
                removeNode(node);  // 链表里摘下这个节点
                --size;  // 个数减一，重新回到不超容量
            }
        }
    }
};

// ↓ 下面是 LeetCode 生成的调用示例注释，按原样保留
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
