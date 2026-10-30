// 3728. Stable Subarrays With Equal Boundary and Interior Sum（边界与内部和相等的稳定子数组）
// 核心思路：用前缀和表示区间和，把“左边界特征”(capacity[l], capacity[l]+s[l+1]) 与“右边界特征”(capacity[r], s[r]) 做成哈希 key，特征相同即说明边界值相等且内部和等于边界值，边扫边计数。
// 复杂度：时间 O(n)，空间 O(n)（前缀和数组与哈希表）。

struct PairHash {  // 为 pair<int, long long> 自定义哈希函数，供 unordered_map 使用
    size_t operator()(const pair<int, long long>& p) const {  // 仿函数：计算 pair 的哈希值
        return hash<int>()(p.first) ^ (hash<long long>()(p.second) << 1);  // 两个成员的哈希值错位异或，降低冲突概率
    }  // operator() 结束
};  // 仿函数结构体结束

class Solution {  // 题解类
public:
    long long countStableSubarrays(vector<int>& capacity) {  // 统计满足“边界值等于内部和”的稳定子数组个数
        int n = capacity.size();  // 取数组长度 n
        vector<long long> s(n + 1, 0);  // 前缀和数组 s，s[i] = capacity[0..i-1] 之和，长度为 n+1
        for (int i = 1; i <= n; ++i) {  // 从 1 开始递推前缀和
            s[i] = s[i - 1] + capacity[i - 1];  // s[i] 等于前 i 个元素之和
        }  // 前缀和构造结束

        unordered_map<pair<int, long long>, int, PairHash> cnt;  // 哈希表：左边界特征 -> 出现次数，用于和右边界特征配对
        long long ans = 0;  // 稳定子数组的计数

        for (int r = 2; r < n; ++r) {  // 枚举右端点 r，从 2 开始以保证内部至少有一个元素
            int l = r - 2;  // 左端点 l 比 r 小 2，随 r 同步后移
            pair<int, long long> keyL = {capacity[l], capacity[l] + s[l + 1]};  // 把左边界特征 (capacity[l], capacity[l] + s[l+1]) 作为 key
            cnt[keyL] += 1;  // 该特征的左端点出现次数加一

            pair<int, long long> keyR = {capacity[r], s[r]};  // 把右边界特征 (capacity[r], s[r]) 作为 key
            ans += cnt.count(keyR) ? cnt[keyR] : 0;  // 存在相同特征的左端点则有 cnt[keyR] 个稳定子数组，累加计数
        }  // 右端点枚举结束

        return ans;  // 返回稳定子数组个数
    }  // 函数结束
};  // 题解类结束
