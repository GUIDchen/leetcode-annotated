// 题目：3180. 执行操作可获得的最大总奖励 I（Maximum Total Reward Using Operations I）
// 思路：排序后记忆化搜索。设当前已累计总奖励为 x，则只能挑选大于 x 的奖励值 v，得到 x+v 并继续递归，f[x] 记录该状态的最优解。
// 时间复杂度：O(n * maxV)，每个状态下扫描可选的更大值；空间复杂度：O(maxV)，记忆化数组大小为 2*最大值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxTotalReward(vector<int>& rewardValues) {  // rewardValues：可选的奖励值集合
        sort(rewardValues.begin(), rewardValues.end());  // 排序后才能用 upper_bound 只挑「严格大于当前总奖励」的值
        int n = rewardValues.size();  // 记录奖励值个数
        int f[rewardValues.back() << 1];  // 记忆化数组：总奖励最大不会超过 2*最大值，用左移 1 位代替乘 2
        memset(f, -1, sizeof(f));  // 置 -1 表示该状态尚未计算过
        function<int(int)> dfs = [&](int x) {  // x 表示当前已经累计的总奖励
            if (f[x] != -1) {  // 该状态已经算过，直接返回记忆值，避免重复搜索
                return f[x];  // 返回缓存的最优结果
            }
            auto it = upper_bound(rewardValues.begin(), rewardValues.end(), x);  // 找到第一个严格大于 x 的位置，只有这些值才允许选
            int ans = 0;  // 当前状态下能获得的额外奖励，先假设一个都不选
            for (; it != rewardValues.end(); ++it) {  // 枚举所有可以选的奖励值
                ans = max(ans, rewardValues[it - rewardValues.begin()] + dfs(x + *it));  // 选它并递归，取下标就是迭代器相对首元素的偏移
            }
            return f[x] = ans;  // 结果写入记忆数组后再返回
        };
        return dfs(0);  // 从总奖励 0 出发搜索，返回最大总奖励
    }
};