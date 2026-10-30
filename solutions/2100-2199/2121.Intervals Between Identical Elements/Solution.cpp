// 题目：2121. 相同元素的间隔之和（Intervals Between Identical Elements）
// 核心思路：把每个值出现的下标聚成一组，组内用前缀和技巧 O(k) 递推：中心右移 delta 时左侧各加、右侧各减。
// 时间复杂度：O(n)，每个下标只被访问常数次；空间复杂度：O(n)，哈希表保存所有下标分组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> getDistances(vector<int>& arr) {  // arr：输入数组
        unordered_map<int, vector<int>> d;  // 值 → 该值出现的所有下标（按扫描顺序天然升序）
        int n = arr.size();  // 数组长度
        for (int i = 0; i < n; ++i) d[arr[i]].push_back(i);  // 一遍扫描把所有下标按值分组
        vector<long long> ans(n);  // 答案数组，用 long long 防止间隔和超出 int 范围
        for (auto& item : d) {  // 逐个值处理它的下标列表
            auto& v = item.second;  // v 是当前这个值的升序下标列表
            int m = v.size();  // 该值出现的次数
            long long val = 0;  // val 用来保存「当前下标到同组其他下标的距离和」
            for (int e : v) val += e;  // 先求出该组所有下标的总和
            val -= 1LL * m * v[0];  // 减去 m 倍首下标，得到首下标位置到其余下标的距离和
            for (int i = 0; i < v.size(); ++i) {  // 按组内顺序递推每个位置的答案
                int delta = i >= 1 ? v[i] - v[i - 1] : 0;  // 与上一个同值下标的间距，i 为 0 时取 0
                val += 1LL * i * delta - 1LL * (m - i) * delta;  // 中心右移 delta：左侧 i 个各加 delta，右侧 m-i 个各减 delta
                ans[v[i]] = val;  // 把结果写回该下标在原数组中的位置
            }
        }
        return ans;  // 返回所有位置的间隔之和
    }
};