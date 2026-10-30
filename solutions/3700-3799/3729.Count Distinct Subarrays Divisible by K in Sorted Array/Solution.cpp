// 3729. 统计有序数组中可被 K 整除的子数组数量 / Count Distinct Subarrays Divisible by K in Sorted Array
// 核心思路：先用前缀和取模统计所有元素和能被 k 整除的子数组，再按连续相同元素分组，扣掉完全由等值元素组成、与其他位置重复的计数。
// 复杂度：时间 O(n + 各组长度之和) = O(n)，空间 O(min(n, k))。
class Solution {  // 定义 LeetCode 解法类
public:  // 公有接口
    long long numGoodSubarrays(vector<int>& nums, int k) {  // 返回元素互不相同且元素和能被 k 整除的子数组数量
        long long ans = 0;  // 答案计数，用 long long 防止溢出
        int s = 0;  // 前缀和模 k 的余数
        unordered_map<int, int> cnt;  // 记录每个前缀余数此前出现的次数
        cnt[0] = 1;  // 空前缀的余数为 0，先放入一个哨兵
        for (int x : nums) {  // 遍历有序数组中的每个元素
            s = (s + x) % k;  // 更新前缀和余数
            ans += cnt[s]++;  // 以当前位置结尾、与前面余数相同的子数组之和都是 k 的倍数
        }  // 余数计数加一，供后续位置使用
        int n = nums.size();  // 数组长度
        for (int i = 0; i < n;) {  // i 指向当前相同元素分组的起点
            int j = i + 1;  // 组内扫描指针从 i 的下一位置开始
            while (j < n && nums[j] == nums[i]) {  // 向右扩展，直到元素值与 nums[i] 不同
                ++j;  // 指针右移
            }  // 循环结束时区间 [i, j) 内元素完全相同
            int m = j - i;  // 本组相同元素的个数
            for (int h = 1; h <= m; ++h) {  // 枚举从本组中取出的元素个数 h
                if (1LL * nums[i] * h % k == 0) {  // 这 h 个相同元素之和能被 k 整除
                    ans -= (m - h);  // 这些子数组只由等值元素构成，同样的值在别处已被统计过，故只保留一份
                }  // 分支结束
            }  // 枚举结束
            i = j;  // 跳到下一个分组
        }  // 分组处理结束
        return ans;  // 返回去重后的答案
    }  // 方法结束
};  // 类定义结束
