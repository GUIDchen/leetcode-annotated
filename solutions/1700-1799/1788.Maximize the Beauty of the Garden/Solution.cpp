// 题目：1788. 最大化花园的美观度（Maximize the Beauty of the Garden）
// 思路：可采的花必须形如 flowers[i] + flowers[j] 加中间正数区间；用前缀和只累加正值，并记录每种花第一次出现的下标，枚举右端点时用 map 找同种花的首次出现位置。
// 时间复杂度：O(n)，哈希表查询均摊 O(1)；空间复杂度：O(n)，前缀和与首次出现位置表。
class Solution {
public:
    int maximumBeauty(vector<int>& flowers) {  // 主函数：返回能获得的最大美观度
        int n = flowers.size();  // 花园里花的总数
        vector<int> s(n + 1);  // 前缀和：s[i] 表示前 i 朵花中所有正数的和（负值花不采，故不计入）
        unordered_map<int, int> d;  // 记录每种花值第一次出现的下标，供后面配对同一数值
        int ans = INT_MIN;  // 答案初始化为最小整数，保证任何合法方案作为候选时都能被 max 更新到
        for (int i = 0; i < n; ++i) {  // 从左到右枚举区间的右端点 i
            int v = flowers[i];  // 当前这朵花的值
            if (d.count(v)) {  // 若这种花之前出现过，说明可以把它当作区间两端
                ans = max(ans, s[i] - s[d[v] + 1] + v * 2);  // 美观度 = 两端各一次 v（共 2v）加上区间内部所有正数之和；内部用前缀和差分得到
            } else {  // 否则这是第一次遇到这种花
                d[v] = i;  // 记下它第一次出现的下标，之后再用同样的值配对
            }
            s[i + 1] = s[i] + max(v, 0);  // 更新前缀和：只累加正数，负值花选择不采，贡献为 0
        }
        return ans;  // 返回最大美观度
    }
};  // 题解类定义结束