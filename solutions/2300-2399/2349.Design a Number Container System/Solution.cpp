// 题目：2349. 设计数字容器系统（Design a Number Container System）
// 思路：d 记录「下标 → 数字」，g 记录「数字 → 有序下标集合」；change 先清掉旧数字的记录，find 取集合首元素即最小下标。
// 时间复杂度：change 为 O(log n)，find 为 O(1)；空间复杂度：O(m)，m 是被赋过值的下标个数。
class NumberContainers {  // 数字容器系统：支持按下标改值、按数字查最小下标
public:  // 对外接口
    NumberContainers() {  // 构造函数：两个哈希表默认构造即可，不需要额外初始化
    }

    void change(int index, int number) {  // 把下标 index 处的数字改成 number
        if (d.contains(index)) {  // 该下标此前被赋过值，需要先清理旧数字的索引
            int oldNumber = d[index];  // 取出该下标原来的数字
            g[oldNumber].erase(index);  // 从「旧数字 → 下标集合」中删掉这个下标
            if (g[oldNumber].empty()) {  // 旧数字已经不再对应任何下标
                g.erase(oldNumber);  // 删除整个条目，避免 find 误以为该数字仍存在
            }
        }
        d[index] = number;  // 更新下标到新数字的映射
        g[number].insert(index);  // 把下标加入「新数字 → 下标集合」，set 保证集合有序
    }

    int find(int number) {  // 查询数字 number 所在的最小下标
        return g.contains(number) ? *g[number].begin() : -1;  // 存在则取有序集合的首元素，否则按题意返回 -1
    }

private:  // 内部数据结构
    unordered_map<int, int> d;  // 下标 → 数字
    unordered_map<int, set<int>> g;  // 数字 → 所有存有该数字的下标（有序）
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */