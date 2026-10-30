// 题目：954. 二倍数对数组（Array of Doubled Pairs）
// 思路：统计每个数值的出现次数，按绝对值从小到大强制让 k 与 2k 配对；0 只能和 0 配对，出现奇数次即失败。
// 时间复杂度：O(n + m log m)，n 为数组长度、m 为不同数值个数；空间复杂度：O(m)，哈希表与键列表各存 m 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canReorderDoubled(vector<int>& arr) {  // arr：输入数组，判断能否重排成 a0*2==a1、a2*2==a3 这样两两成对
        unordered_map<int, int> freq;  // 哈希表 freq：键是数值，值是该数值出现的次数
        for (int& v : arr) ++freq[v];  // 一次遍历就把每个数值的出现次数统计好
        if (freq[0] & 1) return false;  // 0 只能和 0 配对，0 出现奇数次就必然剩下一个，直接判失败
        // 先把所有出现过的不同数值收集起来，方便后面统一按绝对值排序
        vector<int> keys;
        for (auto& [k, _] : freq) keys.push_back(k);  // 用结构化绑定遍历哈希表，把每个不同的键压入 keys
        sort(keys.begin(), keys.end(), [](int a, int b) { return abs(a) < abs(b); });  // 按绝对值升序：绝对值小的值只有 2k 这一个配对对象，必须优先占位
        for (int& k : keys) {  // 从小到大依次处理每个不同的数值 k
            if (freq[k * 2] < freq[k]) return false;  // 要凑出 freq[k] 个 2k 与 k 配对，2k 数量不够就说明无法重排
            freq[k * 2] -= freq[k];  // 用掉与 k 配对的那些 2k，剩下的次数留给后面更大的数值使用
        }  // 所有数值都配对完了
        return true;  // 没有出现配对失败，说明可以重排，返回 true
    }  // 方法结束
};  // 类定义结束