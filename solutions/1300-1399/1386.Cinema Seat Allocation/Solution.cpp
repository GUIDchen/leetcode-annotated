// 题目：1386. 安排电影院座位（Cinema Seat Allocation）
// 思路：用位掩码记录每一行被预定的座位，未预定的行直接贡献 2 组，其余行按三种四人组合尝试占位。
// 时间复杂度：O(n + r)，n 为预定记录数、r 为被预定过的行数；空间复杂度：O(r)，哈希表存每行掩码。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {  // n 为总行数
        unordered_map<int, int> d;  // 行号 → 该行已占座位的位掩码
        for (auto& e : reservedSeats) {  // 逐条处理预定记录
            int i = e[0], j = e[1];  // i 是行号，j 是座位号（1..10）
            d[i] |= 1 << (10 - j);  // 把座位 j 映射到第 (10-j) 位并置为 1
        }  // 建表结束
        int masks[3] = {0b0111100000, 0b0000011110, 0b0001111000};  // 座位 2-5、6-9、4-7 三种可坐四人的组合
        int ans = (n - d.size()) * 2;  // 完全没有预定的行，每行都能安排两组四人家庭
        for (auto& [_, x] : d) {  // 只处理被预定过的行，x 是该行掩码（引用便于原地修改）
            for (int& mask : masks) {  // 依次尝试三种四人组合
                if ((x & mask) == 0) {  // 组合内的四个座位全部空闲
                    x |= mask;  // 占用这四个座位，避免与后面的组合重复安排
                    ++ans;  // 成功安排一组，答案加一
                }  // 判断结束
            }  // 组合尝试结束
        }  // 所有行处理完毕
        return ans;  // 返回最多可安排的家庭数量
    }  // maxNumberOfFamilies 结束
};  // Solution 类结束