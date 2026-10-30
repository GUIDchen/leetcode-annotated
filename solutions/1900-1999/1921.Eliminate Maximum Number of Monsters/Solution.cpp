// 题目：1921. 消灭怪物的最大数量（Eliminate Maximum Number of Monsters）
// 思路：贪心 + 排序。第 i 只怪物需要到达的时间等价于它能在第 (dist-1)/speed 分钟（0 起）之前被消灭；把各自的“截止时间”升序排序，第 i 只必须在第 i 分钟前解决，否则游戏结束。
// 时间复杂度：O(n log n)，排序为瓶颈；空间复杂度：O(n)，保存每只怪物的截止时间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {  // dist 是初始距离，speed 是速度；返回能消灭的怪物最大数量
        int n = dist.size();  // 怪物数量
        vector<int> times;  // 保存每只怪物的“最晚消灭时刻”（0 起分钟数）
        for (int i = 0; i < n; ++i) {  // 逐只计算截止时间
            times.push_back((dist[i] - 1) / speed[i]);  // 抵达需要 ceil(dist/speed) 分钟，减一后整除即得分秒必争的截止时刻
        }  // 结束逐只计算
        sort(times.begin(), times.end());  // 按截止时间升序排序：越早到的越先处理
        for (int i = 0; i < n; ++i) {  // 第 i 分钟只能消灭一只怪物
            if (times[i] < i) {  // 若这只怪物的截止时刻早于 i，说明第 i 分钟时它已经到达
                return i;  // 来不及了，只能消灭前 i 只
            }  // 结束判断
        }  // 结束遍历
        return n;  // 所有怪物都能被按时消灭
    }  // 方法结束
};  // 类定义结束