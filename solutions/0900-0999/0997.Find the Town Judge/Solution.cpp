// 题目：997. 找到小镇的法官（Find the Town Judge）
// 思路：把信任关系看成有向边，法官必须是出度为 0（不信任任何人）且入度为 n-1（被其余所有人信任）的那个点。
// 时间复杂度：O(n + m)，m 为 trust 长度；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findJudge(int n, vector<vector<int>>& trust) {  // n 是小镇人数（编号 1..n）；trust[i] = [a, b] 表示 a 信任 b
        vector<int> cnt1(n + 1);  // cnt1[i]：i 信任了多少人（出度），下标 0 空置
        vector<int> cnt2(n + 1);  // cnt2[i]：有多少人信任 i（入度）
        for (auto& t : trust) {  // 遍历每一条信任关系
            int a = t[0], b = t[1];  // 拆出这条边的起点 a 与终点 b
            ++cnt1[a];  // a 的出度加一
            ++cnt2[b];  // b 的入度加一
        }
        for (int i = 1; i <= n; ++i) {  // 逐个检查候选人
            if (cnt1[i] == 0 && cnt2[i] == n - 1) {  // 法官不认识任何人（出度为 0），且被其余 n-1 个人信任
                return i;  // 满足两个条件就是法官，直接返回编号
            }
        }
        return -1;  // 没有人满足条件，返回 -1
    }
};