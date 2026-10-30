// 题目：2040. 两个有序数组的第 K 小乘积（Kth Smallest Product of Two Sorted Arrays）
// 思路：二分答案 p，用 count(p) 统计乘积不超过 p 的数对个数；nums2 有序，对每个 nums1 元素按符号用二分定位分界点，再以 count(p) ≥ k 收缩上下界。
// 时间复杂度：O(m log n log(M))，m、n 为两数组长度、M 为值域，空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {  // nums1、nums2：两个升序数组；k：第 k 小（从 1 开始）
        int m = nums1.size(), n = nums2.size();  // m、n：两个数组的长度
        int a = max(abs(nums1[0]), abs(nums1[m - 1]));  // a：nums1 中绝对值最大的元素（有序数组，绝对值最大者必在两端）
        int b = max(abs(nums2[0]), abs(nums2[n - 1]));  // b：nums2 中绝对值最大的元素
        long long r = 1LL * a * b;  // r：可能的最大乘积，作为二分上界
        long long l = -r;  // l：对称的最小乘积，作为二分下界
        auto count = [&](long long p) {  // count(p)：统计乘积不超过 p 的数对个数（lambda 按引用捕获两个数组）
            long long cnt = 0;  // cnt：数对个数累加器
            for (int x : nums1) {  // 枚举 nums1 的每个元素
                if (x > 0) {  // x 为正数时，乘积随 nums2 单调递增
                    int l = 0, r = n;  // 在 [0, n) 上二分第一个使 x*nums2[mid] 大于 p 的位置
                    while (l < r) {  // 二分区间左闭右开
                        int mid = (l + r) >> 1;  // 取中点，用移位代替除法
                        if (1LL * x * nums2[mid] > p) {  // mid 处乘积已超过 p
                            r = mid;  // 分界点落在左半段
                        } else {  // mid 处乘积仍不超过 p
                            l = mid + 1;  // 分界点落在右半段
                        }
                    }
                    cnt += l;  // 分界点之前共 l 个元素的乘积都不超过 p
                } else if (x < 0) {  // x 为负数时，乘积随 nums2 单调递减
                    int l = 0, r = n;  // 同样在 [0, n) 上二分第一个使 x*nums2[mid] 不超过 p 的位置
                    while (l < r) {  // 二分区间左闭右开
                        int mid = (l + r) >> 1;  // 取中点
                        if (1LL * x * nums2[mid] <= p) {  // mid 处乘积已满足不超过 p
                            r = mid;  // 分界点落在左半段
                        } else {
                            l = mid + 1;  // mid 处乘积仍大于 p
                        }  // else 分支结束，继续下一轮二分
                    }
                    cnt += n - l;  // 从 l 到末尾共 n-l 个元素的乘积都不超过 p
                } else if (p >= 0) {  // x 为 0：所有乘积都是 0，只有 p 不为负时才计入
                    cnt += n;  // n 个乘积 0 全部计入
                }
            }
            return cnt;  // 返回乘积不超过 p 的数对总数
        };
        while (l < r) {  // 在值域上二分第 k 小的乘积
            long long mid = (l + r) >> 1;  // 取中点值，用移位代替除法
            if (count(mid) >= k) {  // 至少 k 个数对不超过 mid，说明答案不大于 mid
                r = mid;  // 答案落在左半段（含 mid）
            } else {
                l = mid + 1;  // 不足 k 个，答案落在右半段
            }
        }
        return l;  // l 收敛到最小的满足 count(l) ≥ k 的值，正是第 k 小乘积
    }
};