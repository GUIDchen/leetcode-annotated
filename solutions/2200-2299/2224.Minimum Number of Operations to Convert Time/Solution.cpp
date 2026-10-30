// 题目：2224. 转化时间需要的最少操作数（Minimum Number of Operations to Convert Time）
// 思路：两个时刻都换算成分钟，按 60、15、5、1 从大到小贪心取用，大增量用得越多操作数越少。
// 时间复杂度：O(1)，只遍历 4 种固定增量；空间复杂度：O(1)，仅使用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int convertTime(string current, string correct) {  // current：当前时间；correct：目标时间，格式均为 "HH:MM"
        int a = stoi(current.substr(0, 2)) * 60 + stoi(current.substr(3, 2));  // 当前时间折算成分钟
        int b = stoi(correct.substr(0, 2)) * 60 + stoi(correct.substr(3, 2));  // 目标时间折算成分钟
        int ans = 0, d = b - a;  // ans 记录操作次数，d 表示还差多少分钟
        vector<int> inc = {60, 15, 5, 1};  // 可选的四种时间增量，按从大到小排列
        for (int i : inc) {  // 依次尝试每一种增量
            ans += d / i;  // 当前增量最多能使用 d / i 次
            d %= i;  // 用完后剩余的分钟数
        }
        return ans;  // 返回最少操作次数
    }
};
