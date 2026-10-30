// 题目：706. 设计哈希映射（Design HashMap）
// 思路：键的取值范围是 0 到 1000000，直接用定长 int 数组做桶，下标即键，值即 value，用 -1 表示键不存在。
// 时间复杂度：put / get / remove 均为 O(1)；空间复杂度：O(C)，C = 1000001 个 int 槽位。
class MyHashMap {  // 自定义哈希映射类
public:  // 对外接口：构造、put、get、remove
    int data[1000001];  // 定长数组：下标是键，元素值是对应的 value，-1 表示该键尚未插入

    MyHashMap() {  // 构造函数：把所有槽位初始化为 -1，得到空的映射
        memset(data, -1, sizeof data);  // memset 按字节写 -1，使每个 int 都变成 -1，表示全部键都不存在
    }

    void put(int key, int value) {  // put：插入或更新一个键值对
        data[key] = value;  // 直接覆盖写，天然支持「键已存在则更新其值」
    }

    int get(int key) {  // get：查询键对应的值
        return data[key];  // 未插入过的键保持 -1，正好符合题目「不存在返回 -1」的要求
    }

    void remove(int key) {  // remove：删除一个键
        data[key] = -1;  // 把值改回 -1，表示该键又变回不存在
    }
};  // 类定义结束

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */