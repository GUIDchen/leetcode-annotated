// 题目：1711. 大餐计数（Count Good Meals）
// 思路：遍历时用哈希表记录此前各美味值出现的次数；对当前值 d 枚举所有不超过「最大值两倍」的 2 的幂 s，累加 cnt[s-d]，即以 d 为较大下标的所有美味配对。
// 时间复杂度：O(n log M)，M 为最大美味值，枚举的 2 的幂约 21 个；空间复杂度：O(n)，哈希表保存不同美味值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int mod = 1e9 + 7;  // 结果取模的常数

    int countPairs(vector<int>& deliciousness) {  // deliciousness：每道菜的美味程度数组
        int mx = *max_element(deliciousness.begin(), deliciousness.end()) << 1;  // 两数之和的上界是最大值的两倍，超过它的 2 的幂不可能被凑出
        unordered_map<int, int> cnt;  // 哈希表：记录已经遍历过的每个美味值出现了多少次
        int ans = 0;  // 满足「和为 2 的幂」的配对数
        for (auto& d : deliciousness) {  // 逐个取当前美味值 d，在它之前出现过的元素中物色搭档
            for (int s = 1; s <= mx; s <<= 1) {  // 枚举所有不超过上界的 2 的幂作为目标和
                ans = (ans + cnt[s - d]) % mod;  // 需要的搭档是 s-d，把它此前出现的次数累加进答案并取模
            }  // 本个 2 的幂处理结束
            ++cnt[d];  // 把当前值计入哈希表，供后面的元素统计配对
        }  // 本轮处理结束
        return ans;  // 返回配对总数
    }  // 方法结束
};  // 类定义结束