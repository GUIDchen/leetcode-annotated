// 题目：1477. 找两个和为目标值且不重叠的子数组（Find Two Non-overlapping Sub-arrays Each With Target Sum）
// 思路：前缀和 + 哈希表。d 记录「前缀和 → 最早出现的位置」；f[i] 表示前 i 个元素中长 target 子数组的最短长度。扫到 i 时若存在以 i 结尾的合法子数组，就把它和「它起点之前的最优子数组」拼起来更新答案。
// 时间复杂度：O(n)，每个元素只扫一次；空间复杂度：O(n)，哈希表与 f 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSumOfLengths(vector<int>& arr, int target) {  // arr：输入数组；target：子数组目标和
        unordered_map<int, int> d;  // 哈希表：键是前缀和，值是它第一次出现的位置（前缀下标）
        d[0] = 0;  // 空前缀的和为 0，位置为 0，方便处理从下标 0 开始的子数组
        int s = 0, n = arr.size();  // s：当前前缀和；n：数组长度
        int f[n + 1];  // f[i]：只考虑前 i 个元素时，和为 target 的最短子数组长度
        const int inf = 1 << 30;  // 用一个足够大的数表示「不存在」
        f[0] = inf;  // 前 0 个元素里不可能有合法子数组
        int ans = inf;  // 两个子数组长度之和的最小值，初值为无穷大
        for (int i = 1; i <= n; ++i) {  // i 是前缀下标，对应原数组的第 i 个元素
            int v = arr[i - 1];  // 当前元素
            s += v;  // 累加得到前缀和
            f[i] = f[i - 1];  // 先继承「不选以 i 结尾的子数组」时的最优长度
            if (d.count(s - target)) {  // 若之前出现过前缀和 s - target，说明存在以 i 结尾、和为 target 的子数组
                int j = d[s - target];  // j 是该子数组起点的前缀下标
                f[i] = min(f[i], i - j);  // 更新前缀最优长度：取更短的那个
                ans = min(ans, f[j] + i - j);  // 用「j 之前的最优子数组」加上「当前子数组」拼出不重叠的两段
            }
            d[s] = i;  // 记录当前前缀和出现的位置（后出现的位置覆盖前面的，保证子数组尽量短）
        }
        return ans > n ? -1 : ans;  // 答案超过数组长度说明没找到两段，返回 -1
    }
};