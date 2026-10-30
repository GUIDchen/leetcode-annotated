// 题目：1701. 平均等待时间（Average Waiting Time）
// 思路：按顾客到达顺序模拟，维护“当前时间”t；每位顾客在 max(t, 到达时间) 开始制作，加做完后再累加其等待时长。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用到常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double averageWaitingTime(vector<vector<int>>& customers) {  // customers 的每项是 {到达时间, 制作耗时}
        double tot = 0;  // 所有顾客的等待时间总和，用 double 避免整数除法丢精度
        int t = 0;  // 厨师空闲下来的时刻，也就是当前时间
        for (auto& e : customers) {  // 顾客已按到达时间升序给出，顺序处理即可
            int a = e[0], b = e[1];  // a：到达时间；b：制作这道菜需要的时长
            t = max(t, a) + b;  // 厨师要等顾客到达（或自己忙完），所以取较大者，再加制作时间
            tot += t - a;  // 等待时间 = 出餐时刻 - 到达时刻，累加进总和
        }
        return tot / customers.size();  // 除以顾客人数得到平均等待时间
    }
};