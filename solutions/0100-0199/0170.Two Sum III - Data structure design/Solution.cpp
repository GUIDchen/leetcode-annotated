// 题目：170. 两数之和 III - 数据结构设计（Two Sum III - Data Structure Design）
// 思路：哈希表记录「数值 → 出现次数」，find 时枚举已有数值 x，判断补数 value - x 是否存在；当 x 与补数相同时要求该数至少出现两次。
// 时间复杂度：add 为 O(1)，find 为 O(n)（n 是不同数值的个数）；空间复杂度：O(n)，存下所有加入过的数值。
class TwoSum {  // LeetCode 约定的题解类：支持 add 与 find 两数之和的数据结构
public:  // 对外公开的接口
    TwoSum() {  // 构造函数：成员 cnt 由默认构造完成初始化，函数体无需做事
    }  // 构造函数体结束

    void add(int number) {  // 加入一个新数字
        ++cnt[number];  // 计数加一：同一个数字可能被加入多次，所以必须记录出现次数
    }  // add 结束

    bool find(int value) {  // 判断容器中是否存在两个数之和恰好等于 value
        for (auto& [x, v] : cnt) {  // 结构化绑定遍历哈希表：x 是数值，v 是它的出现次数
            long y = (long) value - x;  // 还需要的另一个数；转成 long 防止 value - x 在 int 上溢出
            if (cnt.contains(y) && (x != y || v > 1)) {  // 补数已存在，且（两个数不同 或 同一个数至少出现两次）才算一对
                return true;  // 找到一对，立即返回 true
            }  // if 结束
        }  // 遍历结束
        return false;  // 枚举完所有数值都没有配对成功
    }  // find 结束

private:  // 以下是内部数据，只允许类自身访问
    unordered_map<int, int> cnt;  // 哈希表：键是加入过的数值，值是它出现的次数
};  // 类定义结束

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */