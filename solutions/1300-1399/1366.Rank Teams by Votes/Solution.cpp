// 题目：1366. 通过投票对团队排名（Rank Teams by Votes）
// 思路：统计每个队伍在每个名次上的票数，按名次依次比较票数降序排序，所有名次票数都相同时按字母升序。
// 时间复杂度：O(V·m + 26·m·log26)；空间复杂度：O(26·m)，计数表 cnt。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string rankTeams(vector<string>& votes) {  // votes：每张选票都是所有队伍的一个排名序列
        int m = votes[0].size();  // m 是队伍（也是名次）的数量
        array<array<int, 27>, 26> cnt{};  // cnt[c][k] 表示队伍 c 获得第 k 名的票数，初始全 0

        for (const auto& vote : votes) {  // 逐张选票统计
            for (int i = 0; i < m; ++i) {  // 逐个名次统计
                ++cnt[vote[i] - 'A'][i];  // 该名次上对应队伍的票数加一
            }  // 名次循环结束
        }  // 选票循环结束
        string s = votes[0];  // 待排序的队伍集合（所有队伍都出现在第一张选票里）
        ranges::sort(s, [&](char a, char b) {  // 按自定义比较器排序：先比第 0 名票数，再比第 1 名……
            int i = a - 'A', j = b - 'A';  // a、b 两个队伍的编号（0~25）
            for (int k = 0; k < m; ++k) {  // 依次比较每个名次上的票数
                if (cnt[i][k] != cnt[j][k]) {  // 一旦某个名次票数不同
                    return cnt[i][k] > cnt[j][k];  // 票数多者排在前面
                }  // if 结束
            }  // 名次循环结束
            return a < b;  // 所有名次票数都相同，按字母升序打破平局
        });  // 比较器结束
        return string(s.begin(), s.end());  // 转成 string 返回（此时 s 已按票数降序排好）
    }  // 方法结束
};  // 类定义结束
