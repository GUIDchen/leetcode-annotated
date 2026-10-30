// 3633. 最早完成陆地和水上游乐设施的时间 I / Earliest Finish Time for Land and Water Rides I
// 核心思路：枚举“先陆后水”和“先水后陆”两种顺序，先求第一组的最早结束时间，再与第二组开放时间取大后加时长取最小
// 时间复杂度 O(n + m)，空间复杂度 O(1)
//
class Solution {  // 题目要求实现的类
public:  // 对外接口
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {  // 求先玩一种设施再玩另一种设施时的最早完成时间
        int x = calc(landStartTime, landDuration, waterStartTime, waterDuration);  // 方案一：先陆地，后水上
        int y = calc(waterStartTime, waterDuration, landStartTime, landDuration);  // 方案二：先水上，后陆地
        return min(x, y);  // 取两种方案中较早完成的那个
    }  // 函数结束

    int calc(vector<int>& a1, vector<int>& t1, vector<int>& a2, vector<int>& t2) {  // 辅助函数：先玩 (a1,t1) 这组，再玩 (a2,t2) 这组，返回最早结束时间
        int minEnd = INT_MAX;  // 第一组的最早结束时间，初始为无穷大
        for (int i = 0; i < a1.size(); ++i) {  // 枚举第一组的所有设施
            minEnd = min(minEnd, a1[i] + t1[i]);  // 取结束时间的最小值
        }  // 循环结束，得到第一组的最早结束时刻
        int ans = INT_MAX;  // 第二组的最早结束时间，初始为无穷大
        for (int i = 0; i < a2.size(); ++i) {  // 枚举第二组的所有设施
            ans = min(ans, max(minEnd, a2[i]) + t2[i]);  // 必须等第一组结束才能排队，且不能早于开放时间 a2[i]，再加游玩时长 t2[i]
        }  // 循环结束
        return ans;  // 返回该顺序下的最早完成时间
    }  // 辅助函数结束
};  // 类定义结束
