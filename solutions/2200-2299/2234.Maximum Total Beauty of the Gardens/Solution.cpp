// 题目：2234. 花园的最大总美丽值（Maximum Total Beauty of the Gardens）
// 思路：先排序并求前缀和；枚举最终满园的花园数 x，用二分求剩余花园能被抬到的最大高度 y，取 x*full + y*partial 的最大值。
// 时间复杂度：O(n log n)，排序 O(n log n) 且每个 x 做一次二分；空间复杂度：O(n)，前缀和数组 s。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {  // flowers：各花园现有花朵数；newFlowers：还可新增的花朵总数；target：满园阈值；full/partial：满园与部分美丽值，返回最大总美丽值
        sort(flowers.begin(), flowers.end());  // 升序排序，方便用前缀和与二分统计最小的一批花园
        int n = flowers.size();  // 花园数量
        long long s[n + 1];  // 前缀和数组：s[i] 表示排序后前 i 座花园的花朵总数（VLA，GNU 扩展）
        s[0] = 0;  // 前缀和首项为 0，方便统一递推
        for (int i = 1; i <= n; ++i) {  // 从 1 到 n 递推填表
            s[i] = s[i - 1] + flowers[i - 1];  // 前 i 座之和 = 前 i-1 座之和 + 第 i 座花园（下标 i-1）
        }  // 结束前缀和循环
        long long ans = 0;  // 答案初值：一座花园都不满园时总美丽值为 0
        int i = flowers.end() - lower_bound(flowers.begin(), flowers.end(), target);  // i 是本来就已达标（≥ target）的花园数，这部分花园无需再投入花朵
        for (int x = i; x <= n; ++x) {  // 枚举最终满园的花园数 x，至少为 i，最多 n
            newFlowers -= (x == 0 ? 0 : max(target - flowers[n - x], 0));  // 把第 n-x 座（新纳入满园的最小者）补齐到 target，扣除本次投入；x==0 时无需投入
            if (newFlowers < 0) {  // 花朵不够让更多花园满园
                break;  // x 越大花费越高，后面只会更不可行，直接结束枚举
            }  // 结束可行性判断
            int l = 0, r = n - x - 1;  // 在剩余的 n-x 座花园里二分：需要抬平的前缀右端点区间为 [0, n-x-1]
            while (l < r) {  // 二分找到「把前 mid+1 座抬到 flowers[mid] 仍不超预算」的最大下标
                int mid = (l + r + 1) >> 1;  // 取上中位数，避免 l==mid 时死循环
                if (1LL * flowers[mid] * (mid + 1) - s[mid + 1] <= newFlowers) {  // 把前 mid+1 座都抬到 flowers[mid] 的花费 = flowers[mid]*(mid+1) - 前缀和，判断是否可行
                    l = mid;  // 花费可行，答案至少是 mid，左边界右移
                } else {  // 花费超出剩余花朵
                    r = mid - 1;  // 缩小到左半区间继续找
                }  // 结束二分判定分支
            }  // 结束二分循环
            int y = 0;  // y 表示非满园花园能被抬到的最大高度（决定 partial 部分的价值）
            if (r != -1) {  // r != -1 才有可抬高的花园（r 为 -1 表示一座都抬不动）
                long long cost = 1LL * flowers[l] * (l + 1) - s[l + 1];  // 把前 l+1 座拉平到 flowers[l] 的基础花费
                long long mx = flowers[l] + (newFlowers - cost) / (l + 1);  // 剩余花朵平均分给这 l+1 座，得到它们能共同达到的高度
                long long threshold = target - 1;  // 部分花园必须严格小于 target，否则就该算满园
                y = min(mx, threshold);  // 高度封顶在 target-1
            }  // 结束 y 的计算
            ans = max(ans, 1LL * x * full + 1LL * y * partial);  // 满园 x 座贡献 x*full，非满园部分贡献 y*partial，更新最大总美丽值
        }  // 结束 x 的枚举
        return ans;  // 返回最大总美丽值
    }  // 结束 maximumBeauty 方法
};  // 结束 Solution 类