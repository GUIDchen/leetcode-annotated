// 题目：1997. 访问完所有房间的第一天（First Day Where You Have Been in All the Rooms）
// 思路：动态规划，f[i] 表示第一次访问完房间 0..i 的最早天数；从 i-1 到 i 会被弹回 nextVisit[i-1]，需补回这段往返。
// 时间复杂度：O(n)，一次线性递推；空间复杂度：O(n)，保存长度为 n 的 dp 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {  // nextVisit[i]：奇数次访问房间 i 时下一天要去的房间
        int n = nextVisit.size();  // 房间总数
        vector<long long> f(n);  // f[i]：第一次访问完房间 0..i 的最早天数，初值全为 0
        const int mod = 1e9 + 7;  // 结果需要对 1e9+7 取模
        for (int i = 1; i < n; ++i) {  // 从房间 1 开始逐个递推
            f[i] = (f[i - 1] + 1 + f[i - 1] - f[nextVisit[i - 1]] + 1 + mod) % mod;  // 进入 i（+1）+ 由 nextVisit[i-1] 重返 i-1 的天数（f[i-1]-f[nextVisit[i-1]]）+ 再次进入 i（+1）；加 mod 防止负数取模
        }
        return f[n - 1];  // 返回第一次访问完所有房间的天数，隐式转回 int
    }
};