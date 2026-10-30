// 题目：1943. 描述绘画结果（Describe the Painting）
// 思路：差分数组配合有序 map：每段在 l 处加 c、在 r 处减 c；按坐标扫描并累加差分值，相邻坐标形成一个区间，颜色和为正的区间就是答案。
// 时间复杂度：O(n log n)，map 插入与遍历；空间复杂度：O(n)，差分表至多 2n 个键。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {  // segments：每段画的 (起点, 终点, 颜色值)
        map<int, long long> d;  // 差分表：键是坐标，值是该坐标处的颜色变化量；map 中键自动按升序排列
        for (auto& e : segments) {  // 遍历每一段画线
            int l = e[0], r = e[1], c = e[2];  // 取出左端点 l、右端点 r 与颜色值 c
            d[l] += c;  // 左端点处 +c：从这里开始叠加 c；同一坐标会自然累加
            d[r] -= c;  // 右端点处 -c：到这里这段画的颜色被撤销
        }
        vector<vector<long long>> ans;  // 答案数组，每项是 (区间左端, 区间右端, 该区间的混合颜色)
        long long i, j, cur = 0;  // cur 是扫到当前坐标时的颜色累计值；i 是上一个坐标（区间左端），j 是当前坐标
        for (auto& it : d) {  // 按坐标从小到大扫描差分表
            if (it == *d.begin())  // 第一个坐标只用于初始化区间左端，没有「上一区间」需要输出
                i = it.first;  // 把最小坐标记为区间左端 i
            else {  // 其余坐标 j 都构成一个左闭右开区间 [i, j)
                j = it.first;  // 当前坐标作为下一个区间的左端
                if (cur > 0) ans.push_back({i, j, cur});  // 区间颜色和为正才输出（为 0 说明这段没有画过）
                i = j;  // 区间收尾，把 j 作为新区间的左端
            }
            cur += it.second;  // 累加当前坐标的差分值，得到区间 [j, 下一个坐标) 的颜色和
        }
        return ans;  // 返回所有颜色和为正的区间描述
    }
};