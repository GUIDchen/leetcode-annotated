// 题目：3185. 构成整天的下标对数目 II（Count Pairs That Form a Complete Day II）
// 思路：与第 I 题完全相同的「余数配对」思路，只需把下标对计数换成 64 位整数以应对更大的数据量。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，桶大小固定为 24。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countCompleteDayPairs(vector<int>& hours) {  // hours：每项任务的耗时，返回相加为 24 整数倍的下标对数目
        int cnt[24]{};  // cnt[r]：已遍历过的耗时中模 24 余 r 的个数（值初始化全 0）
        long long ans = 0;  // 用 64 位整数累加：n 可达 1e5，对数可能超过 int 范围
        for (int x : hours) {  // 从左到右枚举，保证每个下标对只在后一个元素处统计一次
            ans += cnt[(24 - x % 24) % 24];  // 前面需要余数 (24 - x%24) % 24 的元素与它配对，其个数就是新增对数
            ++cnt[x % 24];  // 把当前耗时按余数记入桶，供后面的元素配对
        }  // 遍历结束
        return ans;  // 返回总对数
    }  // 方法结束
};