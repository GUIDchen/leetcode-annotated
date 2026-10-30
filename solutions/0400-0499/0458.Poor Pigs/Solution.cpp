// 题目：458. 可怜的小猪（Poor Pigs）
// 思路：每头猪有「轮数+1」种状态（轮数 = minutesToTest/minutesToDie），n 头猪最多区分 base^n 个桶，求最小 n 使 base^n ≥ buckets。
// 时间复杂度：O(log_base buckets)，倍增次数即答案；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {  // buckets：桶数；minutesToDie：猪中毒后死亡所需时间；minutesToTest：总测试时间
        int base = minutesToTest / minutesToDie + 1;  // base = 每头猪的状态数 = 可测试轮数 + 1（多出的 1 表示始终不死的情况）
        int res = 0;  // res 记录所需猪的头数
        for (int p = 1; p < buckets; p *= base) ++res;  // 每增加一头猪，能区分的桶数乘以 base；p 从 1 开始倍增，直到覆盖全部 buckets
        return res;  // 返回最少需要的猪数
    }
};