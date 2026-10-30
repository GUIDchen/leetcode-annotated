// 题目：379. 电话目录管理系统（Design Phone Directory）
// 思路：用一个哈希集合维护所有当前可分配的号码，取号时删一个、归还时加回，均摊 O(1)。
// 时间复杂度：构造 O(n)，get / check / release 平均 O(1)；空间复杂度：O(n)，集合最多存 n 个号码。
class PhoneDirectory {  // 设计题要求的类名
public:  // 对外接口
    PhoneDirectory(int maxNumbers) {  // maxNumbers 为号码总数，号码取值范围 [0, maxNumbers - 1]
        for (int i = 0; i < maxNumbers; ++i) {  // 把全部号码依次加入可用集合
            available.insert(i);  // 号码 i 初始即可分配
        }
    }

    int get() {  // 取出一个可用号码并从集合中删除，无可用时返回 -1
        if (available.empty()) {  // 集合为空表示号码已耗尽
            return -1;  // 没有可用号码，按题目约定返回 -1
        }
        int x = *available.begin();  // 取集合中的第一个可用号码（最小号码）
        available.erase(x);  // 取走后从可用集合中删除，保证不会被重复分配
        return x;  // 返回分配到的号码
    }

    bool check(int number) {  // 判断某个号码当前是否仍可分配
        return available.contains(number);  // C++20 的 contains：在集合中即表示可用
    }

    void release(int number) {  // 归还号码，使其可以再次被分配
        available.insert(number);  // 重新放回可用集合
    }

private:  // 内部成员
    unordered_set<int> available;  // 可用号码集合，哈希表保证增删查平均 O(1)
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory* obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj->get();
 * bool param_2 = obj->check(number);
 * obj->release(number);
 */