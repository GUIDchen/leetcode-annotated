// 题目：881. 救生艇（Boats to Save People）
// 思路：体重升序排序后双指针，每次让最重的人尝试与最轻的人同船，能装下就左指针右移；每轮至少送走最重的一人，船数加一。
// 时间复杂度：O(n log n)，排序为主；空间复杂度：O(log n)，排序所需的栈空间。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int numRescueBoats(vector<int>& people, int limit) {  // people：每人体重；limit：每艘艇的载重上限
        sort(people.begin(), people.end());  // 升序排序，方便用双指针做「一重一轻」配对
        int ans = 0;  // ans 记录需要的救生艇数量
        for (int i = 0, j = people.size() - 1; i <= j; --j) {  // i 指向最轻的人，j 指向最重的人；每轮至少运走最重的一人
            if (people[i] + people[j] <= limit) {  // 最重的人能和最轻的人同船
                ++i;  // 最轻的人一起上船，左指针右移
            }
            ++ans;  // 无论是否配对成功，这艘船都要开走
        }
        return ans;  // 返回最少船数
    }  // 方法结束
};  // 类定义结束