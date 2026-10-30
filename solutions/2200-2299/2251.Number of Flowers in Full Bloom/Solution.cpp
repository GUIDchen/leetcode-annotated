// 题目：2251. 花期内花的数目（Number of Flowers in Full Bloom）
// 思路：把开花时间与凋谢时间分别排序；对每个人，正在开花的数量 = 开花时间 ≤ 当天的花数 − 凋谢时间 < 当天的花数。
// 时间复杂度：O((n + m) log n)，n 为花的数量、m 为人数；空间复杂度：O(n)，两个时间数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {  // flowers 每项是 [开花时间, 凋谢时间]，people 是每个人的到达时间
        int n = flowers.size();  // 花的数量，用于说明规模（后续只用到 push_back）
        vector<int> start;  // start：所有花的开花时间
        vector<int> end;  // end：所有花的凋谢时间
        for (auto& f : flowers) {  // 遍历每朵花，把它的开花、凋谢时间分别拆出来
            start.push_back(f[0]);  // 收集开花时间 f[0]
            end.push_back(f[1]);  // 收集凋谢时间 f[1]
        }  // 结束收集
        sort(start.begin(), start.end());  // 开花时间升序排序，之后才能二分
        sort(end.begin(), end.end());  // 凋谢时间升序排序，之后才能二分
        vector<int> ans;  // ans：每个人看到的花的数目，顺序与 people 一致
        for (auto& p : people) {  // 依次处理每个人的到达时间 p
            auto r = upper_bound(start.begin(), start.end(), p) - start.begin();  // upper_bound 找第一个 > p 的位置，其下标即「开花时间 ≤ p」的花数
            auto l = lower_bound(end.begin(), end.end(), p) - end.begin();  // lower_bound 找第一个 ≥ p 的位置，其下标即「凋谢时间 < p」的花数（这些花已谢）
            ans.push_back(r - l);  // 已开的花数减去已谢的花数，就是当天正在开的花数
        }  // 结束人的遍历
        return ans;  // 按到达顺序返回每个人的答案
    }  // 结束题解方法
};  // 结束题解类