// 题目：4008. 击败所有怪物的最小初始强度（Minimum Initial Strength to Defeat All Monsters）
// 思路：答案具有单调性（初始强度越大越可行），因此二分答案；用差分数组还原每天的加成，在 O(n) 内判断某个初始强度能否按顺序击败所有怪物。
// 时间复杂度：O(m + n log C)，m 为加成区间数、C = 1e15 为二分范围；空间复杂度：O(n)，差分数组与天数同阶。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minInitialStrength(vector<int>& monsters, vector<vector<int>>& boosts) {  // monsters：每天的怪物强度；boosts：形如 [l, r, v] 的加成区间；返回能通关的最小初始强度
        int n = monsters.size();  // n 为天数，也就是怪物数量
        vector<long long> d(n + 1);  // 差分数组：d[i] 表示第 i 天的加成增量
        for (auto& b : boosts) {  // 把每个加成区间拆成两个差分标记
            d[b[0]] += b[2];  // 区间左端开始享受加成 v
            d[b[1] + 1] -= b[2];  // 区间右端之后撤销加成 v
        }  // 结束加成区间处理

        auto check = [&](long long v) -> bool {  // 可行性判断：初始强度为 v 时能否按顺序击败所有怪物
            long long bonus = 0;  // bonus 记录当前累计生效的加成值
            for (int i = 0; i < n; i++) {  // 逐天推进
                bonus += d[i];  // 前缀和还原出第 i 天的加成
                if (v + bonus < monsters[i]) {  // 当前总强度不足以击败第 i 天的怪物
                    return false;  // 该初始强度不可行
                }  // 结束不足判断
                v -= monsters[i];  // 扣除击败怪物消耗的强度
                if (v < 0) {  // 强度不会被扣成负数
                    v = 0;  // 最低按 0 处理
                }  // 结束归零判断
            }  // 结束逐天推进
            return true;  // 全部怪物都能击败，返回可行
        };  // 结束可行性判断 lambda

        long long left = 0, right = 1000000000000000LL;  // 答案单调，在 [0, 1e15] 上二分最小可行强度
        while (left < right) {  // 二分循环
            long long mid = (left + right) / 2;  // 取中点
            if (check(mid)) {  // mid 可行
                right = mid;  // 尝试更小的强度
            } else {  // mid 不可行
                left = mid + 1;  // 答案至少为 mid + 1
            }  // 结束可行性分支
        }  // 结束二分
        return left;  // left == right，即为最小可行初始强度
    }  // 结束 minInitialStrength
};  // 结束 Solution 类