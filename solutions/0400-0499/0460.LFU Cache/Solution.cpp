// 题目：460. LFU 缓存（LFU Cache）
// 思路：键表 map 存「键→节点」，频次表 freqMap 存「频次→双向链表」；get/put 命中后把节点搬到频次+1 的链表头部，满容量时从 minFreq 链表的尾部淘汰最久未使用的键，并维护当前最小频次。
// 时间复杂度：get 与 put 均为 O(1)（哈希表 + 双向链表）；空间复杂度：O(capacity)，节点、键表与频次表都与容量同阶。
class Node {  // 双向链表节点：存放键、值、访问频次以及前后指针
public:  // 成员对外可见，方便链表与缓存直接访问
    int key;  // 缓存键
    int value;  // 缓存值
    int freq;  // 该键被访问的次数（频次）
    Node* prev;  // 前驱节点
    Node* next;  // 后继节点
    Node(int key, int value) {  // 构造函数：新节点的频次从 1 开始
        this->key = key;  // 记录键
        this->value = value;  // 记录值
        this->freq = 1;  // 首次插入即视为访问过一次
        this->prev = nullptr;  // 前后指针先置空，插入链表时再设置
        this->next = nullptr;  // 同上
    }  // 结束构造函数
};

class DoublyLinkedList {  // 双向链表：同一访问频次的所有键放在同一条链表中，链表头部是最近访问的
public:  // 成员对外可见
    Node* head;  // 哨兵头节点，不存真实数据，省去边界判断
    Node* tail;  // 哨兵尾节点，不存真实数据
    DoublyLinkedList() {  // 构造：建立头尾哨兵并互连成空链表
        this->head = new Node(-1, -1);  // 创建头哨兵
        this->tail = new Node(-1, -1);  // 创建尾哨兵
        this->head->next = this->tail;  // head 的后继指向 tail
        this->tail->prev = this->head;  // tail 的前驱指向 head
    }  // 结束构造函数
    void addFirst(Node* node) {  // 把节点插入链表头部（表示该频次下最近被访问）
        node->prev = this->head;  // 新节点的前驱是哨兵 head
        node->next = this->head->next;  // 新节点的后继是原来的第一个真实节点
        this->head->next->prev = node;  // 原第一个节点的前驱改为新节点
        this->head->next = node;  // head 的后继指向新节点
    }  // 结束 addFirst
    Node* remove(Node* node) {  // 从链表中摘除指定节点并返回它
        node->next->prev = node->prev;  // 让后继节点绕过当前节点
        node->prev->next = node->next;  // 让前驱节点绕过当前节点
        node->next = nullptr;  // 断开自身后继指针，避免悬挂引用
        node->prev = nullptr;  // 断开自身前驱指针
        return node;  // 返回被摘除的节点
    }  // 结束 remove
    Node* removeLast() {  // 删除并返回链表尾部节点，即该频次下最久未使用的键
        return remove(this->tail->prev);  // tail 的前驱就是最后一个真实节点
    }  // 结束 removeLast
    bool isEmpty() {  // 判断链表是否为空（只剩两个哨兵）
        return this->head->next == this->tail;  // head 直接指向 tail 说明没有真实节点
    }  // 结束 isEmpty
};

class LFUCache {  // LFU 缓存：按访问频次淘汰，频次相同则淘汰最久未使用的
public:  // 对外接口
    LFUCache(int capacity) {  // 构造函数：记录容量并初始化最小频次
        this->capacity = capacity;  // 保存缓存容量
        this->minFreq = 0;  // 当前缓存中的最小频次，用于 O(1) 定位要淘汰的链表
    }  // 结束构造函数

    int get(int key) {  // 读取键对应的值，不存在返回 -1
        if (capacity == 0 || map.find(key) == map.end()) {  // 容量为 0 或键不存在
            return -1;  // 未命中，返回 -1
        }  // 结束未命中分支
        Node* node = map[key];  // 取出对应节点
        incrFreq(node);  // 命中后频次加一，并在频次链表中移动
        return node->value;  // 返回节点值
    }  // 结束 get

    void put(int key, int value) {  // 写入键值对
        if (capacity == 0) {  // 容量为 0 时无法缓存任何内容
            return;  // 直接返回
        }  // 结束容量判断
        if (map.find(key) != map.end()) {  // 键已存在：更新值并提升频次
            Node* node = map[key];  // 取出已有节点
            node->value = value;  // 覆盖旧值
            incrFreq(node);  // 频次加一并移动到新频次链表
            return;  // 更新完成
        }  // 结束已存在分支
        if (map.size() == capacity) {  // 缓存已满，需要先淘汰一个元素
            DoublyLinkedList* list = freqMap[minFreq];  // 最小频次链表：其尾部就是该频次下最久未使用的节点
            Node* node = list->removeLast();  // 摘除链表尾部节点（即被淘汰的节点）
            map.erase(node->key);  // 同时从键表中删除该键
        }  // 结束淘汰分支
        Node* node = new Node(key, value);  // 为新键创建节点（频次初始为 1）
        addNode(node);  // 加入频次 1 对应的链表
        map[key] = node;  // 记录键到节点的映射
        minFreq = 1;  // 新插入的键频次最小，最小频次重置为 1
    }  // 结束 put

private:  // 私有成员与内部辅助方法
    int capacity;  // 缓存容量
    int minFreq;  // 当前最小频次
    unordered_map<int, Node*> map;  // 键 -> 节点 的哈希表，O(1) 定位
    unordered_map<int, DoublyLinkedList*> freqMap;  // 频次 -> 该频次对应的双向链表 的哈希表

    void incrFreq(Node* node) {  // 把节点的频次加一，并按新频次重新挂到对应链表
        int freq = node->freq;  // 记录旧频次
        DoublyLinkedList* list = freqMap[freq];  // 取出旧频次对应的链表
        list->remove(node);  // 先从旧链表中摘除该节点
        if (list->isEmpty()) {  // 旧频次链表已空
            freqMap.erase(freq);  // 删除这个频次的映射，避免空链表残留
            if (freq == minFreq) {  // 如果空的正是最小频次链表
                minFreq++;  // 最小频次整体加一（只有最小频次链表被搬空时才会发生）
            }  // 结束最小频次判断
        }  // 结束空链表分支
        node->freq++;  // 节点频次加一
        addNode(node);  // 按新频次头插到对应链表
    }  // 结束 incrFreq

    void addNode(Node* node) {  // 把节点插入它当前频次对应链表的头部
        int freq = node->freq;  // 读取节点当前频次
        if (freqMap.find(freq) == freqMap.end()) {  // 该频次还没有链表
            freqMap[freq] = new DoublyLinkedList();  // 新建一条双向链表并登记
        }  // 结束创建分支
        DoublyLinkedList* list = freqMap[freq];  // 取出该频次对应的链表
        list->addFirst(node);  // 头插，表示该频次下最近被访问
        freqMap[freq] = list;  // 回写映射（引用本身不变，确保该频次存在对应链表）
    }  // 结束 addNode
};

// 下面是 LeetCode 给出的使用示例（原题注释，保留原样）
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */