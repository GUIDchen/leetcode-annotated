// 题目：2244. 完成所有任务需要的最少轮数（Minimum Rounds to Complete All Tasks）
// 思路：统计每个难度等级出现的次数；每轮只能做 2 或 3 个同难度任务，所以次数为 1 时无解，否则用「先尽量取 3 个、余数再补一轮」计算轮数。
// 时间复杂度：O(n)，n 为任务数，哈希表统计与遍历都是线性；空间复杂度：O(n)，最坏情况下每个任务一个不同难度。
class Solution {  // LeetCode 约定的题解类
public:  // 对外提供的解法接口
    int minimumRounds(vector<int>& tasks) {  // tasks 中每个元素表示一个任务的难度等级
        unordered_map<int, int> cnt;  // 哈希表：难度等级 → 该等级的任务个数
        for (auto& t : tasks) {  // 遍历所有任务
            ++cnt[t];  // 对应难度的计数加一
        }
        int ans = 0;  // 记录需要的总轮数
        for (auto& [_, v] : cnt) {  // C++17 结构化绑定：_ 为难度（此处不用），v 为出现次数
            if (v == 1) {  // 只剩 1 个任务时凑不出每轮 2 或 3 个，必然做不完
                return -1;  // 按题意返回 -1
            }
            ans += v / 3 + (v % 3 != 0);  // 每轮尽量做 3 个；余 1 或余 2 时再多做一轮即可覆盖
        }
        return ans;  // 返回最少轮数
    }
};