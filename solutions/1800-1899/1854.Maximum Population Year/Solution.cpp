// 题目：1854. 人口最多的年份（Maximum Population Year）
// 思路：差分数组，出生年 +1、死亡年（含该年活着的人到上一年）−1，前缀和即为各年人口，取第一个最大值。
// 时间复杂度：O(n + 101)，扫描日志加一次 101 年的遍历；空间复杂度：O(1)，差分数组固定 101 长。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumPopulation(vector<vector<int>>& logs) {  // logs：每条记录是 [出生年, 死亡年]
        int d[101]{};  // 差分数组，覆盖 1950..2050 共 101 年，{} 会全部初始化为 0
        const int offset = 1950;  // 基准年，把年份映射到 0..100 的下标
        for (auto& log : logs) {  // 逐条处理每个人的出生与死亡
            int a = log[0] - offset;  // 出生年映射成下标
            int b = log[1] - offset;  // 死亡年映射成下标（该年此人已不算在人口内）
            ++d[a];  // 出生年人口 +1
            --d[b];  // 死亡年人口 −1，差分前缀和会自动覆盖中间所有年份
        }  // 结束 for
        int s = 0, mx = 0;  // s 是当前年份的人口，mx 是历史最大人口
        int j = 0;  // j 记录人口最大时的年份下标
        for (int i = 0; i < 101; ++i) {  // 从 1950 年顺序扫到 2050 年
            s += d[i];  // 前缀和还原出该年的实际人口
            if (mx < s) {  // 只有严格更大才更新，保证取到最早的年份
                mx = s;  // 更新最大人口
                j = i;  // 记下该年份的下标
            }  // 结束 if
        }  // 结束 for
        return j + offset;  // 下标换回真实年份
    }  // 结束 maximumPopulation
};  // 结束 Solution 类