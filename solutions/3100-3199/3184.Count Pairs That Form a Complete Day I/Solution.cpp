// 题目：3184. 构成整天的下标对数目 I（Count Pairs That Form a Complete Day I）
// 思路：只关心耗时模 24 的余数，用长度 24 的桶记录已出现过的余数，遍历时查询补数余数的个数并累加。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，桶大小固定为 24。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countCompleteDayPairs(vector<int>& hours) {  // hours：每项任务的耗时，返回相加为 24 整数倍的下标对数目
        int cnt[24]{};  // cnt[r]：已遍历过的耗时中，模 24 余 r 的个数（值初始化全 0）
        int ans = 0;  // 满足条件的下标对总数
        for (int x : hours) {  // 从左到右枚举，保证每个下标对只在后一个元素处统计一次
            ans += cnt[(24 - x % 24) % 24];  // 前面需要有余数 (24 - x%24) % 24 的元素与它配对，其个数就是新增对数
            ++cnt[x % 24];  // 把当前耗时按余数记入桶，供后面的元素配对
        }  // 遍历结束
        return ans;  // 返回总数
    }  // 方法结束
};