// 题目：2332. 坐上公交的最晚时间（The Latest Time to Catch a Bus）
// 思路：两个数组分别排序后按时间顺序贪心模拟每班车能载走哪些乘客，再倒推最后一班车的最晚可达时间，最后把会与乘客撞车的时刻逐个前移。
// 时间复杂度：O((n+m)log(n+m))，主要开销是两次排序；空间复杂度：O(log(n+m))，排序用的递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {  // buses：各班车到站时刻；passengers：乘客到达时刻；capacity：每车座位数
        sort(buses.begin(), buses.end());  // 公交时刻升序，便于按时间顺序逐班模拟
        sort(passengers.begin(), passengers.end());  // 乘客到达升序，先到的人先上车才是最优安排
        int j = 0, c = 0;  // j：已上车的乘客数，也正好是下一位候车乘客的下标；c：当前班车剩余座位数
        for (int t : buses) {  // 按时间顺序模拟每一班车 t
            c = capacity;  // 每班车出发时都有 capacity 个空位
            while (c && j < passengers.size() && passengers[j] <= t) --c, ++j;  // 车还有空位、还有乘客、且该乘客能在 t 前到站，就让他上车；逗号运算符一次更新剩余座位与人数
        }  // 一班车装载完毕
        --j;  // 循环结束后 j 是第一位没上车的乘客，减一即最后一个上了车的人
        int ans = c ? buses[buses.size() - 1] : passengers[j];  // 最后一班车有空位就踩点到发车时刻，否则只能取代最后一个上车乘客的到达时间
        while (~j && ans == passengers[j]) --j, --ans;  // 答案不能与任何乘客的到达时刻重合，逐个前移避开；~j 等价于 j 为合法下标
        return ans;  // 返回最晚还能坐上最后一班车的时间
    }  // 方法结束
};  // 类结束