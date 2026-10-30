// 题目：252. 会议室（Meeting Rooms）
// 思路：按开始时间排序，再检查相邻两场会议是否重叠（前一场的结束时间 > 后一场的开始时间即冲突）。
// 时间复杂度：O(n log n)，排序开销；空间复杂度：O(1)，排序原地进行，只用少量额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 成员函数对外可见
    bool canAttendMeetings(vector<vector<int>>& intervals) {  // intervals：每个元素是 [开始时间, 结束时间]，判断能否参加全部会议
        ranges::sort(intervals, [](const auto& a, const auto& b) {  // C++20 的 ranges::sort：按开始时间升序排列（原地排序）
            return a[0] < b[0];  // 比较规则：开始时间小的排前面
        });  // 排序结束
        for (int i = 1; i < intervals.size(); ++i) {  // 从第二场开始，与前一场比较
            if (intervals[i - 1][1] > intervals[i][0]) {  // 前一场结束时间晚于后一场开始时间，说明时间重叠
                return false;  // 有冲突，无法参加全部会议
            }  // 结束重叠判断
        }  // 结束相邻比较循环
        return true;  // 没有任何重叠，可以全部参加
    }  // 结束 canAttendMeetings 方法
};  // 结束 Solution 类
