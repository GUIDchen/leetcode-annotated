// 题目：705. 设计哈希集合（Design HashSet）
// 思路：键的取值范围是 0 到 1000000，直接用定长 bool 数组做桶，下标即键，true 表示存在，用空间换时间。
// 时间复杂度：add / remove / contains 均为 O(1)；空间复杂度：O(C)，C = 1000001 个布尔槽位。
class MyHashSet {  // 自定义哈希集合类
public:  // 对外接口：构造、add、remove、contains
    bool data[1000001];  // 定长布尔数组：下标就是键，true 表示集合中存在该键

    MyHashSet() {  // 构造函数：把数组全部清零，得到空集合
        memset(data, false, sizeof data);  // memset 按字节写 false，等价于把所有槽位置为「不存在」
    }

    void add(int key) {  // 加入 key：把对应下标标记为存在
        data[key] = true;  // 直接按下标置真，重复加入也不会有副作用，天然去重
    }

    void remove(int key) {  // 删除 key：把对应下标标记为不存在
        data[key] = false;  // 直接按下标置假，键本来就不存在时也安全
    }

    bool contains(int key) {  // 查询 key 是否在集合中
        return data[key];  // 返回该下标上的布尔标记即可
    }
};  // 类定义结束

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */