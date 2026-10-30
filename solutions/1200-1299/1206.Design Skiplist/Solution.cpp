// 题目：1206. 设计跳表（Design Skiplist）
// 思路：用多层有序链表实现跳表，每个结点随机得到一个层数（以 1/4 概率逐层晋升），查询/插入/删除都从最高层往下按「能找到的最右结点」逐层下降。
// 时间复杂度：平均 O(log n)，最坏 O(n)；空间复杂度：O(n)，期望每个结点层数为常数（约 1/(1-p) 层）。
struct Node {  // 跳表结点：值 + 各层的后继指针数组
    int val;  // 结点保存的数值，头结点用 -1 作哨兵
    vector<Node*> next;  // next[i] 表示第 i 层的后继结点，层数由构造时决定
    Node(int v, int level)  // 构造函数：值 v，层数 level
        : val(v)  // 初始化成员 val
        , next(level, nullptr) {}  // 各层后继先全部置空；构造参数 level 决定该结点占据多少层
};  // 结点结构体定义结束

class Skiplist {  // 跳表主体：封装插入、删除、查询
public:  // 对外暴露的接口
    const int p = RAND_MAX / 4;  // 阈值 p：rand() 小于它即向上晋升一层，晋级概率约 1/4
    const int maxLevel = 32;  // 最大层数，32 层足够覆盖 4^32 量级的数据，避免无限增高
    Node* head;  // 头指针指向哨兵结点，它的价值为 -1 且占满 maxLevel 层
    int level;  // 当前跳表的实际最高层数，插入/删除时动态维护

    Skiplist() {  // 构造函数：初始化空跳表
        head = new Node(-1, maxLevel);  // 建立占满所有层的哨兵头结点，方便每层统一从 head 出发
        level = 0;  // 空表没有任何数据层，最高层数记为 0
    }  // 构造函数结束

    bool search(int target) {  // 查询 target 是否存在
        Node* curr = head;  // 从哨兵头结点开始，自顶向下逐层查找
        for (int i = level - 1; ~i; --i) {  // 从当前最高层往下遍历到第 0 层（~i 等价于 i >= 0）
            curr = findClosest(curr, i, target);  // 在第 i 层找到最后一个小于 target 的结点，逐层缩小范围
            if (curr->next[i] && curr->next[i]->val == target) return true;  // 第 i 层的下一个结点就是 target，说明存在，立即返回
        }  // 逐层扫描结束
        return false;  // 所有层都没命中，说明 target 不存在
    }  // search 方法结束

    void add(int num) {  // 插入 num，若已存在则再插入一份（跳表允许重复值）
        Node* curr = head;  // 从哨兵头结点出发，逐层寻找插入位置的前驱
        int lv = randomLevel();  // 随机决定新结点占据的层数，作为后续是否在该层插入的依据
        Node* node = new Node(num, lv);  // 创建新结点，其指针数组长度恰为 lv
        level = max(level, lv);  // 若新结点层数更高，则提升整张表的当前最高层数
        for (int i = level - 1; ~i; --i) {  // 从最高层往第 0 层下降，边下降边挂接指针
            curr = findClosest(curr, i, num);  // 在第 i 层找到插入位置的前一个结点
            if (i < lv) {  // 只有低于新结点层数的层才需要真正插入指针
                node->next[i] = curr->next[i];  // 新结点接管前驱原本的后继
                curr->next[i] = node;  // 前驱改为指向新结点，完成第 i 层的链表插入
            }  // 本层插入分支结束
        }  // 逐层下降结束
    }  // add 方法结束

    bool erase(int num) {  // 删除一个值为 num 的结点，返回是否真的删到了
        Node* curr = head;  // 从哨兵头结点出发，逐层寻找待删结点的前驱
        bool ok = false;  // 标记是否至少在一层删到了该值
        for (int i = level - 1; ~i; --i) {  // 自顶向下逐层处理，保证每层的指针都被摘下
            curr = findClosest(curr, i, num);  // 在第 i 层找到待删结点之前的结点
            if (curr->next[i] && curr->next[i]->val == num) {  // 第 i 层的下一个结点正是待删结点
                curr->next[i] = curr->next[i]->next[i];  // 前驱跨过待删结点，把它从第 i 层链表摘除
                ok = true;  // 记录本次删除成功
            }  // 本层命中判断结束
        }  // 逐层扫描结束
        while (level > 1 && !head->next[level - 1]) --level;  // 若最高层已经没有数据结点，就收缩表的层数，避免无效的顶层遍历
        return ok;  // 返回是否删到过该值
    }  // erase 方法结束

    Node* findClosest(Node* curr, int level, int target) {  // 在第 level 层从 curr 出发，找到最后一个值小于 target 的结点
        while (curr->next[level] && curr->next[level]->val < target) curr = curr->next[level];  // 只要下一个结点仍小于 target 就右移，直到再往后就跨过 target
        return curr;  // 返回这一层上最靠右的「小于 target」的结点
    }  // findClosest 方法结束

    int randomLevel() {  // 随机生成新结点的层数
        int lv = 1;  // 层数至少为 1，保证每个结点一定出现在第 0 层
        while (lv < maxLevel && rand() < p) ++lv;  // 每层以约 1/4 的概率继续晋升，直到失败或触顶
        return lv;  // 返回最终层数
    }  // randomLevel 方法结束
};  // 跳表类定义结束

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */