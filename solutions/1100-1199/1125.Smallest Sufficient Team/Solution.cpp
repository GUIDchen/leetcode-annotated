// 题目：1125. 最小的必要团队（Smallest Sufficient Team）
// 思路：把 m 个技能压成二进制掩码，先算出每个人掌握的技能掩码，再做状压 DP：f[mask] 表示覆盖技能集合 mask 所需的最少人数，用 g/h 数组分别记录「最后加入的人」和「前驱状态」，最后从满集合沿前驱回溯出团队名单。
// 时间复杂度：O(2^m · n)，共有 2^m 个状态、每个状态枚举 n 个人；空间复杂度 O(2^m)，需要三张大小为 2^m 的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {  // req_skills：必需技能；people：每人掌握的技能；返回最少人数团队
        unordered_map<string, int> d;  // d：技能名 → 位编号，便于把技能集合压成二进制掩码
        int m = req_skills.size(), n = people.size();  // m：必需技能数；n：候选人数
        for (int i = 0; i < m; ++i) {  // 给每个必需技能分配一个二进制位
            d[req_skills[i]] = i;  // 技能名映射到编号 i
        }  // 建表循环结束
        int p[n];  // p[i]：第 i 个人掌握的技能集合掩码
        memset(p, 0, sizeof(p));  // 初始清零，表示尚未掌握任何技能
        for (int i = 0; i < n; ++i) {  // 逐个计算每个人的技能掩码
            for (auto& s : people[i]) {  // 遍历这个人掌握的每个技能
                p[i] |= 1 << d[s];  // 把该技能对应的位或进掩码
            }  // 内层循环结束
        }  // 外层循环结束
        int f[1 << m];  // f[mask]：覆盖技能集合 mask 所需的最少人数
        int g[1 << m];  // g[mask]：转移到 mask 时最后加入的人
        int h[1 << m];  // h[mask]：转移前的前驱状态，用于回溯出具体人选
        memset(f, 63, sizeof(f));  // 把 f 的每个字节置为 0x3f，即初值 0x3f3f3f3f 表示不可达
        f[0] = 0;  // 空集合不需要任何人
        for (int i = 0; i < 1 << m; ++i) {  // 枚举所有技能集合作为转移起点
            if (f[i] == 0x3f3f3f3f) {  // 不可达状态无法继续转移，直接跳过
                continue;  // 跳过本状态
            }  // if 分支结束
            for (int j = 0; j < n; ++j) {  // 尝试让第 j 个人加入团队
                if (f[i] + 1 < f[i | p[j]]) {  // 人数更少才更新，保证 f 取到最小值
                    f[i | p[j]] = f[i] + 1;  // 记录新集合所需的最少人数
                    g[i | p[j]] = j;  // 记录本次加入的人
                    h[i | p[j]] = i;  // 记录前驱集合，供回溯使用
                }  // if 分支结束
            }  // 内层循环结束
        }  // 外层循环结束
        vector<int> ans;  // 收集最终人选
        for (int i = (1 << m) - 1; i; i = h[i]) {  // 从满集合出发沿前驱回溯，直到空集合（i 为 0 时停止）
            ans.push_back(g[i]);  // 把该集合最后加入的人放入答案
        }  // 回溯循环结束
        return ans;  // 返回人数最少的团队成员下标列表
    }  // 方法结束
};  // 类定义结束