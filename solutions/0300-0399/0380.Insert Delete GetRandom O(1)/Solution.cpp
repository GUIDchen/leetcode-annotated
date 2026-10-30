// 题目：380. O(1) 时间插入、删除和获取随机元素（Insert Delete GetRandom O(1)）
// 思路：动态数组存元素支持随机下标访问，哈希表存「值 → 下标」；删除时用尾元素覆盖被删位置，避免数组搬移。
// 时间复杂度：insert / remove / getRandom 平均 O(1)；空间复杂度：O(n)，数组与哈希表各存 n 个元素。
class RandomizedSet {  // 设计题要求的类名
public:  // 对外接口
    RandomizedSet() {  // 构造函数：容器初始为空，成员默认构造即可
    }

    bool insert(int val) {  // 插入 val，若已存在则返回 false
        if (d.count(val)) {  // 哈希表里已有 val，说明重复
            return false;  // 重复插入按题目要求返回 false
        }
        d[val] = q.size();  // 记录 val 在动态数组中的下标（即将追加到末尾）
        q.push_back(val);  // 把 val 追加到数组尾部
        return true;  // 插入成功
    }

    bool remove(int val) {  // 删除 val，若不存在则返回 false
        if (!d.count(val)) {  // 哈希表中没有 val，说明不存在
            return false;  // 不存在，按题目要求返回 false
        }
        int i = d[val];  // 先取出 val 在数组中的下标
        d[q.back()] = i;  // 尾元素马上要被搬到位置 i，先更新它在哈希表中记录的下标
        q[i] = q.back();  // 用尾元素覆盖待删除的位置，避免整体前移
        q.pop_back();  // 删掉尾部那份多余的元素
        d.erase(val);  // 最后从哈希表中移除 val
        return true;  // 删除成功
    }

    int getRandom() {  // 等概率随机返回集合中的一个元素
        return q[rand() % q.size()];  // 在数组下标上随机取模，即可等概率取到每个元素
    }

private:  // 内部成员
    unordered_map<int, int> d;  // 值 → 在数组中的下标
    vector<int> q;  // 动态数组，支持 O(1) 随机下标访问
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */