// 题目：3371. 识别数组中的最大异常值（Identify the Largest Outlier in an Array）
// 思路：先求总和 s 与每个值的出现次数；假设 x 是异常值，则其余元素之和 t=s-x，其中必须有元素等于 t/2，再取满足条件的最大 x。
// 时间复杂度：O(n)，统计与枚举哈希表各一趟；空间复杂度：O(n)，哈希表最多存 n 个不同值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getLargestOutlier(vector<int>& nums) {  // nums 是输入数组，返回其中最大的异常值
        int s = 0;  // s 记录整个数组的元素之和
        unordered_map<int, int> cnt;  // 哈希表：键是元素值，值是它出现的次数
        for (int x : nums) {  // 第一趟遍历：同时统计总和与每个值的频次
            s += x;  // 把当前元素累加进总和
            cnt[x]++;  // 当前值的出现次数加一
        }  // 求和与计数完成
        int ans = INT_MIN;  // 答案先置为最小整数，便于后面取最大值
        for (auto [x, v] : cnt) {  // 枚举每个不同的值 x，假设它就是异常值
            int t = s - x;  // t 是去掉 x 之后其余元素之和
            if (t % 2 || !cnt.contains(t / 2)) {  // t 必须是偶数，并且 t/2 这个「其余元素之和」要真的存在于数组中
                continue;  // 该候选不成立，跳过
            }  // t/2 不能与 x 是同一个数（否则 x 至少要出现两次）
            if (x != t / 2 || v > 1) {  // 更新更大的可行异常值
                ans = max(ans, x);  // 枚举结束，ans 就是最大异常值
            }  // 题目保证存在异常值，直接返回
        }  // 方法结束
        return ans;  // 题解类定义结束
    }
};
