// 题目：2237. 计算街道上满足所需亮度的位置数量（Count Positions on Street With Required Brightness）
// 思路：差分数组。每盏灯把区间 [p-r, p+r] 截断到 [0, n-1] 后做端点 +1 / -1，最后前缀和还原每个位置的灯数，逐点与 requirement 比较。
// 时间复杂度：O(n + m)，m 为灯的数量，每个位置、每盏灯各访问一次；空间复杂度：O(n)，差分数组长度为 n+1。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int meetRequirement(int n, vector<vector<int>>& lights, vector<int>& requirement) {  // n：街道位置数；lights：每盏灯的 [位置, 照明半径]；requirement：每个位置所需的最少灯数
        vector<int> d(n + 1);  // 差分数组：多开一位，让 d[n] 用来承接右端点之后的减一，避免越界
        for (const auto& e : lights) {  // 逐盏灯把它能照亮的区间累计到差分数组上
            int i = max(0, e[0] - e[1]), j = min(n - 1, e[0] + e[1]);  // 覆盖区间左右端点，并截断到街道范围 [0, n-1] 内
            ++d[i];  // 区间起点 +1：从这里开始灯数增加
            --d[j + 1];  // 区间终点后一位 -1：从 j+1 开始灯数减少（j+1 最大为 n，不越界）
        }
        int s = 0, ans = 0;  // s：前缀和，即当前位置的灯数；ans：满足亮度要求的位置个数
        for (int i = 0; i < n; ++i) {  // 从左到右扫描，用差分数组还原每个位置的真实灯数
            s += d[i];  // 累加差分值得到位置 i 的灯数
            if (s >= requirement[i]) {  // 灯数达到该位置所需亮度
                ++ans;  // 该位置满足要求，答案加一
            }
        }
        return ans;  // 返回满足要求的位置总数
    }
};
