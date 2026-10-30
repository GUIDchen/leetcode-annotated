// 题目：2025. 分割数组的最多方案数（Maximum Number of Ways to Partition an Array）
// 思路：先算前缀和并把所有前缀和计入「右侧」哈希表；枚举把每个元素换成 k，用「新总和的一半」去左右两张表里查划分点个数，边走边把当前前缀和从右表挪到左表。
// 时间复杂度：O(n)，两次线性扫描加 O(1) 哈希查询；空间复杂度：O(n)，前缀和数组与两张哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int waysToPartition(vector<int>& nums, int k) {  // nums：原数组；k：唯一允许把某个元素替换成的值；返回划分方案数的最大值
        int n = nums.size();  // 数组长度，后面所有循环上界与下标都基于它
        long long s[n];  // 前缀和数组：s[i] = nums[0] + ... + nums[i]，用 long long 防止累加溢出
        s[0] = nums[0];  // 前缀和的第一项就是首元素本身
        unordered_map<long long, int> right;  // right：前缀和频次表，用来 O(1) 得到「划分点落在当前位置右侧」的方案数
        for (int i = 0; i < n - 1; ++i) {  // 先扫一遍，把右侧所有可作划分点前缀和的取值都统计进 right
            right[s[i]]++;  // s[i] 即划分点 i 的左侧和，先算作右侧候选
            s[i + 1] = s[i] + nums[i + 1];  // 顺推下一项前缀和
        }  // 前缀和与右侧频次表构造完毕
        int ans = 0;  // 答案初值：一个元素都不替换时的最大划分方案数
        if (s[n - 1] % 2 == 0) {  // 总和为偶数才可能被平分成两半，否则不存在合法划分
            ans = right[s[n - 1] / 2];  // 不替换时，划分点左侧和恰为总和一半的方案数就是答案
        }  // 不替换元素的基线统计结束
        unordered_map<long long, int> left;  // left：左侧前缀和频次表，随遍历逐步扩大
        for (int i = 0; i < n; ++i) {  // 枚举把下标 i 的元素替换为 k（LeetCode 规定只能替换一个元素）
            int d = k - nums[i];  // d：替换之后数组总和的增量
            if ((s[n - 1] + d) % 2 == 0) {  // 新总和为偶数，才可能分成左右和相等的两半
                int t = left[(s[n - 1] + d) / 2] + right[(s[n - 1] - d) / 2];  // 划分点在 i 的左边 / 右边两种情形，分别到 left、right 中查表并相加
                ans = max(ans, t);  // 用本次替换得到的方案数刷新答案
            }  // 新总和为奇数，本次替换不可能产生划分
            left[s[i]]++;  // 划分点右移到 i 之后，s[i] 从此归入左侧频次表
            right[s[i]]--;  // 同时从右侧频次表扣掉，避免同一个划分点被两边重复统计
        }  // 所有可替换位置枚举完毕
        return ans;  // 返回最大划分方案数
    }  // 方法结束
};  // 类定义结束