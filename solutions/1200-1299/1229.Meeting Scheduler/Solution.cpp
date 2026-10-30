// 题目：1229. 安排会议日程（Meeting Scheduler）
// 思路：两人各自的空闲时段先按开始时间排序，再用双指针求交集：每次只看两个当前区间的重叠部分，重叠够长就返回，否则把结束更早的那个区间的指针前移。
// 时间复杂度：O(m log m + n log n)，主要开销是两次排序；空间复杂度：O(1)，只用了双指针与常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {  // slots1/slots2：两人的空闲时段列表；duration：会议需要的时长，返回最早的可行时间段
        sort(slots1.begin(), slots1.end());  // 把第一个人的空闲时段按开始时间升序排序，便于双指针推进
        sort(slots2.begin(), slots2.end());  // 把第二个人的空闲时段同样排序
        int m = slots1.size(), n = slots2.size();  // m、n 分别是两人空闲时段的个数
        int i = 0, j = 0;  // i、j 是两人当前考察的时段下标
        while (i < m && j < n) {  // 两人都还有时段没看完时继续找重叠
            int start = max(slots1[i][0], slots2[j][0]);  // 重叠区间起点：两个时段开始时间的较大者
            int end = min(slots1[i][1], slots2[j][1]);  // 重叠区间终点：两个时段结束时间的较小者
            if (end - start >= duration) {  // 重叠长度足够放下会议
                return {start, start + duration};  // 取这段重叠的前 duration 分钟返回（排序保证了它是最早的）
            }  // 结束「找到答案」分支
            if (slots1[i][1] < slots2[j][1]) {  // 当前时段更早结束的一方不可能再与对方后面的时段重叠，它的指针要前移
                ++i;  // 第一个人这个时段结束得更早，看他的下一个时段
            } else {  // 否则说明第二个人的这个时段结束得更早
                ++j;  // 改看第二个人的下一个时段
            }  // 结束指针前移的分支
        }  // 结束双指针循环
        return {};  // 所有时段都考察完仍没有够长的重叠，返回空表示无解
    }  // 方法结束
};  // 类定义结束