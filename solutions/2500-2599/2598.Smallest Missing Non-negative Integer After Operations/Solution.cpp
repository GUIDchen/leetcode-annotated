// 题目：2598. 执行操作后的最大 MEX（Smallest Missing Non-negative Integer After Operations）
// 思路：每个元素只能按 value 的整数倍增减，所以真正决定能否凑出某数的是它对 value 的余数；统计余数桶后从 0 起逐个消耗。
// 时间复杂度：O(n + m)，m 为答案大小且不超过 n；空间复杂度：O(value)，需要一个长度 value 的余数桶。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findSmallestInteger(vector<int>& nums, int value) {  // nums：可反复加减 value 的数组；value：每次操作的步长；返回能得到的最小缺失非负整数（MEX）
        int cnt[value];  // 按 value 取模的余数桶：cnt[r] 统计余数为 r 的元素个数
        memset(cnt, 0, sizeof(cnt));  // memset 把桶数组全部清零，作为统计起点
        for (int x : nums) {  // 逐个元素归类到它对应的余数桶
            ++cnt[(x % value + value) % value];  // C++ 的 % 对负数可能得负值，先加 value 再取模，保证下标落在 [0, value)
        }  // 本轮元素统计结束
        for (int i = 0;; ++i) {  // 从 0 开始试探每个非负整数能否被凑出来
            if (cnt[i % value]-- == 0) {  // 先比较再自减：该余数桶已空说明凑不出 i；否则消耗掉一个配额表示 i 被占用
                return i;  // 第一个凑不出的整数就是 MEX
            }  // 该整数可以凑出，继续试下一个
        }  // 无限循环体结束（找到答案时由 return 跳出）
    }  // 方法体结束
};