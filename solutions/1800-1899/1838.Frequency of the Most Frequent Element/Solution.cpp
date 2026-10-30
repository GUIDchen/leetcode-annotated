// 题目：1838. 最高频元素的频数（Frequency of the Most Frequent Element）
// 思路：先排序并求前缀和，再二分答案 m：把连续 m 个数全提升到其中最大值 nums[i-1] 的代价是 nums[i-1]*m 减区间和，若存在代价不超过 k 的窗口则 m 可行。
// 时间复杂度：O(n log n)，排序一次加二分 O(log n) 层、每层校验 O(n)；空间复杂度：O(n)，前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxFrequency(vector<int>& nums, int k) {  // nums 是可自增的数组，k 是可用增量总和，返回最高频元素能达到的最大频数
        int n = nums.size();  // 数组长度
        sort(nums.begin(), nums.end());  // 先排序：最终被提升成同一个值的那批元素，在有序数组中必然连续
        long long s[n + 1];  // 前缀和数组，s[i] 表示前 i 个元素之和；用 long long 防止累加溢出
        s[0] = 0;  // 空前缀和为 0
        for (int i = 1; i <= n; ++i) {  // 逐个元素累加，构造前缀和
            s[i] = s[i - 1] + nums[i - 1];  // s[i] 等于前 i 个元素之和
        }  // 前缀和构造完毕
        int l = 1, r = n;  // 答案二分区间：频数最小为 1，最大为 n
        auto check = [&](int m) {  // 判定函数：是否存在长度 m 的窗口，能靠不超过 k 的增量全部变成窗口最大值
            for (int i = m; i <= n; ++i) {  // 枚举窗口右端点 i，窗口即 nums[i-m .. i-1]
                if (1LL * nums[i - 1] * m - (s[i] - s[i - m]) <= k) {  // 全提升到 nums[i-1] 的代价 = 最大值乘 m 减窗口和，1LL 保证乘法不溢出
                    return true;  // 找到可行窗口，说明频数 m 可以达到
                }  // if 结束
            }  // 枚举完所有窗口
            return false;  // 没有任何窗口可行，频数 m 达不到
        };  // lambda 定义结束
        while (l < r) {  // 二分查找最大的可行 m
            int mid = (l + r + 1) >> 1;  // 向上取整的中点，配合下面的 l = mid 才不会死循环
            if (check(mid)) {  // 检查中点是否可行
                l = mid;  // 可行则保留 mid，继续在右半区间找更大的
            } else {  // 否则中点不可行
                r = mid - 1;  // 不可行则把区间右端左缩
            }  // 二分结束
        }  // 方法结束
        return l;  // 返回最大可行频数
    }  // 方法结束
};  // 类定义结束