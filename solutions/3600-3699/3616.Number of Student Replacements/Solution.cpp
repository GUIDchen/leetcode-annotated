// 3616. Number of Student Replacements / 学生替换人数
// 核心思路：维护当前队长的最小 rank，顺序扫描时每当出现更小的 rank 就计数加一，即统计破纪录的次数。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)，n 为 ranks 长度。
class Solution {  // 定义题解类
public:  // 公有成员：对外提供 totalReplacements
    int totalReplacements(vector<int>& ranks) {  // 统计队长被更小 rank 的同学替换的总次数
        int ans = 0;  // ans 记录替换次数
        int cur = ranks[0];  // cur 记录当前队长的 rank，初始为第一个人
        for (int x : ranks) {  // 按顺序扫描每位同学
            if (x < cur) {  // 若当前同学的 rank 更小
                cur = x;  // 他成为新队长
                ++ans;  // 替换次数加一
            }  // 结束替换分支
        }  // 结束遍历
        return ans;  // 返回替换总次数
    }  // 方法结束
};  // 类定义结束