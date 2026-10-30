// 题目：2212. 射箭比赛中的最大得分（Maximum Points in an Archery Competition）
// 思路：二进制枚举 Bob 想赢下的靶环集合，每环只需比 Alice 多一箭，箭数够用就更新最高分；剩余箭全部塞进 0 环。
// 时间复杂度：O(2^m * m)，m 为靶环数（本题 12）；空间复杂度：O(m)，用于保存答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {  // numArrows：Bob 的箭数；aliceArrows[i]：Alice 在第 i 环射出的箭数
        int st = 0, mx = 0;  // st：最优方案要赢下的环集合（位掩码），mx：该方案的总得分
        int m = aliceArrows.size();  // m：靶环数量，本题固定为 12
        for (int mask = 1; mask < 1 << m; ++mask) {  // 枚举所有非空的环集合，第 i 位为 1 表示要赢下第 i 环
            int cnt = 0, s = 0;  // cnt：该方案消耗的箭数；s：该方案得到的总分
            for (int i = 0; i < m; ++i) {  // 逐环检查是否被选入集合
                if (mask >> i & 1) {  // 第 i 环被选中
                    s += i;  // 赢下第 i 环即可得到 i 分
                    cnt += aliceArrows[i] + 1;  // 只需比 Alice 多射一箭就能拿下该环
                }
            }
            if (cnt <= numArrows && s > mx) {  // 箭数够用且得分严格更高，才更新最优解
                mx = s;  // 记录当前最高得分
                st = mask;  // 记录取得该得分的环集合
            }
        }
        vector<int> ans(m);  // 按最优环集合构造 Bob 的出箭方案，初始每环都是 0 箭
        for (int i = 0; i < m; ++i) {  // 逐环分配箭数
            if (st >> i & 1) {  // 该环在最优方案中要赢下
                ans[i] = aliceArrows[i] + 1;  // 比 Alice 多射一箭
                numArrows -= ans[i];  // 扣掉这一环已经用掉的箭
            }
        }
        ans[0] += numArrows;  // 没用完的箭全部放到 0 环，0 环本来就得 0 分，不影响总分
        return ans;  // 返回 Bob 每个环射出的箭数
    }
};
