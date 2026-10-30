// 题目：1207. 独一无二的出现次数（Unique Number of Occurrences）
// 思路：先用哈希表统计每个值的出现次数，再用哈希集合检查这些次数是否两两不同。
// 时间复杂度：O(n)，只扫描数组与频次表各一次；空间复杂度：O(n)，哈希表与集合最多存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool uniqueOccurrences(vector<int>& arr) {  // arr：输入数组；返回是否所有出现次数都互不相同
        unordered_map<int, int> cnt;  // 哈希表：键是数组中的值，值是它出现的次数
        for (int& x : arr) {  // 遍历数组，逐个累加元素频次
            ++cnt[x];  // 计数加一；键不存在时会先被默认构造为 0
        }  // 频次统计循环结束
        unordered_set<int> vis;  // 哈希集合：记录已经出现过的频次，用于判重
        for (auto& [_, v] : cnt) {  // 结构化绑定遍历频次表，值本身用不到，只看次数 v
            if (vis.count(v)) {  // 这个次数之前已经出现过，说明次数重复了
                return false;  // 直接判定不满足题意
            }  // 重复判断结束
            vis.insert(v);  // 把当前次数记入集合，供后续比较
        }  // 频次遍历结束
        return true;  // 所有次数都独一无二，返回真
    }  // uniqueOccurrences 方法结束
};  // 题解类定义结束