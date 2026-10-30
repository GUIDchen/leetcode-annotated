// 3824. Minimum K to Reduce Array Within Limit | 3824. 减小数组使其满足条件的最小 K 值
// 核心思路：nonPositive(nums, k) = Σ⌈x/k⌉，随 k 增大而单调可行，故在 [1, 1e5] 上二分最小可行 k
// 复杂度：时间 O(n log 1e5)，空间 O(1)
class Solution {
public:
    int minimumK(vector<int>& nums) {  // 求满足操作次数 <= k*k 的最小 k
        auto check = [&](int k) -> bool {  // 判断给定的 k 是否可行
            long long t = 0;  // 累计把全部元素降到非正所需的总操作次数
            for (int x : nums) {  // 遍历数组的每个元素
                t += (x + k - 1) / k;  // 元素 x 每次减 k，需要 ⌈x/k⌉ 次（整数向上取整写法）
            }
            return t <= 1LL * k * k;  // 总次数不超过 k 的平方即为可行
        };

        int l = 1, r = 1e5;  // 二分区间：k 至少为 1，上界取 1e5
        while (l < r) {  // 二分查找最小的可行 k
            int mid = (l + r) >> 1;  // 取区间中点（等价于下取整的 (l+r)/2）
            if (check(mid)) {  // 中点可行
                r = mid;  // 答案不会超过 mid，收缩右边界
            } else {  // 中点不可行
                l = mid + 1;  // 答案必然大于 mid，抬高左边界
            }
        }
        return l;  // 循环结束时 l 即最小可行 k
    }
};
