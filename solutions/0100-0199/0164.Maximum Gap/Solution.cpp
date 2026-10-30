// 题目：164. 最大间距（Maximum Gap）
// 核心思路：把值域按平均间距划分成若干桶，只记录每桶的最小/最大值；最大间距只可能出现在相邻非空桶之间，从而线性时间求解。
// 时间复杂度：O(n)，三趟线性遍历；空间复杂度：O(n)，桶数组随元素个数增长。
using pii = pair<int, int>;  // 类型别名：每个桶只存 (桶内最小值, 桶内最大值)

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int inf = 0x3f3f3f3f;  // 用 0x3f3f3f3f 当作「无穷大」哨兵，取相反数即为负无穷
    int maximumGap(vector<int>& nums) {  // nums：待求最大间距的无序数组（要求在 O(n) 内完成）
        int n = nums.size();  // 元素个数
        if (n < 2) return 0;  // 少于两个数时不存在间距，直接返回 0
        int mi = inf, mx = -inf;  // 数组最小值与最大值，先初始化为两个极端值
        for (int v : nums) {  // 第一趟：求整个数组的极值
            mi = min(mi, v);  // 更新最小值
            mx = max(mx, v);  // 更新最大值
        }
        int bucketSize = max(1, (mx - mi) / (n - 1));  // 桶宽取「平均间距」向下取整，至少为 1 以免除零
        int bucketCount = (mx - mi) / bucketSize + 1;  // 覆盖 [mi, mx] 所需的桶数量
        vector<pii> buckets(bucketCount, {inf, -inf});  // 每桶存 (min, max)，初值 {inf, -inf} 表示空桶
        for (int v : nums) {  // 第二趟：把每个元素放进对应桶
            int i = (v - mi) / bucketSize;  // 由数值线性映射到桶下标，同一桶的元素下标必相同
            buckets[i].first = min(buckets[i].first, v);  // 维护桶内最小值
            buckets[i].second = max(buckets[i].second, v);  // 维护桶内最大值
        }
        int ans = 0;  // 最大间距，最小也是 0
        int prev = inf;  // 上一个非空桶的最大值；先用 inf 占位，使首个桶算出的差值为负，不会污染答案
        for (auto [curmin, curmax] : buckets) {  // 第三趟：按值域从小到大扫描桶
            if (curmin > curmax) continue;  // min > max 说明该桶没有任何元素，跳过
            ans = max(ans, curmin - prev);  // 相邻非空桶之间的间距只可能来自桶与桶之间
            prev = curmax;  // 以当前桶最大值作为下一次比较的基准
        }
        return ans;  // 返回全局最大间距
    }
};